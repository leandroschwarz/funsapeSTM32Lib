/* =============================================================================
 * Project:		GPSDE++ ARM Library
 * File name:	mpu9250.h
 * Module:		MPU9250 interface module for GPDSE++ ARM Library project
 * Author:		Leandro Schwarz
 * Build:		__BUILD_MACRO_TO_BE_CHANGED__
 * Date:		__DATE_MACRO_TO_BE_CHANGED__
 * ========================================================================== */

// =============================================================================
// File build
// =============================================================================

#ifndef __MPU9250_HPP
#define __MPU9250_HPP						__BUILD_MACRO_TO_BE_CHANGED__

// =============================================================================
// System file dependencies
// =============================================================================

#include "globalDefines.hpp"
#if ___GLOBAL_DEFINES_HPP != __BUILD_MACRO_TO_BE_CHANGED__
#	error	Global definitions file (gpdseArmGlobalDefines) must be build __BUILD_MACRO_TO_BE_CHANGED__.
#endif
// #include "..\gpdseArmI2c.h"
// #if __GPDSE_ARM_I2C_H != __BUILD_MACRO_TO_BE_CHANGED__
// #	error	I2C interface module file (gpdseArmI2c) must be build __BUILD_MACRO_TO_BE_CHANGED__.
// #endif
// #include "..\gpdseArmSpi.h"
// #if __GPDSE_ARM_SPI_H != __BUILD_MACRO_TO_BE_CHANGED__
// #	error	SPI interface module file (gpdseArmSpi) must be build __BUILD_MACRO_TO_BE_CHANGED__.
// #endif

// Header files
#include <math.h>
#include "gpdseArmI2c.hpp"

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constants
// =============================================================================

// NONE

// =============================================================================
// Macro-functions
// =============================================================================

// NONE
#define truncateToLimits(variable, minimum, maximum) (variable > maximum) ? maximum : (variable < minimum) ? minimum : variable
#define returnMinimum(variable, minimum) (variable > minimum) ? minimum : variable
#define returnMaximum(variable, maximum) (variable < maximum) ? maximum : variable

// =============================================================================
// New data types
// =============================================================================

typedef enum mpu9250AccelFullScale_e {
	MPU9250_AFS_2G							= 0,
	MPU9250_AFS_4G							= 1,
	MPU9250_AFS_8G							= 2,
	MPU9250_AFS_16G							= 3,
} mpu9250AccelFullScale_e;

typedef enum mpu9250AccelSampleRate_e {
	MPU9250_ACCEL_SAMPLE_RATE_4_KHZ			= 256,
	MPU9250_ACCEL_SAMPLE_RATE_1_KHZ			= 0,
	MPU9250_ACCEL_SAMPLE_RATE_500_HZ		= 1,
	MPU9250_ACCEL_SAMPLE_RATE_250_HZ		= 3,
	MPU9250_ACCEL_SAMPLE_RATE_200_HZ		= 4,
	MPU9250_ACCEL_SAMPLE_RATE_125_HZ		= 7,
	MPU9250_ACCEL_SAMPLE_RATE_100_HZ		= 9,
	MPU9250_ACCEL_SAMPLE_RATE_50_HZ			= 19,
	MPU9250_ACCEL_SAMPLE_RATE_40_HZ			= 24,
	MPU9250_ACCEL_SAMPLE_RATE_25_HZ			= 39,
	MPU9250_ACCEL_SAMPLE_RATE_20_HZ			= 49,
	MPU9250_ACCEL_SAMPLE_RATE_12_5_HZ		= 79,
	MPU9250_ACCEL_SAMPLE_RATE_10_HZ			= 99,
	MPU9250_ACCEL_SAMPLE_RATE_8_HZ			= 124,
	MPU9250_ACCEL_SAMPLE_RATE_5_HZ			= 199,
	MPU9250_ACCEL_SAMPLE_RATE_4_HZ			= 249,
	MPU9250_ACCEL_SAMPLE_RATE_3_9_HZ		= 255,
} mpu9250AccelSampleRate_e;

