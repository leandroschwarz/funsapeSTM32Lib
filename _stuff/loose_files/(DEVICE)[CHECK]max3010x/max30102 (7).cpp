/* =============================================================================
 * Project:		GPSDE++ AVR Library
 * File name:	max30102.cpp
 * Module:		MAX30102 module interface for GPDSE++ Library project
 * Authors:		Leandro Schwarz
 *				Hazael dos Santos Batista
 * Build:		1002
 * Date:		June 14, 2018
 * ========================================================================== */

// =============================================================================
// Dependencies
// =============================================================================

#include "max30102.hpp"
#if __MAX30102_HPP != 1002
#	error [max30102.cpp] Error 102 - Build mismatch on header and source code files.
#endif

#include <stddef.h>
#include <stdint.h>

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define MAX30102_DEVICE_ADDRESS			0x57
#define MAX30102_PART_ID				0x15
#define MAX30102_BYTES_PER_CHANNEL		3
#define MAX30102_FIFO_SIZE_IN_SAMPLES	32

void twiSetClock(uint32_t clockSpeed __attribute__((unused)))
{

}

// =============================================================================
// File exclusive - New data types
// =============================================================================

typedef enum max30102Register_e {
	// Status registers
	MAX30102_REG_INTERRUPT_STATUS_1				= 0x00,
	MAX30102_REG_INTERRUPT_STATUS_2				= 0x01,
	MAX30102_REG_INTERRUPT_ENABLE_1				= 0x02,
	MAX30102_REG_INTERRUPT_ENABLE_2				= 0x03,

	// FIFO registers
	MAX30102_REG_FIFO_WRITE_POINTER				= 0x04,
	MAX30102_REG_FIFO_OVERFLOW_COUNTER			= 0x05,
	MAX30102_REG_FIFO_READ_POINTER				= 0x06,
	MAX30102_REG_FIFO_DATA						= 0x07,

	// Configuration registers
	MAX30102_REG_FIFO_CONFIGURATION				= 0x08,
	MAX30102_REG_MODE_CONFIGURATION				= 0x09,
	MAX30102_REG_SPO2_CONFIGURATION				= 0x0A,
	MAX30102_REG_LED1_PULSE_AMPLITUDE			= 0x0C,
	MAX30102_REG_LED2_PULSE_AMPLITUDE			= 0x0D,
	MAX30102_REG_LED3_PULSE_AMPLITUDE			= 0x0E,
	MAX30102_REG_PROXIMITY_LED_AMPLITUDE		= 0x10,
	MAX30102_REG_MULTI_LED_CONTROL_1			= 0x11,
	MAX30102_REG_MULTI_LED_CONTROL_2			= 0x12,

	// Die temperature registers
	MAX30102_REG_DIE_TEMPERATURE_INTEGER		= 0x1F,
	MAX30102_REG_DIE_TEMPERATURE_FRACTION		= 0x20,
	MAX30102_REG_DIE_TEMPERATURE_CONFIG			= 0x21,

	// Proximity function registers
	MAX30102_REG_PROXIMITY_INTERRUPT_THRESHOLD	= 0x30,

	// Part ID registers
	MAX30102_REG_REVISION_ID					= 0xFE,
	MAX30102_REG_PART_ID						= 0xFF
} max30102Register_e;

typedef enum max30102Bit_e {
	// Interrupt
	MAX30102_BIT_INTERRUPT_FIFO_ALMOST_FULL_FLAG		= 7,		// Interrupt Status 1
	MAX30102_BIT_INTERRUPT_FIFO_NEW_DATA_READY_FLAG		= 6,
	MAX30102_BIT_INTERRUPT_AMBIENT_LIGHT_CANC_FLAG		= 5,
	MAX30102_BIT_INTERRUPT_PROXIMITY_THRESHOLD_FLAG		= 4,
	MAX30102_BIT_INTERRUPT_POWER_READY_FLAG				= 0,
	MAX30102_BIT_INTERRUPT_DIE_TEMPERATURE_READY_FLAG	= 1,		// Interrupt Status 2
	MAX30102_BIT_INTERRUPT_FIFO_ALMOST_FULL_ENABLE		= 7,		// Interrupt Enable 1
	MAX30102_BIT_INTERRUPT_FIFO_NEW_DATA_READY_ENABLE	= 6,
	MAX30102_BIT_INTERRUPT_AMBIENT_LIGHT_CANC_ENABLE	= 5,
	MAX30102_BIT_INTERRUPT_PROXIMITY_THRESHOLD_ENABLE	= 4,
	MAX30102_BIT_INTERRUPT_DIE_TEMPERATURE_READY_ENABLE	= 1,		// Interrupt Enable 2

	// FIFO
	MAX30102_BIT_FIFO_WR_PTR						= 0,		// FIFO Write Pointer
	MAX30102_BIT_FIFO_OVF_COUNTER					= 0,		// FIFO Overflow Counter
	MAX30102_BIT_FIFO_RD_PTR						= 0,		// FIFO Read Pointer
	MAX30102_BIT_FIFO_DATA							= 0,		// FIFO Data Register

	// Configuration
	MAX30102_BIT_CONFIGURATION_SMP_AVE				= 5,		// FIFO Configuration
	MAX30102_BIT_CONFIGURATION_FIFO_ROLLOVER_EN		= 4,
	MAX30102_BIT_CONFIGURATION_FIFO_A_FULL			= 0,
	MAX30102_BIT_CONFIGURATION_SHDN					= 7,		// Mode Configuration
	MAX30102_BIT_CONFIGURATION_RESET				= 6,
	MAX30102_BIT_CONFIGURATION_MODE					= 0,
	MAX30102_BIT_CONFIGURATION_SENSOR_FULL_SCALE	= 5,		// SPO2 Configuration
	MAX30102_BIT_CONFIGURATION_SENSOR_SAMPLE_RATE	= 2,
	MAX30102_BIT_CONFIGURATION_SENSOR_RESOLUTION	= 0,
	MAX30102_BIT_CONFIGURATION_LED1_PA				= 0,		// LED Pulse Amplitude 1
	MAX30102_BIT_CONFIGURATION_LED2_PA				= 0,		// LED Pulse Amplitude 2
	MAX30102_BIT_CONFIGURATION_PILOT_PA				= 0,		// Proximity Mode LED Pulse Amplitude
	MAX30102_BIT_CONFIGURATION_SLOT2				= 4,		// Multi-LED Mode Control Register 1
	MAX30102_BIT_CONFIGURATION_SLOT1				= 0,
	MAX30102_BIT_CONFIGURATION_SLOT4				= 4,		// Multi-LED Mode Control Register 2
	MAX30102_BIT_CONFIGURATION_SLOT3				= 0,

	// Temperature Data
	MAX30102_BIT_TEMPERATURE_TINT					= 0,		// Die Temperature Integer
	MAX30102_BIT_TEMPERATURE_TFRAC					= 0,		// Die Temperature Fraction
	MAX30102_BIT_TEMPERATURE_TEMP_EN				= 0,		// Die Temperature Config

	// Proximity Function
	MAX30102_BIT_PROX_INT_THRESH					= 0,		// Proximity Interrupt Threshold
} max30102Bit_e;






// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

/* NONE */

// =============================================================================
// Global variables
// =============================================================================

/* NONE */

// =============================================================================
// Class constructors
// =============================================================================

/* adsadas */

#define CASA 34

char teste[] = "oie sadsa\n";
int t = CASA;

Max30102::Max30102(uint32_t clockSpeed)
{
	this->clockSpeed_ = clockSpeed;
	this->shutDownControl_ = false;
}

// =============================================================================
// Class public methods
// =============================================================================

bool Max30102::init(max30102SensorSampleRate_e sensorSampleRate,
					max30102SensorResolution_e sensorResolution,
					max30102SensorFullScale_e sensorFullScale)
{
	uint8_t auxBuff[2];

	twiSetClock(this->clockSpeed_);
	this->readDeviceInfo_();
	if (this->partId_ != MAX30102_PART_ID) {
		this->lastError_ = MAX30102_WRONG_PART_ID;
		return false;
	}

	this->sensorResolution_ = sensorResolution;
	this->sensorSampleRate_ = sensorSampleRate;
	this->sensorFullScale_ = sensorFullScale;
	auxBuff[0] = MAX30102_REG_SPO2_CONFIGURATION;
	auxBuff[1] = (sensorResolution << MAX30102_BIT_CONFIGURATION_SENSOR_RESOLUTION)
				 |
				 (sensorSampleRate << MAX30102_BIT_CONFIGURATION_SENSOR_SAMPLE_RATE) |
				 (sensorFullScale << MAX30102_BIT_CONFIGURATION_SENSOR_FULL_SCALE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	this->lastError_ = MAX30102_ERROR_NONE;
	return true;
}

bool Max30102::reset(void)
{
	uint8_t auxBuff[2];

	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (1 << MAX30102_BIT_CONFIGURATION_RESET);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

// TODO reset all data members
	return true;
}

bool Max30102::shutDown(void)
{
	uint8_t auxBuff[2];

	this->shutDownControl_ = true;
	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (this->shutDownControl_ << MAX30102_BIT_CONFIGURATION_SHDN) |
				 (this->modeControl_ << MAX30102_BIT_CONFIGURATION_MODE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	return true;
}

bool Max30102::wakeUp(void)
{
	uint8_t auxBuff[2];

	this->shutDownControl_ = false;
	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (this->shutDownControl_ << MAX30102_BIT_CONFIGURATION_SHDN) |
				 (this->modeControl_ << MAX30102_BIT_CONFIGURATION_MODE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	return true;
}

bool Max30102::setHeartRateMode(max30102LedCurrent_e redLedCurrent)
{
	uint8_t auxBuff[2];

	this->modeControl_ = MAX30102_HEART_RATE_MODE;
	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (this->shutDownControl_ << MAX30102_BIT_CONFIGURATION_SHDN) |
				 (this->modeControl_ << MAX30102_BIT_CONFIGURATION_MODE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	this->redLedCurrent = redLedCurrent;
	auxBuff[0] = MAX30102_REG_LED1_PULSE_AMPLITUDE;
	auxBuff[1] = redLedCurrent;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	return true;
}

bool Max30102::setSpo2Mode(max30102LedCurrent_e redLedCurrent,
						   max30102LedCurrent_e infraredLedCurrent)
{
	uint8_t auxBuff[3];

	max30102LedCurrent_e casa;


	this->modeControl_ = MAX30102_SPO2_MODE;
	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (this->shutDownControl_ << MAX30102_BIT_CONFIGURATION_SHDN) |
				 (this->modeControl_ << MAX30102_BIT_CONFIGURATION_MODE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	this->redLedCurrent = redLedCurrent;
	this->infraredLedCurrent = infraredLedCurrent;
	auxBuff[0] = MAX30102_REG_LED1_PULSE_AMPLITUDE;
	auxBuff[1] = redLedCurrent;
	auxBuff[2] = infraredLedCurrent;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 3);

	return true;
}

bool Max30102::setCustomMode(max30102LedCurrent_e redLedCurrent,
							 max30102LedCurrent_e infraredLedCurrent, max30102LedCurrent_e auxLedCurrent)
{
	uint8_t auxBuff[3];

	this->modeControl_ = MAX30102_MULTI_LED_MODE;
	auxBuff[0] = MAX30102_REG_MODE_CONFIGURATION;
	auxBuff[1] = (this->shutDownControl_ << MAX30102_BIT_CONFIGURATION_SHDN) |
				 (this->modeControl_ << MAX30102_BIT_CONFIGURATION_MODE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	this->redLedCurrent = redLedCurrent;
	this->infraredLedCurrent = infraredLedCurrent;
	auxBuff[0] = MAX30102_REG_LED1_PULSE_AMPLITUDE;
	auxBuff[1] = redLedCurrent;
	auxBuff[2] = infraredLedCurrent;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 3);

	this->auxLedCurrent = auxLedCurrent;
	auxBuff[0] = MAX30102_REG_PROXIMITY_LED_AMPLITUDE;
	auxBuff[1] = auxLedCurrent;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	return true;
}

// TODO Slots

bool Max30102::fifoConfig(max30102FifoAveraging_e averages, bool overflow,
						  uint8_t remainingSpace)
{
	uint8_t auxBuff[2];

	this->fifoAveraging_ = averages;
	this->fifoOverflowEnable_ = overflow;
	this->fifoInterruptRemainingSpace_ = remainingSpace;

	auxBuff[0] = MAX30102_REG_FIFO_CONFIGURATION;
	auxBuff[1] = (this->fifoAveraging_ << MAX30102_BIT_CONFIGURATION_SMP_AVE) |
				 (this->fifoOverflowEnable_ << MAX30102_BIT_CONFIGURATION_FIFO_ROLLOVER_EN) |
				 (this->fifoInterruptRemainingSpace_ << MAX30102_BIT_CONFIGURATION_FIFO_A_FULL);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 2);

	return true;
}

bool Max30102::activateInterrupts(max30102InterruptFlags_f activationMask)
{
	uint8_t auxBuff[3];

	if (activationMask & MAX30102_INTERRUPT_FIFO_ALMOST_FULL) {
		this->fifoAlmostFullEnable_ = true;
	}
	if (activationMask & MAX30102_INTERRUPT_FIFO_NEW_DATA) {
		this->fifoNewDataEnable_ = true;
	}
	if (activationMask & MAX30102_INTERRUPT_AMBIENT_LIGHT_CANC) {
		this->ambientLightCancelationEnable_ = true;
	}
	if (activationMask & MAX30102_INTERRUPT_PROXIMITY) {
		this->proximityThresholdEnable_ = true;
	}
	if (activationMask & MAX30102_INTERRUPT_DIE_TEMPERATURE) {
		this->dieTemperatureEnable_ = true;
	}

	auxBuff[0] = MAX30102_REG_INTERRUPT_ENABLE_1;
	auxBuff[1] = (this->fifoAlmostFullEnable_ <<
				  MAX30102_BIT_INTERRUPT_FIFO_ALMOST_FULL_ENABLE) |
				 (this->fifoNewDataEnable_ << MAX30102_BIT_INTERRUPT_FIFO_NEW_DATA_READY_ENABLE)
				 |
				 (this->ambientLightCancelationEnable_ <<
				  MAX30102_BIT_INTERRUPT_AMBIENT_LIGHT_CANC_ENABLE) |
				 (this->proximityThresholdEnable_ <<
				  MAX30102_BIT_INTERRUPT_PROXIMITY_THRESHOLD_ENABLE);
	auxBuff[2] = (this->dieTemperatureEnable_ <<
				  MAX30102_BIT_INTERRUPT_DIE_TEMPERATURE_READY_ENABLE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 3);

	return true;
}

bool Max30102::deactivateInterrupts(max30102InterruptFlags_f deactivationMask)
{
	uint8_t auxBuff[3];

	if (deactivationMask & MAX30102_INTERRUPT_FIFO_ALMOST_FULL) {
		this->fifoAlmostFullEnable_ = false;
	}
	if (deactivationMask & MAX30102_INTERRUPT_FIFO_NEW_DATA) {
		this->fifoNewDataEnable_ = false;
	}
	if (deactivationMask & MAX30102_INTERRUPT_AMBIENT_LIGHT_CANC) {
		this->ambientLightCancelationEnable_ = false;
	}
	if (deactivationMask & MAX30102_INTERRUPT_PROXIMITY) {
		this->proximityThresholdEnable_ = false;
	}
	if (deactivationMask & MAX30102_INTERRUPT_DIE_TEMPERATURE) {
		this->dieTemperatureEnable_ = false;
	}

	auxBuff[0] = MAX30102_REG_INTERRUPT_ENABLE_1;
	auxBuff[1] = (this->fifoAlmostFullEnable_ <<
				  MAX30102_BIT_INTERRUPT_FIFO_ALMOST_FULL_ENABLE) |
				 (this->fifoNewDataEnable_ << MAX30102_BIT_INTERRUPT_FIFO_NEW_DATA_READY_ENABLE)
				 |
				 (this->ambientLightCancelationEnable_ <<
				  MAX30102_BIT_INTERRUPT_AMBIENT_LIGHT_CANC_ENABLE) |
				 (this->proximityThresholdEnable_ <<
				  MAX30102_BIT_INTERRUPT_PROXIMITY_THRESHOLD_ENABLE);
	auxBuff[2] = (this->dieTemperatureEnable_ <<
				  MAX30102_BIT_INTERRUPT_DIE_TEMPERATURE_READY_ENABLE);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 3);

	return true;
}

bool Max30102::getInterruptStatus(max30102InterruptFlags_f interrupt,
								  bool refreshStatus)
{
	bool status = false;

	if (refreshStatus) {
		uint8_t auxBuff[2];

		auxBuff[0] = MAX30102_REG_INTERRUPT_STATUS_1;
		twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 1);
		twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, 2);
		this->fifoAlmostFullFlag_ = (auxBuff[0] &
									 MAX30102_BIT_INTERRUPT_FIFO_ALMOST_FULL_FLAG);
		this->fifoNewDataFlag_ = (auxBuff[0] &
								  MAX30102_BIT_INTERRUPT_FIFO_NEW_DATA_READY_FLAG);
		this->ambientLightCancelationFlag_ = (auxBuff[0] &
											  MAX30102_BIT_INTERRUPT_AMBIENT_LIGHT_CANC_FLAG);
		this->proximityThresholdFlag_ = (auxBuff[0] &
										 MAX30102_BIT_INTERRUPT_PROXIMITY_THRESHOLD_FLAG);
		this->powerReadyFlag_ = (auxBuff[0] & MAX30102_BIT_INTERRUPT_POWER_READY_FLAG);
		this->dieTemperatureFlag_ = (auxBuff[1] &
									 MAX30102_BIT_INTERRUPT_DIE_TEMPERATURE_READY_FLAG);
	}

	if (interrupt & MAX30102_INTERRUPT_FIFO_ALMOST_FULL) {
		status |= this->fifoAlmostFullFlag_;
	}
	if (interrupt & MAX30102_INTERRUPT_FIFO_NEW_DATA) {
		status |= this->fifoNewDataFlag_;
	}
	if (interrupt & MAX30102_INTERRUPT_AMBIENT_LIGHT_CANC) {
		status |= this->ambientLightCancelationFlag_;
	}
	if (interrupt & MAX30102_INTERRUPT_PROXIMITY) {
		status |= this->proximityThresholdFlag_;
	}
	if (interrupt & MAX30102_INTERRUPT_DIE_TEMPERATURE) {
		status |= this->dieTemperatureFlag_;
	}
	if (interrupt & MAX30102_INTERRUPT_POWER_READY) {
		status |= this->powerReadyFlag_;
	}

	return status;
}

