/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			ds1307.h
 * Module:			DS1307 Real Time Clock controller
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 20, 2018
 * Purpose:			Controls and interfaces a DS1307 Real Time Clock
 * Notes:			This code makes use of some functions defined in twiMaster
 *					module. To use this code with the dedicated peripheral,
 *					just include the twiMaster module files. In order to use the
 *					device with a I2C BitBang interface, please use the same
 *					function names.
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "ds1307.h"
#if __DS1307_H != 1
#error Error 101 - Build mismatch on header and source code files (ds1307).
#endif

// -----------------------------------------------------------------------------
// Constant definitions (used only in this file) -------------------------------

#define DS1307_SECONDS_NO_CHANGE	63
#define DS1307_MINUTES_NO_CHANGE	63
#define DS1307_HOURS_NO_CHANGE		31
#define DS1307_MONTH_DAY_NO_CHANGE	0
#define DS1307_MONTH_NO_CHANGE		0
#define DS1307_YEAR_NO_CHANGE		0

// -----------------------------------------------------------------------------
// New data types (used only in this file) -------------------------------------

typedef enum ds1307RegisterAddress_t {
    DS1307_ADDRESS_SECONDS		= 0x00,
    DS1307_ADDRESS_MINUTES		= 0x01,
    DS1307_ADDRESS_HOURS		= 0x02,
    DS1307_ADDRESS_WEEK_DAY		= 0x03,
    DS1307_ADDRESS_MONTH_DAY	= 0x04,
    DS1307_ADDRESS_MONTH		= 0x05,
    DS1307_ADDRESS_YEAR			= 0x06,
    DS1307_ADDRESS_CONTROL		= 0x07,
    DS1307_ADDRESS_RAM			= 0x08
} ds1307RegisterAddress_t;

#define DS1307_I2C_MIN_CLOCK_SPEED	0UL
#define DS1307_I2C_MAX_CLOCK_SPEED	100000UL
#define DS1307_COUNTER_HALT_BIT		7
#define DS1307_TIME_FORMAT_BIT		6
#define DS1307_TIME_AMPM_BIT		5
#define DS1307_OUTPUT_LEVEL_BIT		7
#define DS1307_SQW_ENABLE_BIT		4
#define DS1307_SQW_FREQUENCY_BIT	0

// -----------------------------------------------------------------------------
// Static function declarations ------------------------------------------------

static void	ds1307GetData(void);

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

ds1307_t ds1307			= {.seconds = 0, .minutes = 0, .hours = 0, .timeFormat = DS1307_TIME_FORMAT_24, .weekDay = WEEKDAY_TUESDAY, .monthDay = 20, .month = 3, .year = 18, .output = DS1307_OUTPUT_LOW, .countingStatus = DS1307_COUNTING_RESUME, .unusedBits = 0};
ds1307_t ds1307Queue	= {.seconds = DS1307_SECONDS_NO_CHANGE, .minutes = DS1307_MINUTES_NO_CHANGE, .hours = DS1307_HOURS_NO_CHANGE, .timeFormat = DS1307_TIME_FORMAT_NO_CHANGE, .weekDay = WEEKDAY_UNDEFINED, .monthDay = DS1307_MONTH_DAY_NO_CHANGE, .month = DS1307_MONTH_NO_CHANGE, .year = DS1307_YEAR_NO_CHANGE, .output = DS1307_OUTPUT_NO_CHANGE, .countingStatus = DS1307_COUNTING_NO_CHANGE, .unusedBits = 0};

// -----------------------------------------------------------------------------
// Public function definitions -------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	ds1307ChangeTimeFormat
 * Purpose:		Changes the current time format
 * Arguments:	timeFormat	ds1307TimeFormat_t enumeration
 *				queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors, except if queued
 * -------------------------------------------------------------------------- */