typedef enum mpu9250AccelDigitalFilter_e {
	MPU9250_ACCEL_DLPF_218_HZ				= 1,
	MPU9250_ACCEL_DLPF_99_HZ				= 2,
	MPU9250_ACCEL_DLPF_45_HZ				= 3,
	MPU9250_ACCEL_DLPF_21_HZ				= 4,
	MPU9250_ACCEL_DLPF_10_HZ				= 5,
	MPU9250_ACCEL_DLPF_5_HZ					= 6,
	MPU9250_ACCEL_DLPF_420_HZ				= 7,
	MPU9250_ACCEL_DLPF_1046_HZ				= 8,
} mpu9250AccelDigitalFilter_e;

typedef enum mpu9250GyroFullScale_e {
	MPU9250_GFS_250DPS						= 0,
	MPU9250_GFS_500DPS						= 1,
	MPU9250_GFS_1000DPS						= 2,
	MPU9250_GFS_2000DPS						= 3,
} mpu9250GyroFullScale_e;

typedef enum mpu9250GyroDigitalFilter_e {
	MPU9250_GYRO_DLPF_250_HZ				= 0,
	MPU9250_GYRO_DLPF_184_HZ				= 1,
	MPU9250_GYRO_DLPF_92_HZ					= 2,
	MPU9250_GYRO_DLPF_41_HZ					= 3,
	MPU9250_GYRO_DLPF_20_HZ					= 4,
	MPU9250_GYRO_DLPF_10_HZ					= 5,
	MPU9250_GYRO_DLPF_5_HZ					= 6,
	MPU9250_GYRO_DLPF_3600_HZ				= 7,
	MPU9250_GYRO_DLPF_8800_HZ				= 8,
} mpu9250GyroDigitalFilter_e;

typedef enum mpu9250GyroSampleRate_e {
	MPU9250_GYRO_SAMPLE_RATE_32_KHZ			= 512,
	MPU9250_GYRO_SAMPLE_RATE_8_KHZ			= 256,
	MPU9250_GYRO_SAMPLE_RATE_4_KHZ			= 257,
	MPU9250_GYRO_SAMPLE_RATE_2_KHZ			= 259,
	MPU9250_GYRO_SAMPLE_RATE_1_6_KHZ		= 260,
	MPU9250_GYRO_SAMPLE_RATE_1_KHZ			= 0,
	MPU9250_GYRO_SAMPLE_RATE_800_HZ			= 265,
	MPU9250_GYRO_SAMPLE_RATE_500_HZ			= 1,
	MPU9250_GYRO_SAMPLE_RATE_400_HZ			= 275,
	MPU9250_GYRO_SAMPLE_RATE_320_HZ			= 281,
	MPU9250_GYRO_SAMPLE_RATE_250_HZ			= 3,
	MPU9250_GYRO_SAMPLE_RATE_200_HZ			= 4,
	MPU9250_GYRO_SAMPLE_RATE_160_HZ			= 305,
	MPU9250_GYRO_SAMPLE_RATE_125_HZ			= 7,
	MPU9250_GYRO_SAMPLE_RATE_100_HZ			= 9,
	MPU9250_GYRO_SAMPLE_RATE_80_HZ			= 355,
	MPU9250_GYRO_SAMPLE_RATE_64_HZ			= 380,
	MPU9250_GYRO_SAMPLE_RATE_50_HZ			= 19,
	MPU9250_GYRO_SAMPLE_RATE_40_HZ			= 24,
	MPU9250_GYRO_SAMPLE_RATE_32_HZ			= 505,
	MPU9250_GYRO_SAMPLE_RATE_31_25_HZ		= 511,
	MPU9250_GYRO_SAMPLE_RATE_25_HZ			= 39,
	MPU9250_GYRO_SAMPLE_RATE_20_HZ			= 49,
	MPU9250_GYRO_SAMPLE_RATE_12_5_HZ		= 79,
	MPU9250_GYRO_SAMPLE_RATE_10_HZ			= 99,
	MPU9250_GYRO_SAMPLE_RATE_8_HZ			= 124,
	MPU9250_GYRO_SAMPLE_RATE_5_HZ			= 199,
	MPU9250_GYRO_SAMPLE_RATE_4_HZ			= 249,
	MPU9250_GYRO_SAMPLE_RATE_3_9_HZ			= 255,
} mpu9250GyroSampleRate_e;

