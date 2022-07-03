/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		max9250.cpp
 * Module:			MAX9250 module interface for FunSAPE++ Embedded Library
 * 					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Dependencies
// =============================================================================

#include "mpu9250.hpp"
#ifndef __MPU9250_HPP
#	error	[mpu9250.cpp] Error 1 - Header file (mpu9250.hpp) is missing or corrupted!
#elif __MPU9250_HPP != __BUILD_TO_REPLACE__
#	error	[mpu9250.cpp] Error 13 - Build mismatch between source (mpu9250.cpp) and header (mpu9250.hpp) files!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define MPU9250_SLAVE_ADDRESS_NORMAL			0x68
#define MPU9250_SLAVE_ADDRESS_ALTERNATE			0x69
#define MPU9250_WHO_AM_I						0x71

// =============================================================================
// File exclusive - New data types
// =============================================================================

// -----------------------------------------------------------------------------
// MPU9250 register bit position
// -----------------------------------------------------------------------------

typedef enum mpu9250RegisterBit_e {
	MPU9250_BIT_CONFIG_FIFO_MODE				= 6,
	MPU9250_BIT_CONFIG_EXT_SYNC_SET_0			= 3,
	MPU9250_BIT_CONFIG_GYRO_DLPF_CFG_0			= 0,
	MPU9250_BIT_GYRO_CONFIG_Z_ST_EN				= 7,
	MPU9250_BIT_GYRO_CONFIG_Y_ST_EN				= 6,
	MPU9250_BIT_GYRO_CONFIG_X_ST_EN				= 5,
	MPU9250_BIT_GYRO_CONFIG_FS_SEL0				= 2,
	MPU9250_BIT_GYRO_CONFIG_FCHOICE_B_0			= 0,
	MPU9250_BIT_ACCEL_CONFIG_Z_ST_EN			= 7,
	MPU9250_BIT_ACCEL_CONFIG_Y_ST_EN			= 6,
	MPU9250_BIT_ACCEL_CONFIG_X_ST_EN			= 5,
	MPU9250_BIT_ACCEL_CONFIG_FS_SEL0			= 3,
	MPU9250_BIT_ACCEL_CONFIG2_FCHOICE_B_0		= 2,
	MPU9250_BIT_ACCEL_CONFIG2_DLPF_CFG_0		= 0,
	MPU9250_BIT_I2C_SLV0_EN						= 7,
	MPU9250_BIT_I2C_SLV0_BYTE_SW				= 6,
	MPU9250_BIT_I2C_SLV0_REG_DIS				= 5,
	MPU9250_BIT_I2C_SLV0_GRP					= 4,
	MPU9250_BIT_I2C_SLV0_LENG_0					= 0,
	MPU9250_BIT_I2C_SLV1_EN						= 7,
	MPU9250_BIT_I2C_SLV1_BYTE_SW				= 6,
	MPU9250_BIT_I2C_SLV1_REG_DIS				= 5,
	MPU9250_BIT_I2C_SLV1_GRP					= 4,
	MPU9250_BIT_I2C_SLV1_LENG_0					= 0,
	MPU9250_BIT_I2C_SLV2_EN						= 7,
	MPU9250_BIT_I2C_SLV2_BYTE_SW				= 6,
	MPU9250_BIT_I2C_SLV2_REG_DIS				= 5,
	MPU9250_BIT_I2C_SLV2_GRP					= 4,
	MPU9250_BIT_I2C_SLV2_LENG_0					= 0,
	MPU9250_BIT_I2C_SLV3_EN						= 7,
	MPU9250_BIT_I2C_SLV3_BYTE_SW				= 6,
	MPU9250_BIT_I2C_SLV3_REG_DIS				= 5,
	MPU9250_BIT_I2C_SLV3_GRP					= 4,
	MPU9250_BIT_I2C_SLV3_LENG_0					= 0,
	MPU9250_BIT_I2C_SLV4_EN						= 7,
	MPU9250_BIT_I2C_SLV4_INT_EN					= 6,
	MPU9250_BIT_I2C_SLV4_REG_DIS				= 5,
	MPU9250_BIT_I2C_SLV4_DELAY					= 0,
	MPU9250_BIT_SIG_PAT_RST_GYRO				= 2,
	MPU9250_BIT_SIG_PAT_RST_ACCEL				= 1,
	MPU9250_BIT_SIG_PAT_RST_TEMP				= 0,
	MPU9250_BIT_USR_CONTROLFIFO_EN				= 6,
	MPU9250_BIT_USR_CONTROLI2C_MST_EN			= 5,
	MPU9250_BIT_USR_CONTROLI2C_IF_DIS			= 4,
	MPU9250_BIT_USR_CONTROLFIFO_RST				= 2,
	MPU9250_BIT_USR_CONTROLI2C_MST_RST			= 1,
	MPU9250_BIT_USR_CONTROLSIG_COND_RST			= 0,
	MPU9250_BIT_PWR_MGMT_1_H_RESET				= 7,
	MPU9250_BIT_PWR_MGMT_1_SLEEP				= 6,
	MPU9250_BIT_PWR_MGMT_1_CYCLE				= 5,
	MPU9250_BIT_PWR_MGMT_1_GYRO_STANDBY			= 4,
	MPU9250_BIT_PWR_MGMT_1_PD_PTAT				= 3,
	MPU9250_BIT_PWR_MGMT_1_CLKSEL_0				= 0,
	MPU9250_BIT_PWR_MGMT_2_DIS_XA				= 5,
	MPU9250_BIT_PWR_MGMT_2_DIS_YA				= 4,
	MPU9250_BIT_PWR_MGMT_2_DIS_ZA				= 3,
	MPU9250_BIT_PWR_MGMT_2_DIS_XG				= 2,
	MPU9250_BIT_PWR_MGMT_2_DIS_YG				= 1,
	MPU9250_BIT_PWR_MGMT_2_DIS_ZG				= 0,
	MPU9250_BIT_INT_PIN_LEVEL					= 7,
	MPU9250_BIT_INT_PIN_DRIVER					= 6,
	MPU9250_BIT_INT_PIN_LATCH					= 5,
	MPU9250_BIT_INT_PIN_AUTO_RESET				= 4,
	MPU9250_BIT_FSYNC_LEVEL						= 3,
	MPU9250_BIT_FSYNC_MODE_EN					= 2,
	MPU9250_BIT_BYPASS_EN						= 1,
	MPU9250_BIT_WAKE_ON_MOTION_EN				= 6,
	MPU9250_BIT_FIFO_OVERFLOW_EN				= 4,
	MPU9250_BIT_FSYNC_INT_EN					= 3,
	MPU9250_BIT_RAW_DATA_READY_EN				= 0,
	MPU9250_BIT_INT_STATUS_WOM					= 6,
	MPU9250_BIT_INT_STATUS_FIFO_OVERFLOW		= 4,
	MPU9250_BIT_INT_STATUS_FSYNC				= 3,
	MPU9250_BIT_INT_STATUS_RAW_DATA_RDY			= 0,
} mpu9250RegisterBit_e;