bool Max30102::flushFifo(void)
{
	uint8_t auxBuff[4];

	this->fifoWritePointer_ = 0;
	this->fifoOverflowCounter_ = 0;
	this->fifoReadPointer_ = 0;

	auxBuff[0] = MAX30102_REG_FIFO_WRITE_POINTER;
	auxBuff[1] = 0;
	auxBuff[2] = 0;
	auxBuff[3] = 0;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 4);

	return true;
}

bool Max30102::getFifoOccupation(uint8_t *samplesWaiting, uint8_t *samplesLost)
{
	uint8_t aux8;
	this->getFifoInfo_();

	if (this->fifoWritePointer_ >= this->fifoReadPointer_) {
		aux8 = this->fifoWritePointer_;
		aux8 -= this->fifoReadPointer_;
	} else {
		aux8 = MAX30102_FIFO_SIZE_IN_SAMPLES;
		aux8 += this->fifoWritePointer_;
		aux8 -= this->fifoReadPointer_;
	}
	*samplesWaiting = aux8;
	if (samplesLost != NULL) {
		*samplesLost = this->fifoOverflowCounter_;
	}

	return true;
}

bool Max30102::getFifoData(uint8_t samplesCount, uint16_t *redLedBuffer,
						   uint16_t *infraredLedBuffer)
{
	// TODO Check for errors
	readFifoData_(samplesCount, redLedBuffer, infraredLedBuffer, sizeof(uint16_t));
	return true;
}

