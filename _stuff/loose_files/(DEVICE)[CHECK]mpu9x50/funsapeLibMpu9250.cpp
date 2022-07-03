/* 
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibMpu9250.cpp
 * Module:			MPU-9250 interface module for FunSAPE++ Embedded Library
 * 					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// 
// System file dependencies
// 

#include "funsapeLibMpu9250.hpp"
#if __FUNSAPE_LIB_MPU9250_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibMpu9250.cpp] Error 102 - Build mismatch on header and source code files.
#endif

// 
// File exclusive - Constants
// 

#define MPU9250_SLAVE_ADDRESS_DEFAULT			0x68
#define MPU9250_SLAVE_ADDRESS_ALTERNATE			0x69
#define MPU9250_WHO_AM_I						0x71
#define MPU9250_RESET_DELAY						200

// Configuration Registers Addresses
#define REG_SMPLRT_DIV							0x19	// Sample Rate Divider Register
#define REG_CONFIG								0x1A	// Configuration Register
#	define BIT_CONFIG_FIFO_MODE					6
#	define BIT_CONFIG_EXT_SYNC_SET				3
#	define BIT_CONFIG_GYRO_DLPF_CFG				0
#define REG_GYRO_CONFIG							0x1B	// Gyroscope Configuration Register
#	define BIT_GYRO_CONFIG_X_ST_EN				7
#	define BIT_GYRO_CONFIG_Y_ST_EN				6
#	define BIT_GYRO_CONFIG_Z_ST_EN				5
#	define BIT_GYRO_CONFIG_FS_SEL				3
#	define BIT_GYRO_CONFIG_FCHOICE_B			0
#define REG_ACCEL_CONFIG						0x1C	// Accelerometer Configuration Registers
#	define BIT_ACCEL_CONFIG_X_ST_EN				7
#	define BIT_ACCEL_CONFIG_Y_ST_EN				6
#	define BIT_ACCEL_CONFIG_Z_ST_EN				5
#	define BIT_ACCEL_CONFIG_FS_SEL				3
#define REG_ACCEL_CONFIG2						0x1D	// ...
#	define BIT_ACCEL_CONFIG2_FCHOICE_B			3
#	define BIT_ACCEL_CONFIG2_DLPF_CFG			0
#define REG_ACCEL_LOW_POWER_ODR					0x1E	// ...
#	define BIT_ACCEL_LP_ODR_CLKSEL				0
#define REG_WOM_THR								0x1F	// Wake-on Motion Threshold Register
#define REG_SIGNAL_PATH_RESET					0x68	// Reset Register
#	define BIT_SIG_PAT_RST_GYRO					2
#	define BIT_SIG_PAT_RST_ACCEL				1
#	define BIT_SIG_PAT_RST_TEMP					0
#define REG_ACCEL_INTEL_CTRL					0x69	// Accelerometer Interrupt Control Register
#	define BIT_ACCEL_INTEL_CTRL_EN				7
#	define BIT_ACCEL_INTEL_CTRL_MODE			6
#define REG_USER_CTRL							0x6A	// User Control Register
#	define BIT_USR_CTRL_FIFO_EN					6
#	define BIT_USR_CTRL_I2C_MST_EN				5
#	define BIT_USR_CTRL_I2C_IF_DIS				4
#	define BIT_USR_CTRL_FIFO_RST				2
#	define BIT_USR_CTRL_I2C_MST_RST				1
#	define BIT_USR_CTRL_SIG_COND_RST			0
#define REG_PWR_MGMT_1							0x6B	// Power Management Registers
#	define BIT_PWR_MGMT_1_H_RESET				7
#	define BIT_PWR_MGMT_1_SLEEP					6
#	define BIT_PWR_MGMT_1_CYCLE					5
#	define BIT_PWR_MGMT_1_GYRO_STANDBY			4
#	define BIT_PWR_MGMT_1_PD_PTAT				3
#	define BIT_PWR_MGMT_1_CLKSEL0				0
#define REG_PWR_MGMT_2							0x6C	// ...
#	define BIT_PWR_MGMT_2_DIS_ACCEL_X			5
#	define BIT_PWR_MGMT_2_DIS_ACCEL_Y			4
#	define BIT_PWR_MGMT_2_DIS_ACCEL_Z			3
#	define BIT_PWR_MGMT_2_DIS_GYRO_X			2
#	define BIT_PWR_MGMT_2_DIS_GYRO_Y			1
#	define BIT_PWR_MGMT_2_DIS_GYRO_Z			0
#define REG_WHO_AM_I							0x75	// Who am I Register

// Accelerometer Registers Addresses
#define REG_ACCEL_X_SELF_TEST					0x0D	// Accelerometer Self-Test Registers
#define REG_ACCEL_Y_SELF_TEST					0x0E	// ...
#define REG_ACCEL_Z_SELF_TEST					0x0F	// ...
#define REG_ACCEL_XH_USR_OFFSET					0x77	// Accelerometer Offset Registers
#define REG_ACCEL_XL_USR_OFFSET					0x78	// ...
#define REG_ACCEL_YH_USR_OFFSET					0x7A	// ...
#define REG_ACCEL_YL_USR_OFFSET					0x7B	// ...
#define REG_ACCEL_ZH_USR_OFFSET					0x7D	// ...
#define REG_ACCEL_ZL_USR_OFFSET					0x7E	// ...
#define REG_ACCEL_OUT_XH						0x3B	// Accelerometer Measurements Registers
#define REG_ACCEL_OUT_XL						0x3C	// ...
#define REG_ACCEL_OUT_YH						0x3D	// ...
#define REG_ACCEL_OUT_YL						0x3E	// ...
#define REG_ACCEL_OUT_ZH						0x3F	// ...
#define REG_ACCEL_OUT_ZL						0x40	// ...

// Gyroscope Registers Addresses
#define REG_GYRO_X_SELF_TEST					0x00	// Gyroscope Self-Test Registers
#define REG_GYRO_Y_SELF_TEST					0x01	// ...
#define REG_GYRO_Z_SELF_TEST					0x02	// ...
#define REG_GYRO_XH_USR_OFFSET					0x13	// Gyro Offset Registers
#define REG_GYRO_XL_USR_OFFSET					0x14	// ...
#define REG_GYRO_YH_USR_OFFSET					0x15	// ...
#define REG_GYRO_YL_USR_OFFSET					0x16	// ...
#define REG_GYRO_ZH_USR_OFFSET					0x17	// ...
#define REG_GYRO_ZL_USR_OFFSET					0x18	// ...
#define REG_GYRO_OUT_XH							0x43	// Gyroscope Measurements Registers
#define REG_GYRO_OUT_XL							0x44	// ...
#define REG_GYRO_OUT_YH							0x45	// ...
#define REG_GYRO_OUT_YL							0x46	// ...
#define REG_GYRO_OUT_ZH							0x47	// ...
#define REG_GYRO_OUT_ZL							0x48	// ...

// Temperature Registers Addresses
#define REG_TEMP_OUT_H							0x41	// Temperature Measurements Registers
#define REG_TEMP_OUT_L							0x42	// ...

// FIFO Registers Addresses
#define REG_FIFO_EN								0x23	// FIFO Configuration Register
#	define BIT_FIFO_TEMP_EN						7
#	define BIT_FIFO_GYRO_X_EN					6
#	define BIT_FIFO_GYRO_Y_EN					5
#	define BIT_FIFO_GYRO_Z_EN					4
#	define BIT_FIFO_ACCEL_EN					3
#	define BIT_FIFO_SLV_2_EN					2
#	define BIT_FIFO_SLV_1_EN					1
#	define BIT_FIFO_SLV_0_EN					0
#define REG_FIFO_COUNT_H						0x72	// FIFO Configuration Registers
#define REG_FIFO_COUNT_L						0x73	// ...
#define REG_FIFO_R_W							0x74	// ...

// Interrupts Registers Addresses
#define REG_INT_CONFIG							0x37	// Interrupts Configuration Registers
#	define BIT_INT_CONFIG_INT_PIN_LEVEL			7
#	define BIT_INT_CONFIG_INT_PIN_DRIVER		6
#	define BIT_INT_CONFIG_INT_PIN_LATCH			5
#	define BIT_INT_CONFIG_INT_PIN_AUTO_RESET	4
#	define BIT_INT_CONFIG_FSYNC_PIN_LEVEL		3
#	define BIT_INT_CONFIG_FSYNC_PIN_MODE_EN		2
#	define BIT_INT_CONFIG_BYPASS_EN				1
#define REG_INT_ENABLE							0x38	// ...
#	define BIT_INT_ENABLE_WAKE_ON_MOTION_EN		6
#	define BIT_INT_ENABLE_FIFO_OVERFLOW_EN		4
#	define BIT_INT_ENABLE_FSYNC_INT_EN			3
#	define BIT_INT_ENABLE_RAW_DATA_READY_EN		0
#define REG_INT_STATUS							0x3A	// ...
#	define BIT_INT_STATUS_WAKE_ON_MOTION_INT	6
#	define BIT_INT_STATUS_FIFO_OVERFLOW_INT		4
#	define BIT_INT_STATUS_FSYNC_INT				3
#	define BIT_INT_STATUS_RAW_DATA_RDY_INT		0

// I2C Registers Addresses
#define REG_I2C_MST_CTRL						0x24	// I2C Master Configuration Registers
#	define BIT_I2C_MST_CTRL_MULT_MST_EN			7
#	define BIT_I2C_MST_CTRL_WAIT_FOR_ES			6
#	define BIT_I2C_MST_CTRL_SLV_3_FIFO_EN		5
#	define BIT_I2C_MST_CTRL_I2C_MST_P_NSR		4
#	define BIT_I2C_MST_CTRL_I2C_MST_CLK			0
#define REG_I2C_MST_DELAY_CTRL					0x67	// ...
#	define BIT_I2C_MST_DLY_CTRL_ES_SHADOW		7
#	define BIT_I2C_MST_DLY_CTRL_SLV4_DLY_EN		4
#	define BIT_I2C_MST_DLY_CTRL_SLV3_DLY_EN		3
#	define BIT_I2C_MST_DLY_CTRL_SLV2_DLY_EN		2
#	define BIT_I2C_MST_DLY_CTRL_SLV1_DLY_EN		1
#	define BIT_I2C_MST_DLY_CTRL_SLV0_DLY_EN		0
#define REG_I2C_MST_STATUS						0x36	// ...
#	define BIT_I2C_MST_STATUS_PASS_THROUGH		7
#	define BIT_I2C_MST_STATUS_SLV4_DONE			6
#	define BIT_I2C_MST_STATUS_LOST_ARB			5
#	define BIT_I2C_MST_STATUS_SLV4_NACK			4
#	define BIT_I2C_MST_STATUS_SLV3_NACK			3
#	define BIT_I2C_MST_STATUS_SLV2_NACK			2
#	define BIT_I2C_MST_STATUS_SLV1_NACK			1
#	define BIT_I2C_MST_STATUS_SLV0_NACK			0
#define REG_I2C_SLV0_ADDR						0x25	// I2C Slave 0 Configuration Registers
#	define BIT_I2C_SLV0_ADDR_RNW				7
#	define BIT_I2C_SLV0_ADDR_ID					0
#define REG_I2C_SLV0_REG						0x26	// ...
#define REG_I2C_SLV0_DO							0x63	// ...
#define REG_I2C_SLV0_CTRL						0x27	// ...
#	define BIT_I2C_SLV0_CTRL_EN					7
#	define BIT_I2C_SLV0_CTRL_BYTE_SW			6
#	define BIT_I2C_SLV0_CTRL_REG_DIS			5
#	define BIT_I2C_SLV0_CTRL_GRP				4
#	define BIT_I2C_SLV0_CTRL_LENG				0
#define REG_I2C_SLV1_ADDR						0x28	// I2C Slave 1 Configuration Registers
#	define BIT_I2C_SLV1_ADDR_RNW				7
#	define BIT_I2C_SLV1_ADDR_ID					0
#define REG_I2C_SLV1_REG						0x29	// ...
#define REG_I2C_SLV1_DO							0x64	// ...
#define REG_I2C_SLV1_CTRL						0x2A	// ...
#	define BIT_I2C_SLV1_CTRL_EN					7
#	define BIT_I2C_SLV1_CTRL_BYTE_SW			6
#	define BIT_I2C_SLV1_CTRL_REG_DIS			5
#	define BIT_I2C_SLV1_CTRL_GRP				4
#	define BIT_I2C_SLV1_CTRL_LENG				0
#define REG_I2C_SLV2_ADDR						0x2B	// I2C Slave 2 Configuration Registers
#	define BIT_I2C_SLV2_ADDR_RNW				7
#	define BIT_I2C_SLV2_ADDR_ID					0
#define REG_I2C_SLV2_REG						0x2C	// ...
#define REG_I2C_SLV2_DO							0x65	// ...
#define REG_I2C_SLV2_CTRL						0x2D	// ...
#	define BIT_I2C_SLV2_CTRL_EN					7
#	define BIT_I2C_SLV2_CTRL_BYTE_SW			6
#	define BIT_I2C_SLV2_CTRL_REG_DIS			5
#	define BIT_I2C_SLV2_CTRL_GRP				4
#	define BIT_I2C_SLV2_CTRL_LENG				0
#define REG_I2C_SLV3_ADDR						0x2E	// I2C Slave 3 Configuration Registers
#	define BIT_I2C_SLV3_ADDR_RNW				7
#	define BIT_I2C_SLV3_ADDR_ID					0
#define REG_I2C_SLV3_REG						0x2F	// ...
#define REG_I2C_SLV3_DO							0x66	// ...
#define REG_I2C_SLV3_CTRL						0x30	// ...
#	define BIT_I2C_SLV3_CTRL_EN					7
#	define BIT_I2C_SLV3_CTRL_BYTE_SW			6
#	define BIT_I2C_SLV3_CTRL_REG_DIS			5
#	define BIT_I2C_SLV3_CTRL_GRP				4
#	define BIT_I2C_SLV3_CTRL_LENG				0
#define REG_I2C_SLV4_ADDR						0x31	// I2C Slave 4 Configuration Registers
#	define BIT_I2C_SLV4_ADDR_RNW				7
#	define BIT_I2C_SLV4_ADDR_ID					0
#define REG_I2C_SLV4_REG						0x32	// ...
#define REG_I2C_SLV4_DO							0x33	// ...
#define REG_I2C_SLV4_CTRL						0x34	// ...
#	define BIT_I2C_SLV4_CTRL_EN					7
#	define BIT_I2C_SLV4_CTRL_DONE_INT_EN		6
#	define BIT_I2C_SLV4_CTRL_REG_DIS			5
#	define BIT_I2C_SLV4_CTRL_MST_DELAY			0
#define REG_I2C_SLV4_DI							0x35	// ...

// External Sensor Data Registers Addresses
#define REG_EXT_SENS_DATA_00					0x49	// External Sensor Data Registers
#define REG_EXT_SENS_DATA_01					0x4A	// ...
#define REG_EXT_SENS_DATA_02					0x4B	// ...
#define REG_EXT_SENS_DATA_03					0x4C	// ...
#define REG_EXT_SENS_DATA_04					0x4D	// ...
#define REG_EXT_SENS_DATA_05					0x4E	// ...
#define REG_EXT_SENS_DATA_06					0x4F	// ...
#define REG_EXT_SENS_DATA_07					0x50	// ...
#define REG_EXT_SENS_DATA_08					0x51	// ...
#define REG_EXT_SENS_DATA_09					0x52	// ...
#define REG_EXT_SENS_DATA_10					0x53	// ...
#define REG_EXT_SENS_DATA_11					0x54	// ...
#define REG_EXT_SENS_DATA_12					0x55	// ...
#define REG_EXT_SENS_DATA_13					0x56	// ...
#define REG_EXT_SENS_DATA_14					0x57	// ...
#define REG_EXT_SENS_DATA_15					0x58	// ...
#define REG_EXT_SENS_DATA_16					0x59	// ...
#define REG_EXT_SENS_DATA_17					0x5A	// ...
#define REG_EXT_SENS_DATA_18					0x5B	// ...
#define REG_EXT_SENS_DATA_19					0x5C	// ...
#define REG_EXT_SENS_DATA_20					0x5D	// ...
#define REG_EXT_SENS_DATA_21					0x5E	// ...
#define REG_EXT_SENS_DATA_22					0x5F	// ...
#define REG_EXT_SENS_DATA_23					0x60	// ...


// 
// File exclusive - New data types
// 

// NONE

// 
// File exclusive - Macro-functions
// 

// NONE

// 
// Global variables
// 

// NONE

// 
// Static functions declarations
// 

// NONE

// 
// Class constructors
// 
#include "main.h"
Mpu9250::Mpu9250(void)
{
	// Reset data members
	this->_resetDataMembers();

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return;
}

Mpu9250::Mpu9250(Handler *hdlr_p)
{
	// Reset data members
	this->_resetDataMembers();

	// Update handler (and sets error accordingly)
	this->setHandler(hdlr_p);

	// Returns
	return;
}

Mpu9250::~Mpu9250(void)
{
	// Reset data members
	this->_resetDataMembers();
}

// 
// Class own methods - public
// 

bool Mpu9250::configAccel(void)											// TODO: Implement this function
{
	// Check if device is functional and ready
	if(!this->_deviceReady()) {
		// Returns error
		return false;
	}

	// ************ DO THE REST ************************

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::configFifo(void)											// TODO: Implement this function
{
	// Check if device is functional and ready
	if(!this->_deviceReady()) {
		// Returns error
		return false;
	}

	// ************ DO THE REST ************************

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::configGyro(void)											// TODO: Implement this function
{
	// Check if device is functional and ready
	if(!this->_deviceReady()) {
		// Returns error
		return false;
	}

	// ************ DO THE REST ************************

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::configInterrupts(void)									// TODO: Implement this function
{
	// Check if device is functional and ready
	if(!this->_deviceReady()) {
		// Returns error
		return false;
	}

	// ************ DO THE REST ************************

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

error_e Mpu9250::getLastError(void)
{
	// Returns last error
	return this->_lastError;
}

bool Mpu9250::init(void)
{
	// Local variables
	uint8_t auxBuf[2];
	bool result = false;

	// Read Who Am I
	// if (!this->_identifyChip()) {
	// 	this->_lastError = ERROR_WRONG_CHIP;
	// 	return false;
	// }
	this->_handler->setDevice(this->_spiSelectDevice, this->_spiDeselectDevice);
	result = this->_handler->sendData(
					(REG_WHO_AM_I | Spi::SPI_READ),
					auxBuf,
					1);
	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}
	if(auxBuf[0] != MPU9250_WHO_AM_I) {
		this->_lastError = ERROR_COMMUNICATION_DEVICE_ID_MATCH_FAILED;
		debugMessage(ERROR_COMMUNICATION_DEVICE_ID_MATCH_FAILED);
		return false;
	}

	// Reset device
	auxBuf[0] = 0;
	auxBuf[0] =
			(1 << BIT_PWR_MGMT_1_H_RESET)		|
			(0 << BIT_PWR_MGMT_1_SLEEP)			|
			(0 << BIT_PWR_MGMT_1_CYCLE)			|
			(0 << BIT_PWR_MGMT_1_GYRO_STANDBY)	|
			(0 << BIT_PWR_MGMT_1_PD_PTAT)		|
			(0 << BIT_PWR_MGMT_1_CLKSEL0);
	result = this->_handler->sendData(
					(REG_PWR_MGMT_1 | Spi::SPI_WRITE),
					auxBuf,
					1);
	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}

	// Wait until device is ready
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
	HAL_Delay(MPU9250_RESET_DELAY);
#elif defined(_FUNSAPE_PLATFORM_AVR)							// AVR implementation
	// TODO: AVR implementation
#endif

	// Wake-up chip
	auxBuf[0] = 0;
	auxBuf[0] =
			(0 << BIT_PWR_MGMT_1_H_RESET)		|
			(0 << BIT_PWR_MGMT_1_SLEEP)			|
			(0 << BIT_PWR_MGMT_1_CYCLE)			|
			(0 << BIT_PWR_MGMT_1_GYRO_STANDBY)	|
			(0 << BIT_PWR_MGMT_1_PD_PTAT)		|
			(0 << BIT_PWR_MGMT_1_CLKSEL0);
	result = this->_handler->sendData(
					(REG_PWR_MGMT_1 | Spi::SPI_WRITE),
					auxBuf,
					1);
	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}

	// Disables I2C bus
	if(this->_interfaceMode == INTERFACE_MODE_SPI) {
		auxBuf[0] = 0;
		auxBuf[0] =
				(0 << BIT_USR_CTRL_FIFO_EN)		|
				(0 << BIT_USR_CTRL_I2C_MST_EN)			|
				(1 << BIT_USR_CTRL_I2C_IF_DIS)			|
				(0 << BIT_USR_CTRL_FIFO_RST)	|
				(0 << BIT_USR_CTRL_I2C_MST_RST)		|
				(0 << BIT_USR_CTRL_SIG_COND_RST);
		result = this->_handler->sendData(
						(REG_USER_CTRL | Spi::SPI_WRITE),
						auxBuf,
						1);
		if(!result) {
			this->_lastError = ERROR_COMMUNICATION_FAILED;
			debugMessage(ERROR_COMMUNICATION_FAILED);
			return false;
		}
	}

	// MPU6500 shares 4kB of memory between the DMP and the FIFO. Since the
	// first 3kB are needed by the DMP, we'll use the last 1kB for the FIFO.
	// data[0] = BIT_FIFO_SIZE_1024 | 0x8;
	// if (i2c_write(st.hw->addr, st.reg->accel_cfg2, 1, data)) {
	// 	return -1;
	// }

	// Standard configuration
	// REG_SMPLRT_DIV => 0
	// REG_CONFIG => 0

	auxBuf[0] = 0;
	auxBuf[0] =
			(0 << BIT_GYRO_CONFIG_X_ST_EN)	|
			(0 << BIT_GYRO_CONFIG_Y_ST_EN)	|
			(0 << BIT_GYRO_CONFIG_Z_ST_EN)	|
			(0 << BIT_GYRO_CONFIG_FS_SEL)	|
			(2 << BIT_GYRO_CONFIG_FCHOICE_B);
	result = this->_handler->sendData(
					(REG_GYRO_CONFIG | Spi::SPI_WRITE),
					auxBuf,
					1);
	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}

	// REG_ACCEL_CONFIG => 0
	auxBuf[0] = 0;
	auxBuf[0] =
			(1 << BIT_ACCEL_CONFIG2_FCHOICE_B) |
			(0 << BIT_ACCEL_CONFIG2_DLPF_CFG);
	result = this->_handler->sendData(
					(REG_ACCEL_CONFIG2 | Spi::SPI_WRITE),
					auxBuf,
					1);
	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}

	// REG_ACCEL_LOW_POWER_ODR => 0

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::setDevice(void (* selDevFunc_p)(void), void (* deselDevFunc_p)(void))
{
	// Check for errors - Function pointers
	if((selDevFunc_p == nullptr) || (deselDevFunc_p == nullptr)) {
		this->_lastError = ERROR_FUNCTION_POINTER_NULL;
		debugMessage(ERROR_FUNCTION_POINTER_NULL);
		return false;
	}

	// Update data members
	this->_spiSelectDevice = selDevFunc_p;
	this->_spiDeselectDevice = deselDevFunc_p;
	this->_spiSelFuncReady = true;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::setHandler(Handler *hdlr_p)
{
	// Check for errors - Handler pointer
	if(!isPointerValid(hdlr_p)) {						// ERROR - Handler pointer is null
		this->_lastError = ERROR_HANDLER_POINTER_NULL;
		debugMessage(ERROR_HANDLER_POINTER_NULL);
		return false;
	}

	// Update data members
	this->_initialized = false;
	switch(hdlr_p->getHandlerType()) {
	case Handler::HANDLER_TYPE_SPI:
		this->_interfaceMode = INTERFACE_MODE_SPI;
		break;
	case Handler::HANDLER_TYPE_TWI:
		this->_interfaceMode = INTERFACE_MODE_TWI;
		break;
	default:
		// Returns error
		this->_lastError = ERROR_HANDLER_UNSUPPORTED;
		debugMessage(ERROR_HANDLER_UNSUPPORTED);
		return false;
	}
	this->_handler = hdlr_p;
	this->_initialized = true;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

// 
// Class own methods - private
// 

bool Mpu9250::_deviceReady(void)
{
	if(!this->_initialized) {							// Checks initialization
		// Returns error
		this->_lastError = ERROR_NOT_INITIALIZED;
		debugMessage(ERROR_NOT_INITIALIZED);
		return false;
	}
	if(this->_interfaceMode == INTERFACE_MODE_SPI) {	// Checks device selection functions
		if(!this->_spiSelFuncReady) {
			// Returns error
			this->_lastError = ERROR_COMMUNICATION_NO_DEVICE_SELECTED;
			debugMessage(ERROR_COMMUNICATION_NO_DEVICE_SELECTED);
			return false;
		}
	}

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

void Mpu9250::_resetDataMembers(void)
{
	// Reset data members
	this->_handler						= nullptr;
	this->_initialized					= false;
	this->_spiSelFuncReady				= false;
	this->_interfaceMode				= INTERFACE_MODE_TWI;
	this->_spiSelectDevice				= nullptr;
	this->_spiDeselectDevice			= nullptr;
	for(uint8_t i = 0; i < 3; i++) {
		this->_accelRawData[i] = 0;
		this->_gyroRawData[i] = 0;
	}
	this->_tempRawData = 0;
	this->_tempData = 0.0;

	// Returns
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return;
}

// Private method
bool Mpu9250::_updateData(void)
{
	this->_handler->setDevice(this->_spiSelectDevice, this->_spiDeselectDevice);
	//uint8_t txBuffer[15];
	uint8_t rxBuffer[15];
//	int32_t aux32;
	bool result = false;

	// Select register
	//txBuffer[0] = REG_ACCEL_OUT_XH | Spi::SPI_READ;

	// Read raw data
	result = this->_handler->sendData((REG_ACCEL_OUT_XH | Spi::SPI_READ), rxBuffer, 14);

	if(!result) {
		this->_lastError = ERROR_COMMUNICATION_FAILED;
		debugMessage(ERROR_COMMUNICATION_FAILED);
		return false;
	}
	// Update data members
	for(uint8_t i = 0; i < 3; i++) {
		this->_accelRawData[i] = (((uint16_t)rxBuffer[(2 * i) + 1]) << 8) | ((uint16_t)rxBuffer[(2 * i + 1) + 1]);
	}
	this->_tempData = (((uint16_t)rxBuffer[7]) << 8) | ((uint16_t)rxBuffer[8]);
	for(uint8_t i = 0; i < 3; i++) {
		this->_gyroRawData[i] = (((uint16_t)rxBuffer[(2 * i) + 9]) << 8) | ((uint16_t)rxBuffer[(2 * i + 1) + 9]);
	}

	// Update temperature value
	// aux32 = ((int32_t)(this->_tempRawData) * 1000) / 333870 + 16100;
	// this->_tempData = ((float)aux32) / 1000.0f;
	this->_tempData = (float)(((((int32_t)this->_tempRawData) * 1000) / 333870) + 16100) / 1000.0f;

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}


bool Mpu9250::getAccelRawData(int16_t *accelData_p, bool updateRawData_p)
{
	if(updateRawData_p) {
		this->_updateData();
	}

	for(uint8_t i = 0; i < 3; i++) {
		accelData_p[i] = this->_accelRawData[i];
	}

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}



bool Mpu9250::getGyroRawData(int16_t *gyroData_p, bool updateRawData_p)
{
	if(updateRawData_p) {
		this->_updateData();
	}

	for(uint8_t i = 0; i < 3; i++) {
		gyroData_p[i] = this->_gyroRawData[i];
	}

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Mpu9250::getTempRawData(int16_t *tempData_p, bool updateRawData_p)
{
	if(updateRawData_p) {
		this->_updateData();
	}

	*tempData_p = (this->_tempRawData);

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}




















// bool Mpu9250::_writeData(void)
// {
// 	// Write data at mpu device
// 	// if (this->_interfaceMode) {				// SPI mode
// 	// 	this->_handler->sendData(this->_register, this->_bufferData, this->)
// 	// } else {							// TWI mode

// 	// }


// 	// Returns successfully
// 	return true;
// }

// bool Mpu9250::_readData(void)
// {

// 	// Returns successfully
// 	return true;
// }

// bool Mpu9250::_runSelfTest(void)
// {
// 	int result;
// 	unsigned char accel_fsr, fifo_sensors, sensors_on;
// 	unsigned short gyro_fsr, sample_rate, lpf;
// 	unsigned char dmp_was_on;

// 	if (st.chip_cfg.dmp_on) {
// 		mpu_set_dmp_state(0);
// 		dmp_was_on = 1;
// 	} else {
// 		dmp_was_on = 0;
// 	}

// 	// Get initial settings
// 	mpu_get_gyro_fsr(&gyro_fsr);
// 	mpu_get_accel_fsr(&accel_fsr);
// 	mpu_get_lpf(&lpf);
// 	mpu_get_sample_rate(&sample_rate);
// 	sensors_on = st.chip_cfg.sensors;
// 	mpu_get_fifo_config(&fifo_sensors);

// 	// For older chips, the self-test will be different
// 	// For now, this function will return a "pass" result for all three sensors
// 	// for compatibility with current test applications

// 	get_st_biases(gyro, accel, 0);
// 	result = 0x7;

// 	// Set to invalid values to ensure no I2C writes are skipped
// 	st.chip_cfg.gyro_fsr = 0xFF;
// 	st.chip_cfg.accel_fsr = 0xFF;
// 	st.chip_cfg.lpf = 0xFF;
// 	st.chip_cfg.sample_rate = 0xFFFF;
// 	st.chip_cfg.sensors = 0xFF;
// 	st.chip_cfg.fifo_enable = 0xFF;
// 	st.chip_cfg.clk_src = INV_CLK_PLL;
// 	mpu_set_gyro_fsr(gyro_fsr);
// 	mpu_set_accel_fsr(accel_fsr);
// 	mpu_set_lpf(lpf);
// 	mpu_set_sample_rate(sample_rate);
// 	mpu_set_sensors(sensors_on);
// 	mpu_configure_fifo(fifo_sensors);

// 	if (dmp_was_on) {
// 		mpu_set_dmp_state(1);
// 	}

// 	return result;

// 	// Returns successfully
// 	this->_lastError = ERROR_NONE;
// 	return true;
// }



// 
// Class own methods - protected
// 

// NONE

// 
// General public functions definitions
// 

// NONE

// 
// Public functions definitions
// 

// NONE
