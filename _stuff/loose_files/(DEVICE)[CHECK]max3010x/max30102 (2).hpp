/* =============================================================================
 * Project:		GPSDE++ AVR Library
 * File name:	max30102.hpp
 * Module:		MAX30102 module interface for GPDSE++ Library project
 * Authors:		Leandro Schwarz
 *				Hazael dos Santos Batista
 * Build:		1002
 * Date:		June 14, 2018
 * ========================================================================== */

#ifndef __MAX30102_HPP
#define __MAX30102_HPP 1002

// =============================================================================
// Dependencies
// =============================================================================

// Global definitions file
#include "..\globalDefines.hpp"
#if __GLOBAL_DEFINES_HPP != 1002
#	error	[max30102.hpp] Error 101 - Global definitions file (globalDefines.hpp) must be build 1002.
#endif

#include <stdint.h>
// Header files
#include "..\twiMaster.hpp"

// =============================================================================
// Undefining previous definitions
// =============================================================================

/* NONE */

// =============================================================================
// Constants
// =============================================================================

/* NONE */
#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000
#define I2C_BUFFER_LENGTH         32

// =============================================================================
// Macro-functions
// =============================================================================

/* NONE */

// =============================================================================
// New data types
// =============================================================================

typedef enum max30102Error_e {
	MAX30102_ERROR_NONE		= 0,
	MAX30102_NOT_INITIALIZED,
	MAX30102_WRONG_PART_ID,
} max30102Error_e;

typedef enum max30102ModeControl_e {
	MAX30102_HEART_RATE_MODE	= 2,
	MAX30102_SPO2_MODE			= 3,
	MAX30102_MULTI_LED_MODE		= 7
} max30102ModeControl_e;

typedef enum max30102FifoAveraging_e {
	MAX30102_FIFO_NO_AVERAGE	= 0,
	MAX30102_FIFO_AVERAGE_2		= 1,
	MAX30102_FIFO_AVERAGE_4		= 2,
	MAX30102_FIFO_AVERAGE_8		= 3,
	MAX30102_FIFO_AVERAGE_16	= 4,
	MAX30102_FIFO_AVERAGE_32	= 5,
} max30102FifoAveraging_e;

typedef enum max30102LedCurrent_e {
	MAX30102_LED_OFF				= 0,
	MAX30102_LED_CURRENT_200_UA		= 1,
	MAX30102_LED_CURRENT_400_UA		= 2,
	MAX30102_LED_CURRENT_800_UA		= 4,
	MAX30102_LED_CURRENT_1_MA		= 5,
	MAX30102_LED_CURRENT_2_MA		= 10,
	MAX30102_LED_CURRENT_3_MA		= 15,
	MAX30102_LED_CURRENT_4_MA		= 20,
	MAX30102_LED_CURRENT_5_MA		= 26,
	MAX30102_LED_CURRENT_6_MA		= 31,
	MAX30102_LED_CURRENT_7_MA		= 36,
	MAX30102_LED_CURRENT_8_MA		= 41,
	MAX30102_LED_CURRENT_9_MA		= 46,
	MAX30102_LED_CURRENT_10_MA		= 51,
	MAX30102_LED_CURRENT_11_MA		= 56,
	MAX30102_LED_CURRENT_12_MA		= 61,
	MAX30102_LED_CURRENT_13_MA		= 66,
	MAX30102_LED_CURRENT_14_MA		= 71,
	MAX30102_LED_CURRENT_15_MA		= 77,
	MAX30102_LED_CURRENT_16_MA		= 82,
	MAX30102_LED_CURRENT_17_MA		= 87,
	MAX30102_LED_CURRENT_18_MA		= 92,
	MAX30102_LED_CURRENT_19_MA		= 96,
	MAX30102_LED_CURRENT_20_MA		= 102,
	MAX30102_LED_CURRENT_21_MA		= 107,
	MAX30102_LED_CURRENT_22_MA		= 112,
	MAX30102_LED_CURRENT_23_MA		= 117,
	MAX30102_LED_CURRENT_24_MA		= 122,
	MAX30102_LED_CURRENT_25_MA		= 128,
	MAX30102_LED_CURRENT_26_MA		= 133,
	MAX30102_LED_CURRENT_27_MA		= 138,
	MAX30102_LED_CURRENT_28_MA		= 143,
	MAX30102_LED_CURRENT_29_MA		= 148,
	MAX30102_LED_CURRENT_30_MA		= 153,
	MAX30102_LED_CURRENT_31_MA		= 158,
	MAX30102_LED_CURRENT_32_MA		= 163,
	MAX30102_LED_CURRENT_33_MA		= 168,
	MAX30102_LED_CURRENT_34_MA		= 173,
	MAX30102_LED_CURRENT_35_MA		= 179,
	MAX30102_LED_CURRENT_36_MA		= 184,
	MAX30102_LED_CURRENT_37_MA		= 189,
	MAX30102_LED_CURRENT_38_MA		= 194,
	MAX30102_LED_CURRENT_39_MA		= 199,
	MAX30102_LED_CURRENT_40_MA		= 204,
	MAX30102_LED_CURRENT_41_MA		= 209,
	MAX30102_LED_CURRENT_42_MA		= 214,
	MAX30102_LED_CURRENT_43_MA		= 219,
	MAX30102_LED_CURRENT_44_MA		= 224,
	MAX30102_LED_CURRENT_45_MA		= 230,
	MAX30102_LED_CURRENT_46_MA		= 235,
	MAX30102_LED_CURRENT_47_MA		= 240,
	MAX30102_LED_CURRENT_48_MA		= 245,
	MAX30102_LED_CURRENT_49_MA		= 250,
	MAX30102_LED_CURRENT_50_MA		= 255
} max30102LedCurrent_e;