bool Max30102::getFifoData(uint8_t samplesCount, uint32_t *redLedBuffer,
						   uint32_t *infraredLedBuffer)
{
	// TODO Check for errors
	readFifoData_(samplesCount, redLedBuffer, infraredLedBuffer, sizeof(uint32_t));
	return true;
}

bool Max30102::getNewestSample(uint16_t *redValue, uint16_t *infraredValue)
{
	uint8_t samples;
	uint16_t *auxBuff1 = NULL;
	uint16_t *auxBuff2 = NULL;

	this->getFifoOccupation(&samples);

	if (samples == 0) {
		return false;
	}
	auxBuff1 = (uint16_t *)calloc(samples, sizeof(uint16_t));
	if (auxBuff1 == NULL) {
		return false;
	}
	if (infraredValue != NULL) {
		auxBuff2 = (uint16_t *)calloc(samples, sizeof(uint16_t));
		if (auxBuff2 == NULL) {
			free(auxBuff1);
			return false;
		}
	}

	if (infraredValue == NULL) {
		readFifoData_(samples, auxBuff1, NULL, sizeof(uint16_t));
		*redValue = auxBuff1[samples - 1];
	} else {
		readFifoData_(samples, auxBuff1, auxBuff2, sizeof(uint16_t));
		*redValue = auxBuff1[samples - 1];
		*infraredValue = auxBuff2[samples - 1];
	}

	free(auxBuff1);
	if (auxBuff2 != NULL) {
		free(auxBuff2);
	}

	return true;
}

bool Max30102::getNewestSample(uint32_t *redValue, uint32_t *infraredValue)
{
	return true;
}