// =============================================================================
// Mpu9250 - Class declaration
// =============================================================================

class Spi
{
public:
	bool sendData(uint8_t reg, uint8_t * bufData, uint8_t bufSize)
	{
		return true;
	}
	bool setDefaultDevice(void (*actDevFuncCallback)(void),
	        void (*deactDevFuncCallback)(void))
	{
		return true;
	}
};



class Mpu9250
{
	// New data types
public:

	typedef enum mpu9250I2cMasterClock_e {
		MPU9250_I2C_MST_CLK_258_KHz	= 8,
		MPU9250_I2C_MST_CLK_267_KHz	= 7,
		MPU9250_I2C_MST_CLK_276_KHz	= 6,
		MPU9250_I2C_MST_CLK_286_KHz	= 5,
		MPU9250_I2C_MST_CLK_296_KHz	= 4,
		MPU9250_I2C_MST_CLK_308_KHz	= 3,
		MPU9250_I2C_MST_CLK_320_KHz	= 2,
		MPU9250_I2C_MST_CLK_333_KHz	= 1,
		MPU9250_I2C_MST_CLK_348_KHz	= 0,
		MPU9250_I2C_MST_CLK_364_KHz	= 15,
		MPU9250_I2C_MST_CLK_381_KHz	= 14,
		MPU9250_I2C_MST_CLK_400_KHz	= 13,
		MPU9250_I2C_MST_CLK_421_KHz	= 12,
		MPU9250_I2C_MST_CLK_444_KHz	= 11,
		MPU9250_I2C_MST_CLK_471_KHz	= 10,
		MPU9250_I2C_MST_CLK_500_KHz	= 9
	} mpu9250I2cMasterClock_e;

	typedef enum mpu9250ExternalSync_e {
		MPU9250_EXT_SYNC_DISABLED	= 0,
		MPU9250_EXT_SYNC_TEMP,
		MPU9250_EXT_SYNC_GYRO_X,
		MPU9250_EXT_SYNC_GYRO_Y,
		MPU9250_EXT_SYNC_GYRO_Z,
		MPU9250_EXT_SYNC_ACCEL_X,
		MPU9250_EXT_SYNC_ACCEL_Y,
		MPU9250_EXT_SYNC_ACCEL_Z
	} mpu9250ExternalSync_e;

	typedef enum mpu9250ResetPath_f {
		MPU9250_RESET_GYRO		= 1,
		MPU9250_RESET_ACCEL		= 2,
		MPU9250_RESET_TEMP		= 4,
		MPU9250_RESET_FIFO		= 8,
		MPU9250_RESET_I2C_MST	= 16,
		MPU9250_RESET_SIG_COND	= 32,
		MPU9250_RESET_ALL		= 63
	} mpu9250ResetPath_f;