void ds1307ChangeTimeFormat(ds1307TimeFormat_t timeFormat, bool_t queued)
{
    uint8_t buffer[2] = {0, 0};

    // No need to change, just return
    if (timeFormat == DS1307_TIME_FORMAT_NO_CHANGE) {
        return;
    }

    // Stores in the queue
    if (queued) {
        ds1307Queue.timeFormat = timeFormat;
        return;
    }

    // Retrieve data from device
    ds1307GetData();

    // Update variables
    switch (timeFormat) {
    case DS1307_TIME_FORMAT_AM:
    case DS1307_TIME_FORMAT_PM:
        buffer[1] = (timeFormat >> DS1307_TIME_FORMAT_BIT);
        setBit(buffer[1], DS1307_TIME_AMPM_BIT);
        // No need to change, just return
        if ((ds1307.timeFormat == DS1307_TIME_FORMAT_AM)  || (ds1307.timeFormat == DS1307_TIME_FORMAT_PM)) {
            return;
        }
        // Need to change the time format from 24 hours to AM/PM
        if (ds1307.hours >= 12) {
            ds1307.timeFormat = DS1307_TIME_FORMAT_PM;
            ds1307.hours -= 12;
            if (ds1307.hours == 0) {
                ds1307.hours = 12;
            }
        } else {
            ds1307.timeFormat = DS1307_TIME_FORMAT_AM;
            if (ds1307.hours == 0) {
                ds1307.hours = 12;
            }
        }
        break;
    case DS1307_TIME_FORMAT_24:
        // No need to change, just return
        if (ds1307.timeFormat == DS1307_TIME_FORMAT_24) {
            return;
        }
        // Need to change the time format from AM/PM to 24 hours
        if (ds1307.timeFormat == DS1307_TIME_FORMAT_AM) {
            if (ds1307.hours == 12) {
                ds1307.hours = 0;
            }
        } else {
            ds1307.hours += 12;
            if (ds1307.hours == 24) {
                ds1307.hours = 12;
            }
        }
        break;
    case DS1307_TIME_FORMAT_NO_CHANGE:
        // No need to change, just return
        return;
    }
    buffer[1] |= (ds1307.hours % 10);
    buffer[1] |= (ds1307.hours / 10) << 4;

    // Sends data back to device
    buffer[0] = DS1307_ADDRESS_HOURS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 2);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307CountingResume
 * Purpose:		Resumes device counting cycle
 * Arguments:	queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors, except if queued
 * -------------------------------------------------------------------------- */

void ds1307CountingResume(bool_t queued)
{
    uint8_t buffer[2] = {0, 0};

    // Stores in the queue
    if (queued) {
        ds1307Queue.countingStatus = DS1307_COUNTING_RESUME;
        return;
    }

    // Retrieve data from device
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 1);
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, buffer, 2);
    // Update variables
    clrBit(buffer[1], DS1307_COUNTER_HALT_BIT);
    ds1307.countingStatus = DS1307_COUNTING_RESUME;
    // Sends data back to device
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 2);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307CountingStop
 * Purpose:		Stop device counting cycle
 * Arguments:	queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors, except if queued
 * -------------------------------------------------------------------------- */

void ds1307CountingStop(bool_t queued)
{
    uint8_t buffer[2] = {0, 0};

    // Stores in the queue
    if (queued) {
        ds1307Queue.countingStatus = DS1307_COUNTING_HALT;
        return;
    }

    // Retrieve data from device
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 1);
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, buffer, 2);
    // Update variables
    setBit(buffer[1], DS1307_COUNTER_HALT_BIT);
    ds1307.countingStatus = DS1307_COUNTING_HALT;
    // Sends data back to device
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 2);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307ReadDate
 * Purpose:		Reads the current date from ds1307
 * Arguments:	year		Pointer to a variable to store the year
 *				month		Pointer to a month_t enumeration to store the month
 *				monthDay	Pointer to a variable to store the day of the month
 *				weekDay		Pointer to a weekDay_t enumeration to store the day of the week
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