/*
//Report the most recent red value
	uint32_t Max30102::getRed(void) {
		//Check the sensor for new data for 250ms
		if (safeCheck(250))
		{ return (sense.red[sense.head]); }
		else
		{ return (0); } //Sensor failed to find new data
	}

//Report the most recent IR value
	uint32_t Max30102::getIR(void) {
		//Check the sensor for new data for 250ms
		if (safeCheck(250))
		{ return (sense.IR[sense.head]); }
		else
		{ return (0); } //Sensor failed to find new data
	}

//Report the most recent Green value
	uint32_t Max30102::getGreen(void) {
		//Check the sensor for new data for 250ms
		if (safeCheck(250))
		{ return (sense.green[sense.head]); }
		else
		{ return (0); } //Sensor failed to find new data
	}

//Report the next Red value in the FIFO
	uint32_t Max30102::getFIFORed(void) {
		return (sense.red[sense.tail]);
	}

//Report the next IR value in the FIFO
	uint32_t Max30102::getFIFOIR(void) {
		return (sense.IR[sense.tail]);
	}

//Report the next Green value in the FIFO
	uint32_t Max30102::getFIFOGreen(void) {
		return (sense.green[sense.tail]);
	}

//Advance the tail
	void Max30102::nextSample(void) {
		if (available()) { //Only advance the tail if new data is available
			sense.tail++;
			sense.tail %= STORAGE_SIZE; //Wrap condition
		}
	}


//Polls the sensor for new data
//Call regularly
//If new data is available, it updates the head and tail in the main struct
//Returns number of new samples obtained
	uint16_t Max30102::check(void) {
		//Read register FIDO_DATA in (3-byte * number of active LED) chunks
		//Until FIFO_RD_PTR = FIFO_WR_PTR

		byte readPointer = getReadPointer();
		byte writePointer = getWritePointer();

		int numberOfSamples = 0;

		//Do we have new data?
		if (readPointer != writePointer) {
			//Calculate the number of readings we need to get from sensor
			numberOfSamples = writePointer - readPointer;
			if (numberOfSamples < 0) { numberOfSamples += 32; } //Wrap condition

			//We now have the number of readings, now calc bytes to read
			//For this example we are just doing Red and IR (3 bytes each)
			int bytesLeftToRead = numberOfSamples * activeLEDs * 3;

			//Get ready to read a burst of data from the FIFO register
			_i2cPort->beginTransmission(Max30102_ADDRESS);
			_i2cPort->write(Max30102_FIFODATA);
			_i2cPort->endTransmission();

			//We may need to read as many as 288 bytes so we read in blocks no larger than I2C_BUFFER_LENGTH
			//I2C_BUFFER_LENGTH changes based on the platform. 64 bytes for SAMD21, 32 bytes for Uno.
			//Wire.requestFrom() is limited to BUFFER_LENGTH which is 32 on the Uno
			while (bytesLeftToRead > 0) {
				int toGet = bytesLeftToRead;
				if (toGet > I2C_BUFFER_LENGTH) {
					//If toGet is 32 this is bad because we read 6 bytes (Red+IR * 3 = 6) at a time
					//32 % 6 = 2 left over. We don't want to request 32 bytes, we want to request 30.
					//32 % 9 (Red+IR+GREEN) = 5 left over. We want to request 27.

					toGet = I2C_BUFFER_LENGTH - (I2C_BUFFER_LENGTH % (activeLEDs * 3)); //Trim toGet to be a multiple of the samples we need to read
				}

				bytesLeftToRead -= toGet;

				//Request toGet number of bytes from sensor
				_i2cPort->requestFrom(Max30102_ADDRESS, toGet);

				while (toGet > 0) {
					sense.head++; //Advance the head of the storage struct
					sense.head %= STORAGE_SIZE; //Wrap condition

					byte temp[sizeof(uint32_t)]; //Array of 4 bytes that we will convert into long
					uint32_t tempLong;

					//Burst read three bytes - RED
					temp[3] = 0;
					temp[2] = _i2cPort->read();
					temp[1] = _i2cPort->read();
					temp[0] = _i2cPort->read();

					//Convert array to long
					memcpy(&tempLong, temp, sizeof(tempLong));

					tempLong &= 0x3FFFF; //Zero out all but 18 bits

					sense.red[sense.head] = tempLong; //Store this reading into the sense array

					if (activeLEDs > 1) {
						//Burst read three more bytes - IR
						temp[3] = 0;
						temp[2] = _i2cPort->read();
						temp[1] = _i2cPort->read();
						temp[0] = _i2cPort->read();

						//Convert array to long
						memcpy(&tempLong, temp, sizeof(tempLong));

						tempLong &= 0x3FFFF; //Zero out all but 18 bits

						sense.IR[sense.head] = tempLong;
					}

					if (activeLEDs > 2) {
						//Burst read three more bytes - Green
						temp[3] = 0;
						temp[2] = _i2cPort->read();
						temp[1] = _i2cPort->read();
						temp[0] = _i2cPort->read();

						//Convert array to long
						memcpy(&tempLong, temp, sizeof(tempLong));

						tempLong &= 0x3FFFF; //Zero out all but 18 bits

						sense.green[sense.head] = tempLong;
					}

					toGet -= activeLEDs * 3;
				}

			} //End while (bytesLeftToRead > 0)

		} //End readPtr != writePtr

		return (numberOfSamples); //Let the world know how much new data we found
	}

//Check for new data but give up after a certain amount of time
//Returns true if new data was found
//Returns false if new data was not found
	bool Max30102::safeCheck(uint8_t maxTimeToCheck) {
		uint32_t markTime = millis();

		while (1) {
			if (millis() - markTime > maxTimeToCheck) { return (false); }

			if (check() == true) //We found new data!
			{ return (true); }

			delay(1);
		}
	}

*/






// =============================================================================
// Class private methods
// =============================================================================

bool Max30102::readDeviceInfo_(void)
{
	uint8_t auxBuff[2];

	auxBuff[0] = MAX30102_REG_REVISION_ID;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 1);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, 2);
	this->revisionId_ = auxBuff[0];
	this->partId_ = auxBuff[1];

	return true;
}

bool Max30102::getFifoInfo_(void)
{
	uint8_t auxBuff[3];

	auxBuff[0] = MAX30102_REG_FIFO_WRITE_POINTER;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 1);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, 3);

	this->fifoWritePointer_ = auxBuff[0];
	this->fifoOverflowCounter_ = auxBuff[1];
	this->fifoReadPointer_ = auxBuff[2];

	return true;
}