	typedef enum mpu9250AccelSamplingLowPower_e {
		MPU9250_ACCEL_SAMP_LOW_POWER_0P24_HZ		= 0,
		MPU9250_ACCEL_SAMP_LOW_POWER_0P49_HZ		= 1,
		MPU9250_ACCEL_SAMP_LOW_POWER_0P98_HZ		= 2,
		MPU9250_ACCEL_SAMP_LOW_POWER_1P95_HZ		= 3,
		MPU9250_ACCEL_SAMP_LOW_POWER_3P91_HZ		= 4,
		MPU9250_ACCEL_SAMP_LOW_POWER_7P81_HZ		= 5,
		MPU9250_ACCEL_SAMP_LOW_POWER_15P63_HZ		= 6,
		MPU9250_ACCEL_SAMP_LOW_POWER_31P25_HZ		= 7,
		MPU9250_ACCEL_SAMP_LOW_POWER_62P50_HZ		= 8,
		MPU9250_ACCEL_SAMP_LOW_POWER_125_HZ			= 9,
		MPU9250_ACCEL_SAMP_LOW_POWER_250_HZ			= 10,
		MPU9250_ACCEL_SAMP_LOW_POWER_500_HZ			= 11,
	} mpu9250AccelSamplingLowPower_e;

	typedef enum mpu9250PowerMode_e {
		MPU9250_POWER_MODE_UNDEFINED			= 0,
		MPU9250_POWER_MODE_SLEEP				= 1,
		MPU9250_POWER_MODE_STANDBY				= 2,
		MPU9250_POWER_MODE_LOW_POWER_ACCEL		= 3,
		MPU9250_POWER_MODE_LOW_NOISE_ACCEL		= 4,
		MPU9250_POWER_MODE_GYRO					= 5,
		MPU9250_POWER_MODE_MAG					= 6,
		MPU9250_POWER_MODE_ACCEL_GYRO			= 7,
		MPU9250_POWER_MODE_ACCEL_MAG			= 8,
		MPU9250_POWER_MODE_ACCEL_GYRO_MAG		= 9,
	} mpu9250PowerMode_e;

	typedef enum mpu9250ClockSelection_e {
		MPU9250_CLOCK_20_MHZ_OSCILLATOR		= 0,
		MPU9250_CLOCK_AUTO_SELECT_BEST		= 1,
		MPU9250_CLOCK_DISABLED				= 2,
	} mpu9250ClockSelection_e;

	// Constructors
public:
	Mpu9250(void);
	~Mpu9250(void);						// ToDo

	// Methods
public:
	// -------------------------------------------------------------------------
	// Interface
	// -------------------------------------------------------------------------
	bool initialize(I2c *i2cHndlr, bool useAlternateAddress = false);
	bool initialize(Spi *spiHndlr,
							void (*actDevFuncCallback)(void),
							void (*deactDevFuncCallback)(void));
	bool restart(			void);
	bool reset(				mpu9250ResetPath_f resetPaths);
	error_e getLastError(	void);

	// -------------------------------------------------------------------------
	// Sensor configuration
	// -------------------------------------------------------------------------
	bool configAccel(		axis_t axis,
							mpu9250AccelFullScale_e scale,
							mpu9250AccelSampleRate_e sampleRate,
							mpu9250AccelDigitalFilter_e filter);
	bool configGyro(		axis_t axis,
							mpu9250GyroFullScale_e scale,
							mpu9250GyroSampleRate_e sampleRate,
							mpu9250GyroDigitalFilter_e filter);
	bool performSelfTest(	axis_t accelAxis,
							axis_t gyroAxis);			// To Do
	bool performCalibration(
	);

	// -------------------------------------------------------------------------
	// Raw data management
	// -------------------------------------------------------------------------
	bool getAccelData(		int16_t *accelBuff,
							axis_t axis = AXIS_ALL);
	bool getAccelOffset(	int16_t *accelBuff,
							axis_t axis = AXIS_ALL);
	bool setAccelOffset(	int16_t *accelBuff,
							axis_t axis = AXIS_ALL);
	bool getGyroData(		int16_t *gyroBuff,
							axis_t axis = AXIS_ALL);
	bool getGyroOffset(		int16_t *gyroBuff,
							axis_t axis = AXIS_ALL);
	bool setGyroOffset(		int16_t *gyroBuff,
							axis_t axis = AXIS_ALL);
	bool getTempData(		int16_t *temp);