void ds1307ReadDate(uint8_t *year, month_t *month, uint8_t *monthDay, weekDay_t *weekDay)
{
    uint8_t buffer[4] = {0, 0, 0, 0};

    // Retrieve data from device
    buffer[0] = DS1307_ADDRESS_WEEK_DAY;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 1);
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, buffer, 4);

    // Update variables
    ds1307.weekDay = buffer[0];
    ds1307.monthDay = ((buffer[1] >> 4) * 10) + (buffer[1] & 0x0F);
    ds1307.month = ((buffer[2] >> 4) * 10) + (buffer[2] & 0x0F);
    ds1307.year = ((buffer[3] >> 4) * 10) + (buffer[3] & 0x0F);
    *year = ds1307.year;
    *month = ds1307.month;
    *monthDay = ds1307.monthDay;
    *weekDay = ds1307.weekDay;

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307ReadRamData
 * Purpose:		Returns the data at the position of the internal RAM
 * Arguments:	position	Position of the memory byte to be read (position
 *							values and absolute addresses are shifted 8 by an
 *							offset of 8 values)
 * Returns:		The value of the byte stores at the given position
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

uint8_t	ds1307ReadRamData(uint8_t position)
{
    uint8_t buffer;

    buffer = DS1307_ADDRESS_RAM + position;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, &buffer, 1);
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, &buffer, 1);

    return buffer;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307ReadTime
 * Purpose:		Reads the current time from ds1307
 * Arguments:	hours		Pointer to a variable to store the hours
 *				minutes		Pointer to a variable to store the minutes
 *				seconds		Pointer to a variable to store the seconds
 * Returns:					ds1307TimeFormat_t enumeration
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

ds1307TimeFormat_t ds1307ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
    uint8_t buffer[3] = {0, 0, 0};

    // Retrieve data from device
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 1);
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, buffer, 3);

    // Update variables
    ds1307.countingStatus = isBitSet(buffer[0], DS1307_COUNTER_HALT_BIT);
    buffer[0] &= 0x7F;
    ds1307.seconds = ((buffer[0] >> 4) * 10) + (buffer[0] & 0x0F);
    ds1307.minutes = ((buffer[1] >> 4) * 10) + (buffer[1] & 0x0F);
    if (isBitSet(buffer[2], DS1307_TIME_FORMAT_BIT)) {		// 12 hour-mode
        if (isBitSet(buffer[2], DS1307_TIME_AMPM_BIT)) {
            ds1307.timeFormat = DS1307_TIME_FORMAT_PM;
        } else {
            ds1307.timeFormat = DS1307_TIME_FORMAT_AM;
        }
        ds1307.hours = (((buffer[2] & 0x10) >> 4) * 10) + (buffer[2] & 0x0F);
    } else {												// 24 hour-mode
        ds1307.timeFormat = DS1307_TIME_FORMAT_24;
        ds1307.hours = (((buffer[2] & 0x30) >> 4) * 10) + (buffer[2] & 0x0F);
    }

    *hours = ds1307.hours;
    *minutes = ds1307.minutes;
    *seconds = ds1307.seconds;

    return ds1307.timeFormat;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307SetOutput
 * Purpose:		Set the device square wave generator
 * Arguments:	output		ds1307Output_t enumeration
 *				queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors, except if queued
 * -------------------------------------------------------------------------- */

void ds1307SetOutput(ds1307Output_t output, bool_t queued)
{
    uint8_t buffer[2] = {0, 0};

    // No need to change, just return
    if (output == DS1307_OUTPUT_NO_CHANGE) {
        return;
    }

    // Stores in the queue
    if (queued) {
        ds1307Queue.output = output;
        return;
    }

    // Update variables
    if (output > DS1307_OUTPUT_32768_HZ) {
        buffer[1] = ((output - 5) << DS1307_OUTPUT_LEVEL_BIT);
    } else {
        buffer[1] = (output & 0x03) << DS1307_SQW_FREQUENCY_BIT;
        setBit(buffer[1], DS1307_SQW_ENABLE_BIT);
    }
    ds1307.output = output;

    // Sends data back to device
    buffer[0] = DS1307_ADDRESS_CONTROL;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 2);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307SetDate
 * Purpose:		Changes the current date at the ds1307
 * Arguments:	year		Value of the year
 *				month		Value of the month
 *				monthDay	Value of the monthDay
 *				weekDay		Value of the weekDay
 *				queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		DS1307_OK
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