// -----------------------------------------------------------------------------
// MPU9250 register addresses
// -----------------------------------------------------------------------------

typedef enum mpu9250Register_e {
	// Self test registers
	MPU9250_REG_ACCEL_SELF_TEST_X				= 0x0D,
	MPU9250_REG_ACCEL_SELF_TEST_Y				= 0x0E,
	MPU9250_REG_ACCEL_SELF_TEST_Z				= 0x0F,
	MPU9250_REG_GYRO_SELF_TEST_X				= 0x00,
	MPU9250_REG_GYRO_SELF_TEST_Y				= 0x01,
	MPU9250_REG_GYRO_SELF_TEST_Z				= 0x02,

	// Offset registers
	MPU9250_REG_ACCEL_OFFSET_XH					= 0x77,
	MPU9250_REG_ACCEL_OFFSET_XL					= 0x78,
	MPU9250_REG_ACCEL_OFFSET_YH					= 0x7A,
	MPU9250_REG_ACCEL_OFFSET_YL					= 0x7B,
	MPU9250_REG_ACCEL_OFFSET_ZH					= 0x7D,
	MPU9250_REG_ACCEL_OFFSET_ZL					= 0x7E,
	MPU9250_REG_GYRO_OFFSET_XH					= 0x13,
	MPU9250_REG_GYRO_OFFSET_XL					= 0x14,
	MPU9250_REG_GYRO_OFFSET_YH					= 0x15,
	MPU9250_REG_GYRO_OFFSET_YL					= 0x16,
	MPU9250_REG_GYRO_OFFSET_ZH					= 0x17,
	MPU9250_REG_GYRO_OFFSET_ZL					= 0x18,

	// Configuration registers
	MPU9250_REG_ACCEL_CONFIG_1					= 0x1C,
	MPU9250_REG_ACCEL_CONFIG_2					= 0x1D,
	MPU9250_REG_ACCEL_LOW_POWER_ODR				= 0x1E,
	MPU9250_REG_CONFIG							= 0x1A,
	MPU9250_REG_GYRO_CONFIG						= 0x1B,
	MPU9250_REG_MOT_DETECT_CONTROL				= 0x69,
	MPU9250_REG_PWR_MGMT_1						= 0x6B,
	MPU9250_REG_PWR_MGMT_2						= 0x6C,
	MPU9250_REG_SAMPLE_RATE_DIV					= 0x19,
	MPU9250_REG_SIGNAL_PATH_RESET				= 0x68,
	MPU9250_REG_USER_CONTROL					= 0x6A,
	MPU9250_REG_WOM_THR							= 0x1F,

	// FIFO registers
	MPU9250_REG_FIFO_COUNT_H					= 0x72,
	MPU9250_REG_FIFO_COUNT_L					= 0x73,
	MPU9250_REG_FIFO_EN							= 0x23,
	MPU9250_REG_FIFO_R_W						= 0x74,

	// I2C master registers
	MPU9250_REG_I2C_MASTER_CONTROL				= 0x24,
	MPU9250_REG_I2C_MASTER_DELAY_CONTROL		= 0x67,
	MPU9250_REG_I2C_MASTER_STATUS				= 0x36,
	MPU9250_REG_I2C_SLV0_ADDRESS				= 0x25,
	MPU9250_REG_I2C_SLV0_CONTROL				= 0x27,
	MPU9250_REG_I2C_SLV0_DO						= 0x63,
	MPU9250_REG_I2C_SLV0_REG					= 0x26,
	MPU9250_REG_I2C_SLV1_ADDRESS				= 0x28,
	MPU9250_REG_I2C_SLV1_CONTROL				= 0x2A,
	MPU9250_REG_I2C_SLV1_DO						= 0x64,
	MPU9250_REG_I2C_SLV1_REG					= 0x29,
	MPU9250_REG_I2C_SLV2_ADDRESS				= 0x2B,
	MPU9250_REG_I2C_SLV2_CONTROL				= 0x2D,
	MPU9250_REG_I2C_SLV2_DO						= 0x65,
	MPU9250_REG_I2C_SLV2_REG					= 0x2C,
	MPU9250_REG_I2C_SLV3_ADDRESS				= 0x2E,
	MPU9250_REG_I2C_SLV3_CONTROL				= 0x30,
	MPU9250_REG_I2C_SLV3_DO						= 0x66,
	MPU9250_REG_I2C_SLV3_REG					= 0x2F,
	MPU9250_REG_I2C_SLV4_ADDRESS				= 0x31,
	MPU9250_REG_I2C_SLV4_CONTROL				= 0x34,
	MPU9250_REG_I2C_SLV4_DI						= 0x35,
	MPU9250_REG_I2C_SLV4_DO						= 0x33,
	MPU9250_REG_I2C_SLV4_REG					= 0x32,

	// Interrupt registers
	MPU9250_REG_INT_ENABLE						= 0x38,
	MPU9250_REG_INT_PIN_CONFIG					= 0x37,
	MPU9250_REG_INT_STATUS						= 0x3A,

	// Data registers
	MPU9250_REG_ACCEL_DATA_XH					= 0x3B,
	MPU9250_REG_ACCEL_DATA_XL					= 0x3C,
	MPU9250_REG_ACCEL_DATA_YH					= 0x3D,
	MPU9250_REG_ACCEL_DATA_YL					= 0x3E,
	MPU9250_REG_ACCEL_DATA_ZH					= 0x3F,
	MPU9250_REG_ACCEL_DATA_ZL					= 0x40,
	MPU9250_REG_GYRO_DATA_XH					= 0x43,
	MPU9250_REG_GYRO_DATA_XL					= 0x44,
	MPU9250_REG_GYRO_DATA_YH					= 0x45,
	MPU9250_REG_GYRO_DATA_YL					= 0x46,
	MPU9250_REG_GYRO_DATA_ZH					= 0x47,
	MPU9250_REG_GYRO_DATA_ZL					= 0x48,
	MPU9250_REG_TEMP_DATA_H						= 0x41,
	MPU9250_REG_TEMP_DATA_L						= 0x42,

	// External sensor data registers
	MPU9250_REG_EXT_SENS_DATA_00				= 0x49,
	MPU9250_REG_EXT_SENS_DATA_01				= 0x4A,
	MPU9250_REG_EXT_SENS_DATA_02				= 0x4B,
	MPU9250_REG_EXT_SENS_DATA_03				= 0x4C,
	MPU9250_REG_EXT_SENS_DATA_04				= 0x4D,
	MPU9250_REG_EXT_SENS_DATA_05				= 0x4E,
	MPU9250_REG_EXT_SENS_DATA_06				= 0x4F,
	MPU9250_REG_EXT_SENS_DATA_07				= 0x50,
	MPU9250_REG_EXT_SENS_DATA_08				= 0x51,
	MPU9250_REG_EXT_SENS_DATA_09				= 0x52,
	MPU9250_REG_EXT_SENS_DATA_10				= 0x53,
	MPU9250_REG_EXT_SENS_DATA_11				= 0x54,
	MPU9250_REG_EXT_SENS_DATA_12				= 0x55,
	MPU9250_REG_EXT_SENS_DATA_13				= 0x56,
	MPU9250_REG_EXT_SENS_DATA_14				= 0x57,
	MPU9250_REG_EXT_SENS_DATA_15				= 0x58,
	MPU9250_REG_EXT_SENS_DATA_16				= 0x59,
	MPU9250_REG_EXT_SENS_DATA_17				= 0x5A,
	MPU9250_REG_EXT_SENS_DATA_18				= 0x5B,
	MPU9250_REG_EXT_SENS_DATA_19				= 0x5C,
	MPU9250_REG_EXT_SENS_DATA_20				= 0x5D,
	MPU9250_REG_EXT_SENS_DATA_21				= 0x5E,
	MPU9250_REG_EXT_SENS_DATA_22				= 0x5F,
	MPU9250_REG_EXT_SENS_DATA_23				= 0x60,

	// Who am I register
	MPU9250_REG_WHO_AM_I						= 0x75,
} mpu9250Register_e;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Mpu9250::Mpu9250(void)
{
	// Reset data members
	this->_clearData();

	// Mark passage for debug
	debugMark();

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return;
}