	// -------------------------------------------------------------------------
	// FIFO configuration
	// -------------------------------------------------------------------------
	bool configFifo(		void);			// To Do

	bool configIntPin(		logicLevel_t pinLevel = LOW,
							outputDriver_t pinDriver = PUSH_PULL,
							bool pinLatch = false,
							bool pinAutoReset = false);
	bool setIntDataReady(	bool enabled);


//	void readAll(uint8_t *buffer, uint8_t *size);
//	void readMag(int16_t * magBuff);

private:
	bool performHardReset(void);
	void dumpClassData_(void);






	// Interface
	bool deinitialize_(void);								// To Do
	bool initialize_(void);
	bool getWhoAmI_(void);

	// Configuration
	bool updateSampleRateDivider_(void);					// To Do
	bool updateAccelConfig_(void);							// To Do
	bool updateAccelConfig2_(void);							// To Do
	bool updatePowerManagementControl2_(void);				// To Do
	bool updateConfig_(void);								// To Do
	bool updateGyroConfig_(void);							// To Do
	bool getAccelSelfTest_(void);					// To Do
	bool getGyroSelfTest_(void);					// To Do
	bool updateUserControl_(void);							// To Do

	// Raw data management
	bool getAccelData_(void);								// To Do
	bool getAccelOffset_(void);							// To Do
	bool getGyroData_(void);								// To Do
	bool getGyroOffset_(void);								// To Do
	bool getTempData_(void);								// To Do
	bool updateAccelOffset_(void);							// To Do
	bool updateGyroOffset_(void);							// To Do

	// FIFO
	bool updateFifoEnable_(void);							// To Do
	bool getFifoCount_(void);								// To Do
	bool getFifoReadWrite_(void);							// To Do
	bool updateFifoReadWrite_(void);						// To Do

	// Motion Control
	bool updateWakeUpMotionThreshold_(void);				// To Do
	bool updateMotionDetectControl_(void);					// To Do

	//	I2C
	bool updateI2cMasterControl_(void);						// To Do
	bool updateI2cSlave0Address_(void);						// To Do
	bool updateI2cSlave0Control_(void);						// To Do
	bool updateI2cSlave0Register_(void);					// To Do
	bool updateI2cSlave1Address_(void);						// To Do
	bool updateI2cSlave1Control_(void);						// To Do
	bool updateI2cSlave1Register_(void);					// To Do
	bool updateI2cSlave2Address_(void);						// To Do
	bool updateI2cSlave2Control_(void);						// To Do
	bool updateI2cSlave2Register_(void);					// To Do
	bool updateI2cSlave3Address_(void);						// To Do
	bool updateI2cSlave3Control_(void);						// To Do
	bool updateI2cSlave3Register_(void);					// To Do
	bool updateI2cSlave4Address_(void);						// To Do
	bool updateI2cSlave4Control_(void);						// To Do
	bool updateI2cSlave4Register_(void);					// To Do
	bool updateI2cSlave4DataOut_(void);						// To Do
	bool getI2cSlave4DataIn_(void);						// To Do
	bool getI2cMasterStatus_(void);						// To Do
	bool updateI2cMasterControlDelay_(void);				// To Do
	bool updateI2cSlave0DataOut_(void);						// To Do
	bool updateI2cSlave1DataOut_(void);						// To Do
	bool updateI2cSlave2DataOut_(void);						// To Do
	bool updateI2cSlave3DataOut_(void);						// To Do

	//	Interrupt
	bool updateIntPinConfig_(void);							// To Do
	bool updateIntEnable_(void);							// To Do
	bool getInterruptStatus_(void);								// To Do

	// External sensor
	bool readExtSensData(uint8_t first, uint8_t total);		// To Do

	// Reset
	bool updateSignalPathReset_(void);						// To Do
	bool updatePowerManagementControl1_(void);				// To Do