typedef enum max30102InterruptFlags_f {
	MAX30102_INTERRUPT_FIFO_ALMOST_FULL		= 1,
	MAX30102_INTERRUPT_FIFO_NEW_DATA		= 2,
	MAX30102_INTERRUPT_AMBIENT_LIGHT_CANC	= 4,
	MAX30102_INTERRUPT_PROXIMITY			= 8,
	MAX30102_INTERRUPT_DIE_TEMPERATURE		= 16,
	MAX30102_INTERRUPT_POWER_READY			= 32,
	MAX30102_INTERRUPT_ALL					= 63,
} max30102InterruptFlags_f;

typedef enum max30102SensorResolution_e {
	MAX30102_SENSOR_RESOLUTION_15_BITS		= 0,
	MAX30102_SENSOR_RESOLUTION_16_BITS		= 1,
	MAX30102_SENSOR_RESOLUTION_17_BITS		= 2,
	MAX30102_SENSOR_RESOLUTION_18_BITS		= 3
} max30102SensorResolution_e;

typedef enum max30102SensorSampleRate_e {
	MAX30102_SENSOR_SAMPLE_RATE_50_HZ		= 0,
	MAX30102_SENSOR_SAMPLE_RATE_100_HZ		= 1,
	MAX30102_SENSOR_SAMPLE_RATE_200_HZ		= 2,
	MAX30102_SENSOR_SAMPLE_RATE_400_HZ		= 3,
	MAX30102_SENSOR_SAMPLE_RATE_800_HZ		= 4,
	MAX30102_SENSOR_SAMPLE_RATE_1000_HZ		= 5,
	MAX30102_SENSOR_SAMPLE_RATE_1600_HZ		= 6,
	MAX30102_SENSOR_SAMPLE_RATE_3200_HZ		= 7
} max30102SensorSampleRate_e;

typedef enum max30102SensorFullScale_e {
	MAX30102_SENSOR_FULL_SCALE_2048_NA		= 0,
	MAX30102_SENSOR_FULL_SCALE_4096_NA		= 1,
	MAX30102_SENSOR_FULL_SCALE_8192_NA		= 2,
	MAX30102_SENSOR_FULL_SCALE_16384_NA		= 3
} max30102SensorFullScale_e;

// =============================================================================
// Max30102 - Class declaration
// =============================================================================

class Max30102 {
	// New data types
public:

	// Constructors
public:
	Max30102(uint32_t clockSpeed = I2C_SPEED_STANDARD);

	// Methods
public:
	bool init(max30102SensorSampleRate_e sensorSampleRate =
				  MAX30102_SENSOR_SAMPLE_RATE_50_HZ,
			  max30102SensorResolution_e sensorResolution =
				  MAX30102_SENSOR_RESOLUTION_15_BITS,
			  max30102SensorFullScale_e sensorFullScale = MAX30102_SENSOR_FULL_SCALE_2048_NA);
	bool reset(void);
	bool shutDown(void);
	bool wakeUp(void);
	bool setHeartRateMode(max30102LedCurrent_e redLedCurrent =
							  MAX30102_LED_CURRENT_1_MA);
	bool setSpo2Mode(max30102LedCurrent_e redLedCurrent = MAX30102_LED_CURRENT_1_MA,
					 max30102LedCurrent_e infraredLedCurrent = MAX30102_LED_CURRENT_1_MA);
	bool setCustomMode(max30102LedCurrent_e redLedCurrent =
						   MAX30102_LED_CURRENT_1_MA,
					   max30102LedCurrent_e infraredLedCurrent = MAX30102_LED_CURRENT_1_MA,
					   max30102LedCurrent_e auxLedCurrent = MAX30102_LED_CURRENT_1_MA);
	bool fifoConfig(max30102FifoAveraging_e averages = MAX30102_FIFO_NO_AVERAGE,
					bool overflow = true, uint8_t remainingSpace = 0);
	bool activateInterrupts(max30102InterruptFlags_f activationMask);
	bool deactivateInterrupts(max30102InterruptFlags_f deactivationMask);
	bool getInterruptStatus(max30102InterruptFlags_f interrupt, bool refreshStatus);
	bool flushFifo(void);
	bool getFifoOccupation(uint8_t *samplesWaiting, uint8_t *samplesLost = NULL);
	bool getFifoData(uint8_t samplesCount, uint16_t *redLedBuffer,
					 uint16_t *infraredLedBuffer = NULL);
	bool getFifoData(uint8_t samplesCount, uint32_t *redLedBuffer,
					 uint32_t *infraredLedBuffer = NULL);
	bool getNewestSample(uint16_t *redValue, uint16_t *infraredValue = NULL);
	bool getNewestSample(uint32_t *redValue, uint32_t *infraredValue = NULL);