void ds1307SetDate(uint8_t year, month_t month, uint8_t monthDay, weekDay_t weekDay, bool_t queued)
{
    uint8_t buffer[5];

    // Wrong value passed, just return
    if (weekDay == WEEKDAY_UNDEFINED) {
        return;
    }

    // Stores in the queue
    if (queued) {
        ds1307Queue.weekDay = weekDay;
        ds1307Queue.monthDay = monthDay;
        ds1307Queue.month = month;
        ds1307Queue.year = year;
        return;
    }

    // Update variables
    ds1307.weekDay = weekDay;
    buffer[1] = weekDay;
    ds1307.monthDay = monthDay;
    buffer[2] = ((monthDay / 10) << 4) | (monthDay % 10);
    ds1307.month = month;
    buffer[3] = ((month / 10) << 4) | (month % 10);
    ds1307.year = year;
    buffer[4] = ((year / 10) << 4) | (year % 10);

    // Sends data back to device
    buffer[0] = DS1307_ADDRESS_WEEK_DAY;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 5);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307SetTime
 * Purpose:		Changes the current time at the ds1307
 * Arguments:	hours		Value of the hours
 *				minutes		Value of the minutes
 *				seconds		Value of the seconds
 *				abbrev		ds1307TimeFormat_t enumeration
 *				queued		FALSE	-> send changes to device
 *							TRUE	-> store but do not send changes to device
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors, except if queued
 * -------------------------------------------------------------------------- */

void ds1307SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, ds1307TimeFormat_t timeFormat, bool_t queued)
{
    uint8_t buffer[4] = {0, 0, 0, 0};

    // Stores in the queue
    if (queued) {
        ds1307Queue.seconds = seconds;
        ds1307Queue.minutes = minutes;
        ds1307Queue.hours = hours ;
        if (ds1307Queue.timeFormat != DS1307_TIME_FORMAT_NO_CHANGE) {
            ds1307Queue.timeFormat = timeFormat;
        }
        return;
    }

    // Update variables
    ds1307.seconds = seconds;
    buffer[1] = ((seconds / 10) << 4);
    buffer[1] |= (seconds % 10);
    if (ds1307.countingStatus == DS1307_COUNTING_HALT) {
        setBit(buffer[1], DS1307_COUNTER_HALT_BIT);
    }
    ds1307.minutes = minutes;
    buffer[2] = ((minutes / 10) << 4);
    buffer[2] |= (minutes % 10);
    ds1307.hours = hours;
    buffer[3] = ((hours / 10) << 4);
    buffer[3] |= (hours % 10);
    if (timeFormat != DS1307_TIME_FORMAT_NO_CHANGE) {
        ds1307.timeFormat = timeFormat;
    }
    switch (ds1307.timeFormat) {
    case DS1307_TIME_FORMAT_PM:
        setBit(buffer[3], DS1307_TIME_AMPM_BIT);
    case DS1307_TIME_FORMAT_AM:
        setBit(buffer[3], DS1307_TIME_FORMAT_BIT);
        break;
    case DS1307_TIME_FORMAT_24:
        break;
    }

    // Sends data back to device
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 4);

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307StoreQueuedData
 * Purpose:		Sends all queued data to the device
 * Arguments:	-
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