	// Low power
	bool updateLowPowerAccelODR_(void);						// To Do

	// Low level communication
	bool readFromDevice_(uint8_t reg, uint8_t *buffer, uint8_t size);
	bool writeAtDevice_(uint8_t reg, uint8_t *buffer, uint8_t size);	// To Do

protected:

	// Data members
public:

private:
	// Interface
	error_e		lastError_;
	bool		initialized_					: 1;
	I2c *i2cHandler_;
	uint8_t		i2c7bitAddress_					: 7;
	bool		useSpi_							: 1;
	bool		commPortSet_					: 1;
	Spi			*spiHandler_;
	void		(*activateDevice_)(void);
	void		(*deactivateDevice_)(void);
	bool		resetGyro_						: 1;
	bool		resetAccel_						: 1;
	bool		resetTemp_						: 1;
	bool		resetFifo_						: 1;
	bool		resetI2c_						: 1;
	bool		resetSignal_					: 1;

	// Sensor configuration
	bool		accelDisableX_					: 1;
	bool		accelDisableY_					: 1;
	bool		accelDisableZ_					: 1;
	uint8_t		accelDlpfCfg_					: 3;
	bool		accelFChoiceB_					: 1;
	uint8_t		accelFullScale_					: 2;
	uint8_t		sampleRateDivider_;
	bool		gyroDisableX_					: 1;
	bool		gyroDisableY_					: 1;
	bool		gyroDisableZ_					: 1;
	uint8_t		gyroDlpfCfg_					: 3;
	uint8_t		gyroFChoiceB_					: 2;
	uint8_t		gyroFullScale_					: 2;
	bool		accelXSelfTestEnabled_			: 1;	/// To do
	bool		accelYSelfTestEnabled_			: 1;	/// To do
	bool		accelZSelfTestEnabled_			: 1;	/// To do
	uint8_t		accelSelfTest_[3];						/// To do
	bool		gyroXSelfTestEnabled_			: 1;	/// To do
	bool		gyroYSelfTestEnabled_			: 1;	/// To do
	bool		gyroZSelfTestEnabled_			: 1;	/// To do
	uint8_t		gyroSelfTest_[3];						/// To do

	// Raw data management
	int16_t		accelData_[3];
	uint16_t	accelOffset_[3];
	int16_t		gyroData_[3];
	uint16_t	gyroOffset_[3];
	int16_t		tempData_;

	// FIFO configuration
	bool		fifoMode_						: 1;
	bool		fifoEnable_						: 1;
	uint16_t	fifoLenght_;
	bool		fifoTempStore_					: 1;
	bool		fifoGyroXStore_					: 1;
	bool		fifoGyroyStore_					: 1;
	bool		fifoGyrozStore_					: 1;
	bool		fifoAccelStore_					: 1;
	bool		fifoSlave3Store_				: 1;
	bool		fifoSlave2Store_				: 1;
	bool		fifoSlave1Store_				: 1;
	bool		fifoSlave0Store_				: 1;