	uint8_t getReadPointer();
	uint8_t getWritePointer();
	/*
		uint32_t getRed(void); //Returns immediate red value
		uint32_t getIR(void); //Returns immediate IR value
		uint32_t getGreen(void); //Returns immediate green value
		bool safeCheck(uint8_t maxTimeToCheck); //Given a max amount of time, check for new data
		void softReset();
		void setADCRange(uint8_t adcRange);
		void setSampleRate(uint8_t sampleRate);
		void setPulseWidth(uint8_t pulseWidth);
		void setProximityThreshold(uint8_t threshMSB);
		void enableSlot(uint8_t slotNumber, uint8_t device); //Given slot number, assign a device to slot
		void disableSlots(void);
		uint8_t getINT1(void); //Returns the main interrupt group
		uint8_t getINT2(void); //Returns the temp ready interrupt
		uint16_t check(void); //Checks for new data and fills FIFO
		uint8_t available(void); //Tells caller how many new samples are available (head - tail)
		void nextSample(void); //Advances the tail of the sense array
		uint32_t getFIFORed(void); //Returns the FIFO sample pointed to by tail
		uint32_t getFIFOIR(void); //Returns the FIFO sample pointed to by tail
		uint32_t getFIFOGreen(void); //Returns the FIFO sample pointed to by tail
		uint8_t getWritePointer(void);
		uint8_t getReadPointer(void);
		void clearFIFO(void); //Sets the read/write pointers to zero
		void setPROXINTTHRESH(uint8_t val);
		float readTemperature();
		float readTemperatureF();
		void setup(uint8_t powerLevel = 0x1F, uint8_t sampleAverage = 4, uint8_t ledMode = 3, int sampleRate = 400, int pulseWidth = 411, int adcRange = 4096);
		uint8_t readRegister8(uint8_t address, uint8_t reg);
		void writeRegister8(uint8_t address, uint8_t reg, uint8_t value);
	*/
	bool getFifoInfo_(void);

private:
	bool readDeviceInfo_(void);
//	bool getFifoInfo_(void);
	bool readFifoData_(uint8_t nSamples, void *buff1, void *buff2, uint8_t varSize);
	bool readNewestSample_(uint16_t *redValue, uint16_t *infraredValue,
						   uint8_t varSize);

protected:

	// Data members
public:

private:
	max30102Error_e lastError_;
	uint32_t clockSpeed_;
	uint8_t revisionId_;
	uint8_t partId_;
	max30102FifoAveraging_e fifoAveraging_			: 3;
	bool fifoOverflowEnable_						: 1;
	uint8_t fifoInterruptRemainingSpace_			: 4;
	uint8_t redLedCurrent;
	uint8_t infraredLedCurrent;
	uint8_t auxLedCurrent;
	bool shutDownControl_							: 1;
	bool resetControl_								: 1;
	uint8_t enabledSlotsCounter_					: 3;

	max30102ModeControl_e		modeControl_		: 3;
	max30102SensorResolution_e	sensorResolution_	: 2;
	max30102SensorFullScale_e	sensorFullScale_	: 2;
	max30102SensorSampleRate_e	sensorSampleRate_	: 3;

	bool fifoAlmostFullEnable_			: 1;
	bool fifoAlmostFullFlag_			: 1;
	bool fifoNewDataEnable_				: 1;
	bool fifoNewDataFlag_				: 1;
	bool ambientLightCancelationEnable_	: 1;
	bool ambientLightCancelationFlag_	: 1;
	bool proximityThresholdEnable_		: 1;
	bool proximityThresholdFlag_		: 1;
	bool dieTemperatureEnable_			: 1;
	bool dieTemperatureFlag_			: 1;
	bool powerReadyFlag_				: 1;
	uint8_t fifoWritePointer_			: 5;
	uint8_t fifoOverflowCounter_		: 5;
	uint8_t fifoReadPointer_			: 5;
	uint8_t fifoData_;



	uint8_t multiLedSlot1Control_		: 3;
	uint8_t multiLedSlot2Control_		: 3;
	uint8_t multiLedSlot3Control_		: 3;
	uint8_t multiLedSlot4Control_		: 3;
	uint8_t dieTemperatureInteger_;
	uint8_t dieTemperatureFraction_		: 4;
	uint8_t proximityInterruptThreshold_;





//	uint8_t activeLEDs; //Gets set during setup. Allows check() to calculate how many uint8_ts to read from FIFO

protected:

}; // class Max30102

// =============================================================================
// Max30102 - Class inline function definitions
// =============================================================================

/* NONE */

// =============================================================================
// Extern global variables
// =============================================================================

/* NONE */

// =============================================================================
// General public functions declarations
// =============================================================================

/* NONE */

// =============================================================================
// General inline functions definitions
// =============================================================================

/* NONE */

#endif // __MAX30102_HPP