void ds1307StoreQueuedData(void)
{
    uint8_t buffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Retrieve data from device
    ds1307GetData();

    // Update variables
    if (ds1307Queue.countingStatus == DS1307_COUNTING_NO_CHANGE) {
        setMaskOffset(buffer[1], ds1307.countingStatus, DS1307_COUNTER_HALT_BIT);
    } else {
        setMaskOffset(buffer[1], ds1307Queue.countingStatus, DS1307_COUNTER_HALT_BIT);
    }
    if (ds1307Queue.seconds == DS1307_SECONDS_NO_CHANGE) {
        buffer[1] |= ((ds1307.seconds / 10) << 4);
        buffer[1] |= (ds1307.seconds % 10);
    } else {
        buffer[1] |= ((ds1307Queue.seconds / 10) << 4);
        buffer[1] |= (ds1307Queue.seconds % 10);
    }
    if (ds1307Queue.minutes == DS1307_MINUTES_NO_CHANGE) {
        buffer[2] = ((ds1307.minutes / 10) << 4);
        buffer[2] |= (ds1307.minutes % 10);
    } else {
        buffer[2] = ((ds1307Queue.minutes / 10) << 4);
        buffer[2] |= (ds1307Queue.minutes % 10);
    }
    if (ds1307Queue.hours == DS1307_HOURS_NO_CHANGE) {
        buffer[3] = ((ds1307.hours / 10) << 4);
        buffer[3] |= (ds1307.hours % 10);
        switch (ds1307.timeFormat) {
        case DS1307_TIME_FORMAT_PM:
            setBit(buffer[3], DS1307_TIME_AMPM_BIT);
        case DS1307_TIME_FORMAT_AM:
            setBit(buffer[3], DS1307_TIME_FORMAT_BIT);
            break;
        case DS1307_TIME_FORMAT_24:
            break;
        }
    } else {
        buffer[3] = ((ds1307Queue.hours / 10) << 4);
        buffer[3] |= (ds1307Queue.hours % 10);
        switch (ds1307Queue.timeFormat) {
        case DS1307_TIME_FORMAT_PM:
            setBit(buffer[3], DS1307_TIME_AMPM_BIT);
        case DS1307_TIME_FORMAT_AM:
            setBit(buffer[3], DS1307_TIME_FORMAT_BIT);
            break;
        case DS1307_TIME_FORMAT_24:
            break;
        }
    }
    if (ds1307Queue.weekDay == WEEKDAY_UNDEFINED) {
        buffer[4] = ds1307.weekDay;
    } else {
        buffer[4] = ds1307Queue.weekDay;
    }
    if (ds1307Queue.monthDay == DS1307_MONTH_DAY_NO_CHANGE) {
        buffer[5] = ((ds1307.monthDay / 10) << 4);
        buffer[5] |= (ds1307.monthDay % 10);
    } else {
        buffer[5] = ((ds1307Queue.monthDay / 10) << 4);
        buffer[5] |= (ds1307Queue.monthDay % 10);
    }
    if (ds1307Queue.month == DS1307_MONTH_NO_CHANGE) {
        buffer[6] = ((ds1307.month / 10) << 4);
        buffer[6] |= (ds1307.month % 10);
    } else {
        buffer[6] = ((ds1307Queue.month / 10) << 4);
        buffer[6] |= (ds1307Queue.month % 10);
    }
    if (ds1307Queue.year == DS1307_YEAR_NO_CHANGE) {
        buffer[7] = ((ds1307.year / 10) << 4);
        buffer[7] |= (ds1307.year % 10);
    } else {
        buffer[7] = ((ds1307Queue.year / 10) << 4);
        buffer[7] = (ds1307Queue.year % 10);
    }
    if (ds1307Queue.output == DS1307_OUTPUT_NO_CHANGE) {
        if (ds1307.output > DS1307_OUTPUT_32768_HZ) {
            buffer[8] = ((ds1307.output - 5) << DS1307_OUTPUT_LEVEL_BIT);
        } else {
            buffer[8] = (ds1307.output & 0x03) << DS1307_SQW_FREQUENCY_BIT;
            setBit(buffer[8], DS1307_SQW_ENABLE_BIT);
        }
    } else {
        if (ds1307Queue.output > DS1307_OUTPUT_32768_HZ) {
            buffer[8] = ((ds1307Queue.output - 5) << DS1307_OUTPUT_LEVEL_BIT);
        } else {
            buffer[8] = (ds1307Queue.output & 0x03) << DS1307_SQW_FREQUENCY_BIT;
            setBit(buffer[8], DS1307_SQW_ENABLE_BIT);
        }
    }

    // Sends data back to device
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 9);

    // Reset variables to default:
    ds1307Queue.seconds = DS1307_SECONDS_NO_CHANGE;
    ds1307Queue.minutes = DS1307_MINUTES_NO_CHANGE;
    ds1307Queue.hours = DS1307_HOURS_NO_CHANGE;
    ds1307Queue.timeFormat = DS1307_TIME_FORMAT_NO_CHANGE;
    ds1307Queue.weekDay = WEEKDAY_UNDEFINED;
    ds1307Queue.monthDay = DS1307_MONTH_DAY_NO_CHANGE;
    ds1307Queue.month = DS1307_MONTH_NO_CHANGE;
    ds1307Queue.year = DS1307_YEAR_NO_CHANGE;
    ds1307Queue.output = DS1307_OUTPUT_NO_CHANGE;
    ds1307Queue.countingStatus = DS1307_COUNTING_NO_CHANGE;
    ds1307Queue.unusedBits = 0;

    return;
}

/* -----------------------------------------------------------------------------
 * Function:	ds1307SetRamData
 * Purpose:		Writes the given data at the position of the internal RAM
 * Arguments:	data		Value to be stored in the internal RAM
 *				position	Position of the memory byte to be read (position
 *							values and absolute addresses are shifted 8 by an
 *							offset of 8 values)
 * Returns:		-
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

void ds1307WriteRamData(uint8_t data, uint8_t position)
{
    uint8_t buffer[2] = {0, 0};

    buffer[0] = DS1307_ADDRESS_RAM + position;
    buffer[1] = data;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 2);

    return;
}

// -----------------------------------------------------------------------------
// Private function definitions ------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	ds1307GetData
 * Purpose:		Gets data from DS1307 and updates internal struct
 * Arguments:	none
 * Returns:		DS1307_OK
 * Notes:		Since the i2c controller is interrupt-driven, this function must
 * 				be called outside of the interrupt vectors
 * -------------------------------------------------------------------------- */

void ds1307GetData(void)
{
    uint8_t buffer[8];

    // Sets DS1307 internal pointer to address 0x00
    buffer[0] = DS1307_ADDRESS_SECONDS;
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_WRITE, buffer, 1);
    // Retrieve all available data
    twiMasterSendData(DS1307_SLAVE_ADDRESS, TWI_READ, buffer, 8);
    // Decodes the information
    ds1307.countingStatus = isBitSet(buffer[0], DS1307_COUNTER_HALT_BIT);
    buffer[0] &= 0x7F;
    ds1307.seconds = ((buffer[0] >> 4) * 10) + (buffer[0] & 0x0F);
    ds1307.minutes = ((buffer[1] >> 4) * 10) + (buffer[1] & 0x0F);
    if (isBitSet(buffer[2], DS1307_TIME_FORMAT_BIT)) {	// 12 hour-mode
        if (isBitSet(buffer[2], DS1307_TIME_AMPM_BIT)) {
            ds1307.timeFormat = DS1307_TIME_FORMAT_PM;
        } else {
            ds1307.timeFormat = DS1307_TIME_FORMAT_AM;
        }
        ds1307.hours = (((buffer[2] & 0x10) >> 4) * 10) + (buffer[2] & 0x0F);
    } else {						// 24 hour-mode
        ds1307.timeFormat = DS1307_TIME_FORMAT_24;
        ds1307.hours = (((buffer[2] & 0x30) >> 4) * 10) + (buffer[2] & 0x0F);
    }
    ds1307.weekDay = buffer[3];
    ds1307.monthDay = ((buffer[4] >> 4) * 10) + (buffer[4] & 0x0F);
    ds1307.month = ((buffer[5] >> 4) * 10) + (buffer[5] & 0x0F);
    ds1307.year = ((buffer[6] >> 4) * 10) + (buffer[6] & 0x0F);

    if (isBitSet(buffer[7], DS1307_SQW_ENABLE_BIT)) {	// Square wave enabled
        ds1307.output = buffer[7] & 0x03;
    } else {
        ds1307.output = (buffer[7] & (1 << 4)) + 5;
    }

    return;
}