	// I2C master bus data members
	bool		i2cMultiMaster_					: 1;
	bool		i2cWaitForExtSensor_			: 1;
	bool		i2cStopBetweenTransmissions_	: 1;
	bool		i2cMasterClock_					: 4;
	bool		i2cSlave0ReadWrite_				: 1;
	uint8_t		i2cSlave0Address_				: 7;
	bool		i2cSlave1ReadWrite_				: 1;
	uint8_t		i2cSlave1Address_				: 7;
	bool		i2cSlave2ReadWrite_				: 1;
	uint8_t		i2cSlave2Address_				: 7;
	bool		i2cSlave3ReadWrite_				: 1;
	uint8_t		i2cSlave3Address_				: 7;
	bool		i2cSlave4ReadWrite_				: 1;
	uint8_t		i2cSlave4Address_				: 7;
	uint8_t		i2cSlave0Register_;
	uint8_t		i2cSlave1Register_;
	uint8_t		i2cSlave2Register_;
	uint8_t		i2cSlave3Register_;
	uint8_t		i2cSlave4Register_;
	uint8_t		i2cSlave0DataOut_;
	uint8_t		i2cSlave1DataOut_;
	uint8_t		i2cSlave2DataOut_;
	uint8_t		i2cSlave3DataOut_;
	uint8_t		i2cSlave4DataOut_;
	bool		i2cSlave0Enable_				: 1;
	bool		i2cSlave0SwapBytes_				: 1;
	bool		i2cSlave0RegisterDisable_		: 1;
	bool		i2cSlave0GroupingSkipFirst_		: 1;
	uint8_t		i2cSlave0DataLength_			: 4;
	bool		i2cSlave1Enable_				: 1;
	bool		i2cSlave1SwapBytes_				: 1;
	bool		i2cSlave1RegisterDisable_		: 1;
	bool		i2cSlave1GroupingSkipFirst_		: 1;
	uint8_t		i2cSlave1DataLength_			: 4;
	bool		i2cSlave2Enable_				: 1;
	bool		i2cSlave2SwapBytes_				: 1;
	bool		i2cSlave2RegisterDisable_		: 1;
	bool		i2cSlave2GroupingSkipFirst_		: 1;
	uint8_t		i2cSlave2DataLength_			: 4;
	bool		i2cSlave3Enable_				: 1;
	bool		i2cSlave3SwapBytes_				: 1;
	bool		i2cSlave3RegisterDisable_		: 1;
	bool		i2cSlave3GroupingSkipFirst_		: 1;
	uint8_t		i2cSlave3DataLength_			: 4;
	bool		i2cSlave4Enable_				: 1;
	bool		i2cSlave4IntEnable_				: 1;
	bool		i2cSlave4RegisterDisable_		: 1;
	uint8_t		i2cSlave4Delay_					: 5;
	bool		i2cBypassEnable_				: 1;
	bool		i2cExtSensorShadowDelayEnable_	: 1;
	bool		i2cSlave4DelayEnable_			: 1;
	bool		i2cSlave3DelayEnable_			: 1;
	bool		i2cSlave2DelayEnable_			: 1;
	bool		i2cSlave1DelayEnable_			: 1;
	bool		i2cSlave0DelayEnable_			: 1;
	bool		i2cMasterEnable_				: 1;

	// Interrupts
	bool		intPinActiveLevel_				: 1;
	bool		intPinOpenDrain_				: 1;
	bool		intPinLatchEnable_				: 1;
	bool		intPinAutoClear_				: 1;
	bool		intPinFsyncActiveLevel_			: 1;
	bool		intFsyncModeEnable_				: 1;
	bool		intWakeOnMotionEnable_			: 1;
	bool		intFifoOverfowEnable_			: 1;
	bool		intFsyncEnable_					: 1;
	bool		intRawDataReadyEnable_			: 1;
	bool		intWakeOnMotionFlag_			: 1;
	bool		intFifoOverflowFlag_			: 1;
	bool		intFsyncFlag_					: 1;
	bool		intI2cDataReadyFlag_			: 1;

	// Motion detection
	uint8_t		wakeOnMotionThreshold_;
	bool		wakeOnMotionMode_				: 1;
	bool		wakeOnMotionEnable_				: 1;

	// Power management
	bool		cycleEnable_					: 1;
	bool		sleepEnable_					: 1;
	bool		gyroStandby_					: 1;
	bool		ptatDisable_					: 1;
	uint8_t		clockSelection_					: 3;
	uint8_t		lowPowerOscClock_				: 4;

	// External sensor data members
	uint8_t		extenalSensorData_[24];
	uint8_t		extSyncSet_						: 3;

protected:

}; // class Mpu9250

// =============================================================================
// Mpu9250 - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

#endif // __MPU9250_H