bool Max30102::readFifoData_(uint8_t nSamples, void *buff1, void *buff2,
							 uint8_t varSize)
{
	uint8_t *auxBuff = NULL;
	uint8_t aux8 = 0;
	uint16_t aux16 = 0;
	int32_t aux32 = 0;
	uint16_t *buff16ptr1 = (uint16_t *)buff1;
	uint16_t *buff16ptr2 = (uint16_t *)buff2;
	uint32_t *buff32ptr1 = (uint32_t *)buff1;
	uint32_t *buff32ptr2 = (uint32_t *)buff2;

	// Set device's register address pointer
	aux8 = MAX30102_REG_FIFO_DATA;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, &aux8, 1);

	// Evaluate buffer size
	switch (this->modeControl_) {
	case MAX30102_HEART_RATE_MODE:
		aux16 = MAX30102_BYTES_PER_CHANNEL * nSamples * 1;
		break;
	case MAX30102_SPO2_MODE:
		aux16 = MAX30102_BYTES_PER_CHANNEL * nSamples * 2;
		break;
	case MAX30102_MULTI_LED_MODE:
		aux16 = MAX30102_BYTES_PER_CHANNEL * nSamples * this->enabledSlotsCounter_;
		break;
	default:
		break;
	}

	// Memory allocation
	auxBuff = (uint8_t *)calloc(aux16, sizeof(uint8_t));
	if (auxBuff == NULL) {
		return false;
	}

	// Read data
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, aux16);

	// Evaluate resolution fix
	switch (this->sensorResolution_) {
	case MAX30102_SENSOR_RESOLUTION_15_BITS:
		aux8 = 3;
		break;
	case MAX30102_SENSOR_RESOLUTION_16_BITS:
		aux8 = 2;
		break;
	case MAX30102_SENSOR_RESOLUTION_17_BITS:
		aux8 = 1;
		break;
	case MAX30102_SENSOR_RESOLUTION_18_BITS:
		aux8 = 0;
		break;
	default:
		free(auxBuff);
		return false;
	}

	// Decode data
	aux8 = 0;	////////////////////////////////////////
	aux16 = 0;
	for (uint8_t i = 0; i < nSamples; i++) {
		switch (this->modeControl_) {

		case MAX30102_HEART_RATE_MODE:
			aux32 = (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			if (varSize == 2) {
				*buff16ptr1++ = (uint16_t)(aux32 >> aux8);
			} else {
				*buff32ptr1++ = (aux32 >> aux8);
			}
			break;

		case MAX30102_SPO2_MODE:
			aux32 = (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			if (varSize == 2) {
				*buff16ptr1++ = (uint16_t)(aux32 >> aux8);
			} else {
				*buff32ptr1++ = (aux32 >> aux8);
			}
			aux32 = (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			aux32 <<= 8;
			aux32 |= (uint32_t)(auxBuff[aux16++]);
			if (varSize == 2) {
				*buff16ptr2++ = (uint16_t)(aux32 >> aux8);
			} else {
				*buff32ptr2++ = (aux32 >> aux8);
			}
			break;

		case MAX30102_MULTI_LED_MODE:
			// TODO
			break;
		}
	}
	free(auxBuff);

	// Update data members
	this->getFifoInfo_();

	return true;
}
/*
bool Max30102::readNewestSample_(void *redValue, void *infraredValue, uint8_t varSize)
{
	uint8_t samples;

	this->getFifoOccupation(&samples);

	if (samples == 0) {
		return false;
	}

	if (varSize == sizeof(uint16_t)) {

		// Local variables
		uint16_t *auxBuff1 = NULL;
		uint16_t *auxBuff2 = NULL;

		// Red LED memory allocation
		auxBuff1 = (uint16_t *)calloc(samples, sizeof(uint16_t));
		if (auxBuff1 == NULL) {
			return false;
		}

		// Infrared LED memory allocation
		if (infraredValue != NULL) {
			auxBuff2 = (uint16_t *)calloc(samples, sizeof(uint16_t));
			if (auxBuff2 == NULL) {
				free(auxBuff1);
				return false;
			}
		}

		// Retrieve FIFO data
		if (infraredValue == NULL) {
			readFifoData_(samples, auxBuff1, NULL, sizeof(uint16_t));
			(uint16_t *)*redValue = auxBuff1[samples - 1];
		} else {
			readFifoData_(samples, auxBuff1, auxBuff2, sizeof(uint16_t));
			*redValue = auxBuff1[samples - 1];
			*infraredValue = auxBuff2[samples - 1];
		}
		free(auxBuff1);
		if (auxBuff2 != NULL) {
			free(auxBuff2);
		}

	} else if (varSize == sizeof(uint32_t)) {
		uint32_t *auxBuff1 = NULL;
		uint32_t *auxBuff2 = NULL;
	} else {

	}
	return true;
}
*/


// =============================================================================
// Class protected methods
// =============================================================================

/* NONE */

// =============================================================================
// General public functions definitions
// =============================================================================

/* NONE */

// =============================================================================
// Public functions definitions
// =============================================================================

/* NONE */

























/*

//
// Configuration
//

void Max30102::softReset(void)
{
	bitMask(MAX30102_REG_MODECONFIG, MAX30102_REG_RESET_MASK, MAX30102_REG_RESET);

	// Poll for bit to clear, reset is then complete
	// Timeout after 100ms
	unsigned long startTime = millis();
	while (millis() - startTime < 100) {
		uint8_t response = readRegister8(_i2caddr, MAX30102_REG_MODECONFIG);
		if ((response & MAX30102_REG_RESET) == 0) { break; } //We're done!
		delay(1); //Let's not over burden the I2C bus
	}
}



void Max30102::setADCRange(uint8_t adcRange)
{
	// adcRange: one of MAX30102_REG_ADCRANGE_2048, _4096, _8192, _16384
	bitMask(MAX30102_REG_PARTICLECONFIG, MAX30102_REG_ADCRANGE_MASK, adcRange);
}

void Max30102::setSampleRate(uint8_t sampleRate)
{
	// sampleRate: one of MAX30102_REG_SAMPLERATE_50, _100, _200, _400, _800, _1000, _1600, _3200
	bitMask(MAX30102_REG_PARTICLECONFIG, MAX30102_REG_SAMPLERATE_MASK, sampleRate);
}

void Max30102::setPulseWidth(uint8_t pulseWidth)
{
	// pulseWidth: one of MAX30102_REG_PULSEWIDTH_69, _188, _215, _411
	bitMask(MAX30102_REG_PARTICLECONFIG, MAX30102_REG_PULSEWIDTH_MASK, pulseWidth);
}

void Max30102::setProximityThreshold(uint8_t threshMSB)
{
	// Set the IR ADC count that will trigger the beginning of particle-sensing mode.
	// The threshMSB signifies only the 8 most significant-bits of the ADC count.
	// See datasheet, page 24.
	writeRegister8(_i2caddr, MAX30102_REG_PROXINTTHRESH, threshMSB);
}

//Given a slot number assign a thing to it
//Devices are SLOT_RED_LED or SLOT_RED_PILOT (proximity)
//Assigning a SLOT_RED_LED will pulse LED
//Assigning a SLOT_RED_PILOT will ??
void Max30102::enableSlot(uint8_t slotNumber, uint8_t device)
{

	uint8_t originalContents;

	switch (slotNumber) {
	case (1):
		bitMask(MAX30102_REG_MULTILEDCONFIG1, MAX30102_REG_SLOT1_MASK, device);
		break;
	case (2):
		bitMask(MAX30102_REG_MULTILEDCONFIG1, MAX30102_REG_SLOT2_MASK, device << 4);
		break;
	case (3):
		bitMask(MAX30102_REG_MULTILEDCONFIG2, MAX30102_REG_SLOT3_MASK, device);
		break;
	case (4):
		bitMask(MAX30102_REG_MULTILEDCONFIG2, MAX30102_REG_SLOT4_MASK, device << 4);
		break;
	default:
		//Shouldn't be here!
		break;
	}
}

//Clears all slot assignments
void Max30102::disableSlots(void)
{
	writeRegister8(_i2caddr, MAX30102_REG_MULTILEDCONFIG1, 0);
	writeRegister8(_i2caddr, MAX30102_REG_MULTILEDCONFIG2, 0);
}

//
// FIFO Configuration
//


// Die Temperature
// Returns temp in C
float Max30102::readTemperature()
{
	// Step 1: Config die temperature register to take 1 temperature sample
	writeRegister8(_i2caddr, MAX30102_REG_DIETEMPCONFIG, 0x01);

	// Poll for bit to clear, reading is then complete
	// Timeout after 100ms
	unsigned long startTime = millis();
	while (millis() - startTime < 100) {
		uint8_t response = readRegister8(_i2caddr, MAX30102_REG_DIETEMPCONFIG);
		if ((response & 0x01) == 0) { break; } //We're done!
		delay(1); //Let's not over burden the I2C bus
	}
	//TODO How do we want to fail? With what type of error?
	//? if(millis() - startTime >= 100) return(-999.0);

	// Step 2: Read die temperature register (integer)
	int8_t tempInt = readRegister8(_i2caddr, MAX30102_REG_DIETEMPINT);
	uint8_t tempFrac = readRegister8(_i2caddr, MAX30102_REG_DIETEMPFRAC);

	// Step 3: Calculate temperature (datasheet pg. 23)
	return (float)tempInt + ((float)tempFrac * 0.0625);
}

// Returns die temp in F
float Max30102::readTemperatureF()
{
	float temp = readTemperature();

	if (temp != -999.0) { temp = temp * 1.8 + 32.0; }

	return (temp);
}

// Set the PROX_INT_THRESHold
void Max30102::setPROXINTTHRESH(uint8_t val)
{
	writeRegister8(_i2caddr, MAX30102_REG_PROXINTTHRESH, val);
}

//Setup the sensor
//The Max30102 has many settings. By default we select:
// Sample Average = 4
// Mode = MultiLED
// ADC Range = 16384 (62.5pA per LSB)
// Sample rate = 50
//Use the default setup if you are just getting started with the Max30102 sensor
void Max30102::setup(uint8_t powerLevel, uint8_t sampleAverage, uint8_t ledMode, int sampleRate, int pulseWidth, int adcRange)
{
	softReset(); //Reset all configuration, threshold, and data registers to POR values

	//FIFO Configuration
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//The chip will average multiple samples of same type together if you wish
	if (sampleAverage == 1) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_1); } //No averaging per FIFO record
	else if (sampleAverage == 2) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_2); }
	else if (sampleAverage == 4) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_4); }
	else if (sampleAverage == 8) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_8); }
	else if (sampleAverage == 16) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_16); }
	else if (sampleAverage == 32) { setFIFOAverage(MAX30102_REG_SAMPLEAVG_32); }
	else { setFIFOAverage(MAX30102_REG_SAMPLEAVG_4); }

	//setFIFOAlmostFull(2); //Set to 30 samples to trigger an 'Almost Full' interrupt
	enableFIFORollover(); //Allow FIFO to wrap/roll over
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	//Mode Configuration
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	if (ledMode == 3) { setLEDMode(MAX30102_REG_MODE_MULTILED); } //Watch all three LED channels
	else if (ledMode == 2) { setLEDMode(MAX30102_REG_MODE_REDIRONLY); } //Red and IR
	else { setLEDMode(MAX30102_REG_MODE_REDONLY); } //Red only
	activeLEDs = ledMode; //Used to control how many uint8_ts to read from FIFO buffer
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	//Particle Sensing Configuration
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	if (adcRange < 4096) { setADCRange(MAX30102_REG_ADCRANGE_2048); } //7.81pA per LSB
	else if (adcRange < 8192) { setADCRange(MAX30102_REG_ADCRANGE_4096); } //15.63pA per LSB
	else if (adcRange < 16384) { setADCRange(MAX30102_REG_ADCRANGE_8192); } //31.25pA per LSB
	else if (adcRange == 16384) { setADCRange(MAX30102_REG_ADCRANGE_16384); } //62.5pA per LSB
	else { setADCRange(MAX30102_REG_ADCRANGE_2048); }

	if (sampleRate < 100) { setSampleRate(MAX30102_REG_SAMPLERATE_50); } //Take 50 samples per second
	else if (sampleRate < 200) { setSampleRate(MAX30102_REG_SAMPLERATE_100); }
	else if (sampleRate < 400) { setSampleRate(MAX30102_REG_SAMPLERATE_200); }
	else if (sampleRate < 800) { setSampleRate(MAX30102_REG_SAMPLERATE_400); }
	else if (sampleRate < 1000) { setSampleRate(MAX30102_REG_SAMPLERATE_800); }
	else if (sampleRate < 1600) { setSampleRate(MAX30102_REG_SAMPLERATE_1000); }
	else if (sampleRate < 3200) { setSampleRate(MAX30102_REG_SAMPLERATE_1600); }
	else if (sampleRate == 3200) { setSampleRate(MAX30102_REG_SAMPLERATE_3200); }
	else { setSampleRate(MAX30102_REG_SAMPLERATE_50); }

	//The longer the pulse width the longer range of detection you'll have
	//At 69us and 0.4mA it's about 2 inches
	//At 411us and 0.4mA it's about 6 inches
	if (pulseWidth < 118) { setPulseWidth(MAX30102_REG_PULSEWIDTH_69); } //Page 26, Gets us 15 bit resolution
	else if (pulseWidth < 215) { setPulseWidth(MAX30102_REG_PULSEWIDTH_118); } //16 bit resolution
	else if (pulseWidth < 411) { setPulseWidth(MAX30102_REG_PULSEWIDTH_215); } //17 bit resolution
	else if (pulseWidth == 411) { setPulseWidth(MAX30102_REG_PULSEWIDTH_411); } //18 bit resolution
	else { setPulseWidth(MAX30102_REG_PULSEWIDTH_69); }
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	//LED Pulse Amplitude Configuration
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//Default is 0x1F which gets us 6.4mA
	//powerLevel = 0x02, 0.4mA - Presence detection of ~4 inch
	//powerLevel = 0x1F, 6.4mA - Presence detection of ~8 inch
	//powerLevel = 0x7F, 25.4mA - Presence detection of ~8 inch
	//powerLevel = 0xFF, 50.0mA - Presence detection of ~12 inch

	setPulseAmplitudeRed(powerLevel);
	setPulseAmplitudeIR(powerLevel);
	setPulseAmplitudeGreen(powerLevel);
	setPulseAmplitudeProximity(powerLevel);
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	//Multi-LED Mode Configuration, Enable the reading of the three LEDs
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	enableSlot(1, SLOT_RED_LED);
	if (ledMode > 1) { enableSlot(2, SLOT_IR_LED); }
	if (ledMode > 2) { enableSlot(3, SLOT_GREEN_LED); }
	//enableSlot(1, SLOT_RED_PILOT);
	//enableSlot(2, SLOT_IR_PILOT);
	//enableSlot(3, SLOT_GREEN_PILOT);
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	clearFIFO(); //Reset the FIFO before we begin checking the sensor
}

//
// Data Collection
//

//Given a register, read it, mask it, and then set the thing
void Max30102::bitMask(uint8_t reg, uint8_t mask, uint8_t thing)
{
	// Grab current register context
	uint8_t originalContents = readRegister8(_i2caddr, reg);

	// Zero-out the portions of the register we're interested in
	originalContents = originalContents & mask;

	// Change contents
	writeRegister8(_i2caddr, reg, originalContents | thing);
}

//
// Low-level I2C Communication
//
uint8_t Max30102::readRegister8(uint8_t address, uint8_t reg)
{
	_i2cPort->beginTransmission(address);
	_i2cPort->write(reg);
	_i2cPort->endTransmission(false);

	_i2cPort->requestFrom((uint8_t)address, (uint8_t)1); // Request 1 uint8_t
	if (_i2cPort->available()) {
		return (_i2cPort->read());
	}

	return (0); //Fail

}

void Max30102::writeRegister8(uint8_t address, uint8_t reg, uint8_t value)
{
	_i2cPort->beginTransmission(address);
	_i2cPort->write(reg);
	_i2cPort->write(value);
	_i2cPort->endTransmission();
}
*/


uint8_t Max30102::getReadPointer()
{
	uint8_t auxBuff[2];

	auxBuff[0] = MAX30102_REG_FIFO_READ_POINTER;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 1);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, 1);

	return auxBuff[0];
}

uint8_t Max30102::getWritePointer()
{
	uint8_t auxBuff[2];

	auxBuff[0] = MAX30102_REG_FIFO_WRITE_POINTER;
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_WRITE, auxBuff, 1);
	twi.sendData(MAX30102_DEVICE_ADDRESS, TWI_READ, auxBuff, 1);

	return auxBuff[0];
}