Mpu9250::~Mpu9250(void)									// TODO: Implement this function
{
	return;
}

// =============================================================================
// Inherited methods - Public
// =============================================================================

// NONE

// =============================================================================
// Inherited methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Class own methods - Public
// =============================================================================

bool Mpu9250::init(Handler *twiHandler_p, bool useAlternateAddress_p)
{
	// Local variables
	uint8_t auxBuff;

	// Mark passage for debug
	debugMark();

	// Reset data members
	this->_initialized = false;
	this->_handler = nullptr;
	this->_activateDevice = nullptr;
	this->_deactivateDevice = nullptr;
	this->_useSpi = false;
	this->_i2c7bitAddress = 0;

	// Check for errors
	if(!isPointerValid(twiHandler_p)) {
		this->_handler = nullptr;
		this->_lastError = Error::HANDLER_POINTER_NULL;
		debugMessage(Error::HANDLER_POINTER_NULL);
		return false;
	} else {
		switch(twiHandler_p->getHandlerType()) {
		case Handler::HandlerType::TWI:
			break;
		case Handler::HandlerType::SPI:
			this->_lastError = Error::UNKNOWN;			// TODO: Create specific error code
			debugMessage(Error::UNKNOWN);				// TODO: Create specific error code
			return false;
		default:
			this->_lastError = Error::HANDLER_UNSUPPORTED;
			debugMessage(Error::HANDLER_UNSUPPORTED);
			return false;
		}
	}

	// Update data members
	this->_handler = twiHandler_p;
	if(useAlternateAddress_p) {
		this->_i2c7bitAddress = MPU9250_SLAVE_ADDRESS_ALTERNATE;
	} else {
		this->_i2c7bitAddress = MPU9250_SLAVE_ADDRESS_NORMAL;
	}
	this->_useSpi = false;

	// Get device ID
	if(this->_read(MPU9250_REG_WHO_AM_I, &auxBuff, 1)) {
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}
	// Check device ID
	if(auxBuff != MPU9250_WHO_AM_I) {
		// Returns error
		this->_lastError = Error::DEVICE_ID_MATCH_FAILED;
		debugMessage(Error::DEVICE_ID_MATCH_FAILED);
		return false;
	}

	// Reset device
	if(!this->reset()) {
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}

	// Update data members
	this->_initialized = true;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Mpu9250::init(Handler *spiHandler_p, void (*actDevFuncCallback_p)(void), void (*deactDevFuncCallback_p)(void))
{
	// Local variables
	uint8_t auxBuff;

	// Mark passage for debug
	debugMark();

	// Reset data members
	this->_initialized = false;
	this->_handler = nullptr;
	this->_activateDevice = nullptr;
	this->_deactivateDevice = nullptr;
	this->_useSpi = false;
	this->_i2c7bitAddress = 0;

	// Check for errors
	if(!isPointerValid(actDevFuncCallback_p) || !isPointerValid(deactDevFuncCallback_p)) {
		this->_handler = nullptr;
		this->_lastError = Error::FUNCTION_POINTER_NULL;
		debugMessage(Error::FUNCTION_POINTER_NULL);
		return false;
	}
	if(!isPointerValid(spiHandler_p)) {
		this->_handler = nullptr;
		this->_lastError = Error::HANDLER_POINTER_NULL;
		debugMessage(Error::HANDLER_POINTER_NULL);
		return false;
	} else {
		switch(spiHandler_p->getHandlerType()) {
		case Handler::HandlerType::TWI:
			this->_lastError = Error::UNKNOWN;			// TODO: Create specific error code
			debugMessage(Error::UNKNOWN);				// TODO: Create specific error code
			return false;
		case Handler::HandlerType::SPI:
			break;
		default:
			this->_lastError = Error::HANDLER_UNSUPPORTED;
			debugMessage(Error::HANDLER_UNSUPPORTED);
			return false;
		}
	}

	// Update data members
	this->_handler = spiHandler_p;
	this->_activateDevice = actDevFuncCallback_p;
	this->_deactivateDevice = deactDevFuncCallback_p;
	this->_useSpi = true;

	// Get device ID
	if(this->_read(MPU9250_REG_WHO_AM_I, &auxBuff, 1)) {
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}
	// Check device ID
	if(auxBuff != MPU9250_WHO_AM_I) {
		// Returns error
		this->_lastError = Error::DEVICE_ID_MATCH_FAILED;
		debugMessage(Error::DEVICE_ID_MATCH_FAILED);
		return false;
	}

	// Reset device
	if(!this->reset()) {
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}

	// Update data members
	this->_initialized = true;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Mpu9250::reset(ResetFlags reset_p)
{
	// Local variables
	bool auxBool = false;

	// Mark passage for debug
	debugMark();

	// Signal path reset
	this->_resetGyro = (reset_p & ResetFlags::RESET_GYRO);
	this->_resetAccel = (reset_p & ResetFlags::RESET_ACCEL);
	this->_resetTemp = (reset_p & ResetFlags::RESET_TEMP);
	if(this->_resetGyro | this->_resetAccel | this->_resetTemp) {
		auxBool = this->_updateSignalPathReset();
		this->_resetGyro = false;
		this->_resetAccel = false;
		this->_resetTemp = false;
		if(!auxBool) {
			return false;
		}
	}




	// Check for errors
	if(!isPointerValid(this->_handler)) {
		// Returns error
		this->_lastError = Error::HANDLER_POINTER_NULL;
		debugMessage(Error::HANDLER_POINTER_NULL);
		return false;
	} else if(this->_handler->getHandlerType() != Handler::HandlerType::TWI) {
		this->_lastError = Error::HANDLER_UNSUPPORTED;
		debugMessage(Error::HANDLER_UNSUPPORTED);
		return false;
	}

	// Mount data package
	auxBuff = (1 << MAX30105_BIT_CONFIGURATION_RESET);

	// Write data to device
	if(!this->_write(MAX30105_REG_MODE_CONFIGURATION, &auxBuff, 1)) {
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}

	// Test until reset flag is cleared by hardware
	delayMs(10);			// TODO: Pool for RESET FLAG until its cleared by hardware

	// Reset data members
	this->_clearData();

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}







// =============================================================================
// Class own methods - Private
// =============================================================================

void Mpu9250::_clearData(void)
{
	// Mark passage for debug
	debugMark();

	//     /////////////////     PERIPHERAL HANDLER     /////////////////     //
	this->_activateDevice				= nullptr;
	this->_commPortSet					= false;
	this->_deactivateDevice				= nullptr;
	this->_handler						= nullptr;
	this->_i2c7bitAddress				= 0x00;
	this->_useSpi						= false;

	//     /////////////////     CONTROL AND STATUS     /////////////////     //
	this->_initialized					= false;
	this->_lastError = Error::NONE;

	//     ////////////////     SENSOR CONFIGURATION     ////////////////     //
	this->_accelDisableX				= false;
	this->_accelDisableY				= false;
	this->_accelDisableZ				= false;
	this->_accelDlpfCfg					= AccelDigitalFilter::FILTER_FREQ_218_HZ;
	this->_accelFChoiceB				= false;
	this->_accelFullScale				= AccelFullScale::FULL_SCALE_2_G;
	this->_sampleRateDivider			= 0;
	this->_gyroDisableX					= false;
	this->_gyroDisableY					= false;
	this->_gyroDisableZ					= false;
	this->_gyroDlpfCfg					= GyroDigitalFilter::FILTER_FREQ_250_HZ;
	this->_gyroFChoiceB					= 0;
	this->_gyroFullScale				= GyroFullScale::FULL_SCALE_250_DPS;
	this->_accelXSelfTestEnabled		= false;
	this->_accelYSelfTestEnabled		= false;
	this->_accelZSelfTestEnabled		= false;
	this->_accelSelfTest[0]				= 0;
	this->_accelSelfTest[1]				= 0;
	this->_accelSelfTest[2]				= 0;
	this->_gyroXSelfTestEnabled			= false;
	this->_gyroYSelfTestEnabled			= false;
	this->_gyroZSelfTestEnabled			= false;
	this->_gyroSelfTest[0]				= 0;
	this->_gyroSelfTest[1]				= 0;
	this->_gyroSelfTest[2]				= 0;

	//     /////////////////    RAW DATA MANAGEMENT     /////////////////     //
	this->_accelData[0]					= 0;
	this->_accelData[1]					= 0;
	this->_accelData[2]					= 0;
	this->_accelOffset[0]				= 0;
	this->_accelOffset[1]				= 0;
	this->_accelOffset[2]				= 0;
	this->_gyroData[0]					= 0;
	this->_gyroData[1]					= 0;
	this->_gyroData[2]					= 0;
	this->_gyroOffset[0]				= 0;
	this->_gyroOffset[1]				= 0;
	this->_gyroOffset[2]				= 0;
	this->_tempData						= 0;

	//     /////////////////     FIFO CONFIGURATION     /////////////////     //
	this->_fifoAccelStore				= false;
	this->_fifoEnable					= false;
	this->_fifoGyroXStore				= false;
	this->_fifoGyroYStore				= false;
	this->_fifoGyroZStore				= false;
	this->_fifoLenght					= 0;
	this->_fifoMode						= false;
	this->_fifoSlave0Store				= false;
	this->_fifoSlave1Store				= false;
	this->_fifoSlave2Store				= false;
	this->_fifoSlave3Store				= false;
	this->_fifoTempStore				= false;


	//     /////////////    I2C MASTER BUS DATA MEMBERS     /////////////     //
	this->_i2cMultiMaster				= false;
	this->_i2cWaitForExtSensor			= false;
	this->_i2cStopBetweenTransmissions	= false;
	this->_i2cMasterClock				= false;
	this->_i2cSlave0ReadWrite			= false;
	this->_i2cSlave0Address				= 0;
	this->_i2cSlave1ReadWrite			= false;
	this->_i2cSlave1Address				= 0;
	this->_i2cSlave2ReadWrite			= false;
	this->_i2cSlave2Address				= 0;
	this->_i2cSlave3ReadWrite			= false;
	this->_i2cSlave3Address				= 0;
	this->_i2cSlave4ReadWrite			= false;
	this->_i2cSlave4Address				= 0;
	this->_i2cSlave0Register			= 0;
	this->_i2cSlave1Register			= 0;
	this->_i2cSlave2Register			= 0;
	this->_i2cSlave3Register			= 0;
	this->_i2cSlave4Register			= 0;
	this->_i2cSlave0DataOut				= 0;
	this->_i2cSlave1DataOut				= 0;
	this->_i2cSlave2DataOut				= 0;
	this->_i2cSlave3DataOut				= 0;
	this->_i2cSlave4DataOut				= 0;
	this->_i2cSlave0Enable				= false;
	this->_i2cSlave0SwapBytes			= false;
	this->_i2cSlave0RegisterDisable		= false;
	this->_i2cSlave0GroupingSkipFirst	= false;
	this->_i2cSlave0DataLength			= 0;
	this->_i2cSlave1Enable				= false;
	this->_i2cSlave1SwapBytes			= false;
	this->_i2cSlave1RegisterDisable		= false;
	this->_i2cSlave1GroupingSkipFirst	= false;
	this->_i2cSlave1DataLength			= 0;
	this->_i2cSlave2Enable				= false;
	this->_i2cSlave2SwapBytes			= false;
	this->_i2cSlave2RegisterDisable		= false;
	this->_i2cSlave2GroupingSkipFirst	= false;
	this->_i2cSlave2DataLength			= 0;
	this->_i2cSlave3Enable				= false;
	this->_i2cSlave3SwapBytes			= false;
	this->_i2cSlave3RegisterDisable		= false;
	this->_i2cSlave3GroupingSkipFirst	= false;
	this->_i2cSlave3DataLength			= 0;
	this->_i2cSlave4Enable				= false;
	this->_i2cSlave4IntEnable			= false;
	this->_i2cSlave4RegisterDisable		= false;
	this->_i2cSlave4Delay				= 0;
	this->_i2cBypassEnable				= false;
	this->_i2cExtSensorShadowDelayEnable	= false;
	this->_i2cSlave4DelayEnable			= false;
	this->_i2cSlave3DelayEnable			= false;
	this->_i2cSlave2DelayEnable			= false;
	this->_i2cSlave1DelayEnable			= false;
	this->_i2cSlave0DelayEnable			= false;
	this->_i2cMasterEnable				= false;

	//     ///////////////    INTERRUPT CONFIGURATION     ///////////////     //
	this->_intPinActiveLevel			= false;
	this->_intPinOpenDrain				= false;
	this->_intPinLatchEnable			= false;
	this->_intPinAutoClear				= false;
	this->_intPinFsyncActiveLevel		= false;
	this->_intFsyncModeEnable			= false;
	this->_intWakeOnMotionEnable		= false;
	this->_intFifoOverfowEnable			= false;
	this->_intFsyncEnable				= false;
	this->_intRawDataReadyEnable		= false;

	//     //////////////////     INTERRUPT STATUS     //////////////////     //
	this->_intWakeOnMotionFlag			= false;
	this->_intFifoOverflowFlag			= false;
	this->_intFsyncFlag					= false;
	this->_intI2cDataReadyFlag			= false;

	//     //////////////////     MOTION DETECTION     //////////////////     //
	this->_wakeOnMotionThreshold		= 0;
	this->_wakeOnMotionMode				= false;
	this->_wakeOnMotionEnable			= false;

	//     //////////////////     POWER MANAGEMENT     //////////////////     //
	this->_cycleEnable					= false;
	this->_sleepEnable					= false;
	this->_gyroStandby					= false;
	this->_ptatDisable					= false;
	this->_clockSelection				= 0;
	this->_lowPowerOscClock				= 0;

	//     /////////////    EXTERNAL SENSOR DATA MEMBER     /////////////     //
	this->_extenalSensorData[0]			= 0;
	this->_extenalSensorData[1]			= 0;
	this->_extenalSensorData[2]			= 0;
	this->_extenalSensorData[3]			= 0;
	this->_extenalSensorData[4]			= 0;
	this->_extenalSensorData[5]			= 0;
	this->_extenalSensorData[6]			= 0;
	this->_extenalSensorData[7]			= 0;
	this->_extenalSensorData[8]			= 0;
	this->_extenalSensorData[9]			= 0;
	this->_extenalSensorData[10]		= 0;
	this->_extenalSensorData[11]		= 0;
	this->_extenalSensorData[12]		= 0;
	this->_extenalSensorData[13]		= 0;
	this->_extenalSensorData[14]		= 0;
	this->_extenalSensorData[15]		= 0;
	this->_extenalSensorData[16]		= 0;
	this->_extenalSensorData[17]		= 0;
	this->_extenalSensorData[18]		= 0;
	this->_extenalSensorData[19]		= 0;
	this->_extenalSensorData[20]		= 0;
	this->_extenalSensorData[21]		= 0;
	this->_extenalSensorData[22]		= 0;
	this->_extenalSensorData[23]		= 0;
	this->_extSyncSet					= 0;

	//     /////////////////////    RESET FLAGS     /////////////////////     //
	this->_resetGyro					= false;
	this->_resetAccel					= false;
	this->_resetTemp					= false;
	this->_resetFifo					= false;
	this->_resetI2c						= false;
	this->_resetSignal					= false;

	// Return successfully
	return;
}

bool Mpu9250::_read(uint8_t regAddr_p, uint8_t *dataBuffer_p, uint16_t bytesToRead_p)
{
	return true;
}

bool Mpu9250::_write(uint8_t regAddr_p, uint8_t *dataBuffer_p, uint16_t bytesToWrite_p)
{
	return true;
}



/********                      AQUI                      ********/
/********                      AQUI                      ********/
/********                      AQUI                      ********/
/********                      AQUI                      ********/
/********                      AQUI                      ********/
/********                      AQUI                      ********/

/*

bool Mpu9250::init(Handler *handler_p)
{
	return true;
}

bool Mpu9250::setSpiFunctions(void (*actDevFuncCallback_p)(void), void (*deactDevFuncCallback_p)(void))
{
	return true;
}

bool Mpu9250::setTwiAddress(bool useAlternateAddress_p)
{
	return true;
}

bool Mpu9250::restart(void)
{
	return true;
}

bool Mpu9250::reset(ResetPathFlags resetPaths_p)
{
	return true;
}

// -----------------------------------------------------------------------------
// CHECK STATUS
// -----------------------------------------------------------------------------

Error Mpu9250::getLastError(void)
{
	return this->_lastError;
}

// -----------------------------------------------------------------------------
// DEVICE CONFIGURATION
// -----------------------------------------------------------------------------

bool Mpu9250::configAccel(Axis axis_p, AccelFullScale scale_p, AccelSampleRate sampleRate_p, AccelDigitalFilter filter_p)
{
	return true;
}

bool Mpu9250::configGyro(Axis axis_p, GyroFullScale scale_p, GyroSampleRate sampleRate_p, GyroDigitalFilter filter_p)
{
	return true;
}

bool Mpu9250::performSelfTest(Axis accelAxis_p, Axis gyroAxis_p)
{
	return true;
}

// -----------------------------------------------------------------------------
// RAW DATA MANAGEMENT
// -----------------------------------------------------------------------------

bool Mpu9250::getAccelData(int16_t *accelBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::getAccelOffset(int16_t *accelBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::setAccelOffset(int16_t *accelBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::getGyroData(int16_t *gyroBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::getGyroOffset(int16_t *gyroBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::setGyroOffset(int16_t *gyroBuff_p, Axis axis_p)
{
	return true;
}

bool Mpu9250::getTempData(int16_t *temp_p)
{
	return true;
}

// -----------------------------------------------------------------------------
// FIFO CONFIGURATION
// -----------------------------------------------------------------------------

bool Mpu9250::configFifo(void)
{
	return true;
}

bool Mpu9250::configIntPin(LogicLevel pinLevel_p, DriverMode pinDriver_p, bool pinLatch_p, bool pinAutoReset_p)
{
	return true;
}

bool Mpu9250::setIntDataReady(bool enabled_p)
{
	return true;
}

// -----------------------------------------------------------------------------
// OTHER TEST FUNCTIONS
// -----------------------------------------------------------------------------

// void Mpu9250::readAll(uint8_t *buffer, uint8_t *size)
// {
// 	return;
// }

// void Mpu9250::readMag(int16_t *magBuff)
// {
// 	return;
// }

// =============================================================================
// Class own methods - Private
// =============================================================================

// -----------------------------------------------------------------------------
// INTERFACE
// -----------------------------------------------------------------------------

bool Mpu9250::_deinitialize(void)
{
	return true;
}

bool Mpu9250::_initialize(void)
{
	return true;
}

bool Mpu9250::_getWhoAmI(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// CONFIGURATION
// -----------------------------------------------------------------------------

bool Mpu9250::_updateSampleRateDivider(void)
{
	return true;
}

bool Mpu9250::_updateAccelConfig(void)
{
	return true;
}

bool Mpu9250::_updateAccelConfig2(void)
{
	return true;
}

bool Mpu9250::_updatePowerManagementControl2(void)
{
	return true;
}

bool Mpu9250::_updateConfig(void)
{
	return true;
}

bool Mpu9250::_updateGyroConfig(void)
{
	return true;
}

bool Mpu9250::_getAccelSelfTest(void)
{
	return true;
}

bool Mpu9250::_getGyroSelfTest(void)
{
	return true;
}

bool Mpu9250::_updateUserControl(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// RAW DATA MANAGEMENT
// -----------------------------------------------------------------------------

bool Mpu9250::_getAccelData(void)
{
	return true;
}

bool Mpu9250::_getAccelOffset(void)
{
	return true;
}

bool Mpu9250::_getGyroData(void)
{
	return true;
}

bool Mpu9250::_getGyroOffset(void)
{
	return true;
}

bool Mpu9250::_getTempData(void)
{
	return true;
}

bool Mpu9250::_updateAccelOffset(void)
{
	return true;
}

bool Mpu9250::_updateGyroOffset(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// FIFO
// -----------------------------------------------------------------------------

bool Mpu9250::_updateFifoEnable(void)
{
	return true;
}

bool Mpu9250::_getFifoCount(void)
{
	return true;
}

bool Mpu9250::_getFifoReadWrite(void)
{
	return true;
}

bool Mpu9250::_updateFifoReadWrite(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// MOTION CONTROL
// -----------------------------------------------------------------------------

bool Mpu9250::_updateWakeUpMotionThreshold(void)
{
	return true;
}

bool Mpu9250::_updateMotionDetectControl(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// I2C
// -----------------------------------------------------------------------------

bool Mpu9250::_updateI2cMasterControl(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave0Address(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave0Control(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave0Register(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave1Address(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave1Control(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave1Register(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave2Address(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave2Control(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave2Register(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave3Address(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave3Control(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave3Register(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave4Address(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave4Control(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave4Register(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave4DataOut(void)
{
	return true;
}

bool Mpu9250::_getI2cSlave4DataIn(void)
{
	return true;
}

bool Mpu9250::_getI2cMasterStatus(void)
{
	return true;
}

bool Mpu9250::_updateI2cMasterControlDelay(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave0DataOut(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave1DataOut(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave2DataOut(void)
{
	return true;
}

bool Mpu9250::_updateI2cSlave3DataOut(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// INTERRUPT
// -----------------------------------------------------------------------------

bool Mpu9250::_updateIntPinConfig(void)
{
	return true;
}

bool Mpu9250::_updateIntEnable(void)
{
	return true;
}

bool Mpu9250::_getInterruptStatus(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// EXTERNAL SENSOR
// -----------------------------------------------------------------------------

bool Mpu9250::_readExtSensData(uint8_t first_p, uint8_t total_p)
{
	return true;
}

// -----------------------------------------------------------------------------
// RESET
// -----------------------------------------------------------------------------

bool Mpu9250::_updateSignalPathReset(void)
{
	return true;
}

bool Mpu9250::_updatePowerManagementControl1(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// LOW POWER
// -----------------------------------------------------------------------------

bool Mpu9250::_updateLowPowerAccelODR(void)
{
	return true;
}

// -----------------------------------------------------------------------------
// LOW LEVEL COMMUNICATION
// -----------------------------------------------------------------------------

bool inlined Mpu9250::_readFromDevice(uint8_t reg_p, uint8_t *buffer_p, uint8_t size_p)
{
	return true;
}

bool inlined Mpu9250::_writeAtDevice(uint8_t reg_p, uint8_t *buffer_p, uint8_t size_p)
{
	return true;
}
*/

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE
