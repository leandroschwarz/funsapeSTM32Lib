/* -----------------------------------------------------------------------------
 * Project:		GPSDE++ AVR Library
 * File name:	mpu9250.hpp
 * Module:		MPU9250 Driver for GPDSE++ AVR Library project
 * Authors:		Leandro Schwarz
 *				Hazael dos Santos Batista
 * Build:		1001
 * Date:		May 26, 2018
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Include guards --------------------------------------------------------------

#ifndef __MPU9250_HPP
#define __MPU9250_HPP	1001

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#if __USE_OWN_DEFINITIONS_FILE == 1
#	include "..\userDefines.hpp"
#else
#	include "..\globalDefines.hpp"
#	if __GLOBAL_DEFINES_HPP != 1001
#		error 	[mpu9250.hpp] Error 102 - Build mismatch (globalDefines.hpp and mpu9250.hpp)
#	endif		// __GLOBAL_CONFIGS_HPP != 1001
#endif		// __USE_OWN_DEFINITIONS_FILE == 1

#include TWI_LIBRARY_PATH
#include <util/delay.h>

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum mpu9250Error_e {
	MPU9250_ERROR_NONE				= 0,
	MPU9250_ERROR_WRONG_WHO_AM_I	= 1,
	MPU9250_ERROR_NOT_INITIALIZED	= 2,
	MPU9250_INVALID_AXIS			= 3,
} mpu9250Error_e;

// -----------------------------------------------------------------------------
// Macro-functions definitions -------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Extern global variables -----------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// General public function declarations ----------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// General inline function declarations ----------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Mpu9250 class - Class Definition --------------------------------------------

class Mpu9250
{
	// New data types - Public
public:
	typedef enum gyroFullScale_e {
		GFS_250DPS	= 0,
		GFS_500DPS,
		GFS_1000DPS,
		GFS_2000DPS
	} gyroFullScale_e;
	typedef enum accelFullScale_e {
		AFS_2G = 0,
		AFS_4G,
		AFS_8G,
		AFS_16G
	} accelFullScale_e;
	typedef enum i2cMasterClock_e {
		I2C_MST_CLK_258_KHz	= 8,
		I2C_MST_CLK_267_KHz	= 7,
		I2C_MST_CLK_276_KHz	= 6,
		I2C_MST_CLK_286_KHz	= 5,
		I2C_MST_CLK_296_KHz	= 4,
		I2C_MST_CLK_308_KHz	= 3,
		I2C_MST_CLK_320_KHz	= 2,
		I2C_MST_CLK_333_KHz	= 1,
		I2C_MST_CLK_348_KHz	= 0,
		I2C_MST_CLK_364_KHz	= 15,
		I2C_MST_CLK_381_KHz	= 14,
		I2C_MST_CLK_400_KHz	= 13,
		I2C_MST_CLK_421_KHz	= 12,
		I2C_MST_CLK_444_KHz	= 11,
		I2C_MST_CLK_471_KHz	= 10,
		I2C_MST_CLK_500_KHz	= 9
	} i2cMasterClock_e;
	typedef enum externalSync_e {
		EXT_SYNC_DISABLED	= 0,
		EXT_SYNC_TEMP,
		EXT_SYNC_GYRO_X,
		EXT_SYNC_GYRO_Y,
		EXT_SYNC_GYRO_Z,
		EXT_SYNC_ACCEL_X,
		EXT_SYNC_ACCEL_Y,
		EXT_SYNC_ACCEL_Z
	} externalSync_e;
	typedef enum gyroSamplingConfig_e {
		GYRO_SAMP_32_KHZ_FILTER_8800_HZ		= 8,
		GYRO_SAMP_32_KHZ_FILTER_3600_HZ		= 16,
		GYRO_SAMP_8_KHZ_FILTER_250_HZ		= 0,
		GYRO_SAMP_1_KHZ_FILTER_184_HZ		= 1,
		GYRO_SAMP_1_KHZ_FILTER_92_HZ		= 2,
		GYRO_SAMP_1_KHZ_FILTER_41_HZ		= 3,
		GYRO_SAMP_1_KHZ_FILTER_20_HZ		= 4,
		GYRO_SAMP_1_KHZ_FILTER_10_HZ		= 5,
		GYRO_SAMP_1_KHZ_FILTER_5_HZ			= 6,
		GYRO_SAMP_8_KHZ_FILTER_3600_HZ		= 7,
	} gyroSamplingConfig_e;
	typedef enum accelSamplingConfig_e {
		ACCEL_SAMP_4_KHZ_FILTER_1046_HZ		= 0,
		ACCEL_SAMP_1_KHZ_FILTER_218_HZ		= 8,
		ACCEL_SAMP_1_KHZ_FILTER_99_HZ		= 10,
		ACCEL_SAMP_1_KHZ_FILTER_45_HZ		= 11,
		ACCEL_SAMP_1_KHZ_FILTER_21_HZ		= 12,
		ACCEL_SAMP_1_KHZ_FILTER_10_HZ		= 13,
		ACCEL_SAMP_1_KHZ_FILTER_5_HZ		= 14,
		ACCEL_SAMP_1_KHZ_FILTER_420_HZ		= 15,
	} accelSamplingConfig_e;
	typedef enum accelSamplingLowPower_e {
		ACCEL_SAMP_LOW_POWER_0P24_HZ		= 0,
		ACCEL_SAMP_LOW_POWER_0P49_HZ		= 1,
		ACCEL_SAMP_LOW_POWER_0P98_HZ		= 2,
		ACCEL_SAMP_LOW_POWER_1P95_HZ		= 3,
		ACCEL_SAMP_LOW_POWER_3P91_HZ		= 4,
		ACCEL_SAMP_LOW_POWER_7P81_HZ		= 5,
		ACCEL_SAMP_LOW_POWER_15P63_HZ		= 6,
		ACCEL_SAMP_LOW_POWER_31P25_HZ		= 7,
		ACCEL_SAMP_LOW_POWER_62P50_HZ		= 8,
		ACCEL_SAMP_LOW_POWER_125_HZ			= 9,
		ACCEL_SAMP_LOW_POWER_250_HZ			= 10,
		ACCEL_SAMP_LOW_POWER_500_HZ			= 11,
	} accelSamplingLowPower_e;
	typedef enum powerMode_e {
		POWER_MODE_NORMAL		= 0,
		POWER_MODE_SLEEP		= 1,
		POWER_MODE_CYCLE		= 2,
		POWER_MODE_STANDBY		= 4,
	} powerMode_e;
	typedef enum clockSelection_e {
		CLOCK_20_MHZ_OSCILLATOR		= 0,
		CLOCK_AUTO_SELECT_BEST		= 1,
		CLOCK_DISABLED				= 2,
	} clockSelection_e;

	// New data types - Private
private:

	// New data types - Protected
protected:

	// Constructors
public:
	Mpu9250(TWI_HANDLER_CLASS * i2cHand, bool_t alternateAddress = FALSE);
	// Methods - Public
public:
	mpu9250Error_e initialize(void);
	void setI2cMasterBusBypass(bool_t bypass);
	void initializeMagnetometer(void);
	void setMagnetometerSampleRate(void);
	mpu9250Error_e getAccelRaw(int16_t * accelRawBuff, axis_t axis);
	mpu9250Error_e getGyroRaw(int16_t * gyroRawBuff, axis_t axis);
	mpu9250Error_e getAccel(int32_t * accelQ9Buff, axis_t axis, int16_t * accelRawBuff);
	mpu9250Error_e getGyro(int32_t * gyroQ9Buff, axis_t axis, int16_t * gyroRawBuff);
	mpu9250Error_e getTemp(uint32_t * tempUQ12);
	mpu9250Error_e setGyroScale(gyroFullScale_e gyroScale);
	mpu9250Error_e setAccelScale(accelFullScale_e accelScale);
	mpu9250Error_e getAccelOffset(int16_t * accelOffsetBuff, axis_t axis);
	mpu9250Error_e getGyroOffset(int16_t * gyroOffsetBuff, axis_t axis);
	mpu9250Error_e setAccelOffset(int16_t * accelOffsetBuff, axis_t axis);
	mpu9250Error_e setGyroOffset(int16_t * gyroOffsetBuff, axis_t axis);

	// Methods - Private
private:
	void writeDataI2c();
	void readAccelData(void);
	void readGyroData(void);
	void readTempData(void);
	void updateAccelConfig(void);
	void updateAccelConfig2(void);
	void updateConfig(void);
	void updateFifoEnable(void);
	void updateGyroConfig(void);
	void updateI2cMasterControl(void);
	void updateI2cMasterDelayControl(void);
	void updateI2cSlave0Address(void);
	void updateI2cSlave0Control(void);
	void updateI2cSlave0Register(void);
	void updateI2cSlave1Address(void);
	void updateI2cSlave1Control(void);
	void updateI2cSlave1Register(void);
	void updateI2cSlave2Address(void);
	void updateI2cSlave2Control(void);
	void updateI2cSlave2Register(void);
	void updateI2cSlave3Address(void);
	void updateI2cSlave3Control(void);
	void updateI2cSlave3Register(void);
	void updateI2cSlave4Address(void);
	void updateI2cSlave4Register(void);
	void updateI2cSlave4Control(void);
	void updateI2cSlave4DataOut(void);
	void readI2cSlave4DataIn(void);
	void updateI2cSlave3DataOut(void);
	void updateI2cSlave2DataOut(void);
	void updateI2cSlave1DataOut(void);
	void updateI2cSlave0DataOut(void);
	void updateIntPinConfig(void);
	void updatePowerManagementControl1(void);
	void updatePowerManagementControl2(void);
	void updateUserControl(void);
	bool_t checkWhoAmI(void);
	void updateGyroOffset(void);
	void updateAccelOffset(void);
	void readAccelOffset(void);
	void readGyroOffset(void);
	void readGyroFactorySelfTest(void);
	void readAccelFactorySelfTest(void);

	// Methods - Protected
protected:

	// Data members - Public
public:

	// Data members - Private
private:
	TWI_HANDLER_CLASS		* i2cHandler_;
	uint8_t					i2cMyAddress_;
	bool_t					initialized_						: 1;
	// SELF TEST
	uint8_t					gyroFactorySelfTest_[3];
	uint8_t					accelFactorySelfTest_[3];
	// GYRO OFFSET
	uint16_t				gyroOffset_[3];
	// SMPLRT_DIV
	uint8_t					sampleRateDivider_;
	// CONFIG
	bool_t					fifoStopWhenFull_					: 1;
	externalSync_e			externalSync_						: 3;
	gyroSamplingConfig_e	gyroSamplingConfig_					: 5;	// [2:0]
	// GYRO_CONFIG
	bool_t					gyroXSelfTestEnabled_				: 1;
	bool_t					gyroYSelfTestEnabled_				: 1;
	bool_t					gyroZSelfTestEnabled_				: 1;
	gyroFullScale_e			gyroFullScale_						: 2;
	// 	gyroSamplingConfig_e	gyroSamplingConfig_					: 5;	// [4:3]
	// ACCEL_CONFIG
	bool_t					accelXSelfTestEnabled_				: 1;
	bool_t					accelYSelfTestEnabled_				: 1;
	bool_t					accelZSelfTestEnabled_				: 1;
	accelFullScale_e		accelFullScale_						: 2;
	// ACCEL_CONFIG2
	accelSamplingConfig_e	accelSamplingConfig_				: 4;
	// LP_ACCEL_ODR
	accelSamplingLowPower_e	accelSamplingLowPower_				: 4;
	// WOM_THR
	uint8_t					accelWakeUpMotionThreshold_;
	// FIFO_EN
	bool_t					fifoTempRecordEnabled_				: 1;
	bool_t					fifoGyroXRecordEnabled_				: 1;
	bool_t					fifoGyroYRecordEnabled_				: 1;
	bool_t					fifoGyroZRecordEnabled_				: 1;
	bool_t					fifoAccelXYXRecordEnabled_			: 1;
	bool_t					fifoSlave2RecordEnabled_			: 1;
	bool_t					fifoSlave1RecordEnabled_			: 1;
	bool_t					fifoSlave0RecordEnabled_			: 1;
	// I2C_MST_CTRL
	bool_t					i2cMultiMasterEnabled_				: 1;
	bool_t					i2cDataReadyIntWaitExternalSensors_	: 1;
	bool_t					fifoSlave3RecordEnabled_			: 1;
	bool_t					i2cSendStopBetweenSlaves_			: 1;
	i2cMasterClock_e		i2cMasterClock_						: 4;
	// I2C_SLV0_ADDR
	bool_t					i2cSlave0ReadMode_					: 1;
	uint8_t					i2cSlave0Address_					: 7;
	// I2C_SLV0_REG
	uint8_t					i2cSlave0Register_;
	// I2C_SLV0_CTRL
	bool_t					i2cSlave0Enabled_					: 1;
	bool_t					i2cSlave0WordBytesSwap_				: 1;
	bool_t					i2cSlave0DoNotSendRegister_			: 1;
	bool_t					i2cSlave0GroupEndingEven_			: 1;
	uint8_t					i2cSlave0DataLenght_				: 4;
	// I2C_SLV1_ADDR
	bool_t					i2cSlave1ReadMode_					: 1;
	uint8_t					i2cSlave1Address_					: 7;
	// I2C_SLV1_REG
	uint8_t					i2cSlave1Register_;
	// I2C_SLV1_CTRL
	bool_t					i2cSlave1Enabled_					: 1;
	bool_t					i2cSlave1WordBytesSwap_				: 1;
	bool_t					i2cSlave1DoNotSendRegister_			: 1;
	bool_t					i2cSlave1GroupEndingEven_			: 1;
	uint8_t					i2cSlave1DataLenght_				: 4;
	// I2C_SLV2_ADDR
	bool_t					i2cSlave2ReadMode_					: 1;
	uint8_t					i2cSlave2Address_					: 7;
	// I2C_SLV2_REG
	uint8_t					i2cSlave2Register_;
	// I2C_SLV2_CTRL
	bool_t					i2cSlave2Enabled_					: 1;
	bool_t					i2cSlave2WordBytesSwap_				: 1;
	bool_t					i2cSlave2DoNotSendRegister_			: 1;
	bool_t					i2cSlave2GroupEndingEven_			: 1;
	uint8_t					i2cSlave2DataLenght_				: 4;
	// I2C_SLV3_ADDR
	bool_t					i2cSlave3ReadMode_					: 1;
	uint8_t					i2cSlave3Address_					: 7;
	// I2C_SLV3_REG
	uint8_t					i2cSlave3Register_;
	// I2C_SLV3_CTRL
	bool_t					i2cSlave3Enabled_					: 1;
	bool_t					i2cSlave3WordBytesSwap_				: 1;
	bool_t					i2cSlave3DoNotSendRegister_			: 1;
	bool_t					i2cSlave3GroupEndingEven_			: 1;
	uint8_t					i2cSlave3DataLenght_				: 4;
	// I2C_SLV4_ADDR
	bool_t					i2cSlave4ReadMode_					: 1;
	uint8_t					i2cSlave4Address_					: 7;
	// I2C_SLV4_REG
	uint8_t					i2cSlave4Register_;
	// I2C_SLV4_DO
	uint8_t					i2cSlave4DataOut_;
	// I2C_SLV4_CTRL
	bool_t					i2cSlave4SingleTransferEnable_		: 1;
	bool_t					i2cSlave4IntTransferReadyEnabled_	: 1;
	bool_t					i2cSlave4DoNotSendRegister_			: 1;
	uint8_t					i2cSlave4MasterDelay_				: 5;
	// I2C_SLV4_DI
	uint8_t					i2cSlave4DataIn_;
	// I2C_MST_STATUS
	bool_t					i2cStatusPassThroughFlag_			: 1;
	bool_t					i2cStatusSlave4TransferDoneFlag_	: 1;
	bool_t					i2cStatusArbitrationLost_			: 1;
	bool_t					i2cStatusSlave4NackReceivedFlag_	: 1;
	bool_t					i2cStatusSlave3NackReceivedFlag_	: 1;
	bool_t					i2cStatusSlave2NackReceivedFlag_	: 1;
	bool_t					i2cStatusSlave1NackReceivedFlag_	: 1;
	bool_t					i2cStatusSlave0NackReceivedFlag_	: 1;
	// INT_PIN_CFG
	logicLevel_t			intPinActivationLevel_				: 1;
	outputDriver_t			intPinOutputDriver_					: 1;
	bool_t					intPinLatched_						: 1;
	bool_t					intPinClearWhenRead_				: 1;
	logicLevel_t			fsyncPinActivationLevel_			: 1;
	bool_t					fsyncPinTriggerInterrupt_			: 1;
	bool_t					i2cBypassModeEnabled_				: 1;
	// INT_ENABLE
	bool_t					intWakeOnMotionEnabled_				: 1;
	bool_t					intFifoOverflowEnabled_				: 1;
	bool_t					intFsyncEnabled_					: 1;
	bool_t					intI2cDataReadyEnabled_				: 1;
	// INT_STATUS
	bool_t					intWakeOnMotionFlag_				: 1;
	bool_t					intFifoOverflowFlag_				: 1;
	bool_t					intFsyncFlag_						: 1;
	bool_t					intI2cDataReadyFlag_				: 1;
	// ACCEL_OUT
	int16_t					accelData_[3];
	// TEMP_OUT
	int16_t					tempData_;
	// GYRO_OUT
	int16_t					gyroData_[3];
	// EXT_SENS_DATA
	uint8_t					extSensData_[24];
	// I2C_SLVx_DO
	uint8_t					i2cSlave0DataOut_;
	uint8_t					i2cSlave1DataOut_;
	uint8_t					i2cSlave2DataOut_;
	uint8_t					i2cSlave3DataOut_;
	// I2C_MST_DELAY_CTRL
	bool_t					i2cExtDataShadowingEnabled_			: 1;
	bool_t					i2cSlave4DelayEnabled_				: 1;
	bool_t					i2cSlave3DelayEnabled_				: 1;
	bool_t					i2cSlave2DelayEnabled_				: 1;
	bool_t					i2cSlave1DelayEnabled_				: 1;
	bool_t					i2cSlave0DelayEnabled_				: 1;
	// SIGNAL_PATH_RESET
	bool_t					gyroSignalPathReset_				: 1;
	bool_t					accelSignalPathReset_				: 1;
	bool_t					tempSignalPathReset_				: 1;
	// MOT_DETECT_CTRL
	//	MOT_DETECT_CTRL			ACCEL_INTEL_EN
	//	MOT_DETECT_CTRL			ACCEL_INTEL_MODE
	// USER_CTRL
	bool_t					fifoEnabled_						: 1;
	bool_t					i2cMasterEnabled_					: 1;
	bool_t					useSpiInterface_					: 1;
	bool_t					fifoResetStrobe_					: 1;
	bool_t					i2cMasterResetStrobe_				: 1;
	bool_t					signalPathResetStrobe_				: 1;
	// PWR_MGMT_1
	bool_t					resetDevice_						: 1;
	powerMode_e				powerMode_							: 3;	// SLEEP, CYCLE, GYRO_STANDBY
	bool_t					powerDownMode_						: 1;	// PD_PTAT
	clockSelection_e		clockSelection_						: 2;
	// PWR_MGMT_2
	bool_t					accelXDisable_						: 1;
	bool_t					accelYDisable_						: 1;
	bool_t					accelZDisable_						: 1;
	bool_t					gyroXDisable_						: 1;
	bool_t					gyroYDisable_						: 1;
	bool_t					gyroZDisable_						: 1;
	// FIFO_COUNT
	uint16_t				fifoCount_							: 13;
	// FIFO_R_W
	uint8_t					fifoData_;		// FIFO_R_W
	// ACCEL OFFSET
	uint16_t				accelOffset_[3];

	// MAGNETOMETER
	bool_t					magI2cBypass_						: 1;
	int16_t					magSensibility_[3];

	// Data members - Protected
protected:

};

// -----------------------------------------------------------------------------
// Mpu9250 class - Static or inline functions definitions ----------------------

/* NONE */

// -----------------------------------------------------------------------------
// External class instantiations -----------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// General static or inline functions declarations -----------------------------

/* NONE */

#endif		// __MPU9250_HPP
