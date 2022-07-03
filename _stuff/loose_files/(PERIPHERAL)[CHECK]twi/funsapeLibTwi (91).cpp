/* 
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTwi.cpp
 * Module:			TWI Peripheral Interface for FunSAPE++ Embedded Library
 * 					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// 
// Dependencies
// 

#include "funsapeLibTwi.hpp"
#ifndef __FUNSAPE_LIB_TWI_HPP
#	error	[funsapeLibTwi.cpp] Error 1 - Header file (funsapeLibTwi.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_TWI_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.cpp] Error 13 - Build mismatch between source (funsapeLibTwi.cpp) and header (funsapeLibTwi.hpp) files!
#endif

// 
// File exclusive - Constants
// 

#define		TWI_DEFAULT_TIME_OUT				30
#define		TWI_MIN_BUFFER_SIZE					5
#define		TWI_MAX_BUFFER_SIZE					200

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

Twi::Twi(void)
{
	// Reset data members
	this->_reset();

	// Return successfully
	this->_lastError = Error::NONE;
	return;
}

Twi::~Twi(void)
{
	// Reset data members
	this->_reset();

	// Return successfully
	return;
}

// 
// Inherited methods - Public
// 

bool Twi::read(uint8_t reg_p, uint8_t *dataBuffer_p, uint16_t bytesToRead_p)
{
	debugMark();

	// Checks for errors
	if(!this->_initialized) {
		this->_lastError = Error::NOT_INITIALIZED;
		debugMessage(Error::NOT_INITIALIZED);
		return false;
	}
	if(!isPointerValid(dataBuffer_p)) {
		this->_lastError = Error::BUFFER_POINTER_NULL;
		debugMessage(Error::BUFFER_POINTER_NULL);
		return false;
	}
	if(bytesToRead_p == 0) {
		this->_lastError = Error::BUFFER_SIZE_ZERO;
		debugMessage(Error::BUFFER_SIZE_ZERO);
		return false;
	}
	if((bytesToRead_p + 1) > this->_bufferMaxSize) {
		this->_lastError = Error::BUFFER_NOT_ENOUGH_SPACE;
		debugMessage(Error::BUFFER_NOT_ENOUGH_SPACE);
		return false;
	}
	if(this->_isBusy) {
		this->_lastError = Error::IS_BUSY;
		debugMessage(Error::IS_BUSY);
		return false;
	}

	// Processing request
	this->_readWrite = true;
	this->_isBusy = true;
	this->_bytesToProcess = bytesToRead_p;
	this->_auxRegister = reg_p;

	// Communicate through bus
	switch(this->_interfaceMode) {

	case InterfaceMode::BLOCKING_MODE:	// Using blocking mode
		if(this->_readBlocking()) {
			// Transfer data between buffers
			memcpy(dataBuffer_p, this->_bufferData, bytesToRead_p);
			this->_bufferLength = bytesToRead_p;
			this->_bufferIndex = 0;
			// Returns successfully
			this->_lastError = Error::NONE;
			debugMessage(Error::NONE);
			return true;
		}
		return false;

	case InterfaceMode::INTERRUPT_MODE:	// Using interrupt mode
		return this->_readInterrupt();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	case InterfaceMode::DMA_MODE:		// Using DMA mode
		return this->_readDma();
#endif

	}

	// Returns error - Ops. How did you arrived here?
	this->_lastError = Error::UNKNOWN;
	debugMessage(Error::UNKNOWN);
	return false;
}

bool Twi::write(uint8_t reg_p, uint8_t *dataBuffer_p, uint16_t bytesToWrite_p)
{
	debugMark();

	// Checks for errors
	if(!this->_initialized) {
		this->_lastError = Error::NOT_INITIALIZED;
		debugMessage(Error::NOT_INITIALIZED);
		return false;
	}
	if(!isPointerValid(dataBuffer_p)) {
		this->_lastError = Error::BUFFER_POINTER_NULL;
		debugMessage(Error::BUFFER_POINTER_NULL);
		return false;
	}
	if(bytesToWrite_p == 0) {
		this->_lastError = Error::BUFFER_SIZE_ZERO;
		debugMessage(Error::BUFFER_SIZE_ZERO);
		return false;
	}
	if((bytesToWrite_p + 1) > this->_bufferMaxSize) {
		this->_lastError = Error::BUFFER_NOT_ENOUGH_SPACE;
		debugMessage(Error::BUFFER_NOT_ENOUGH_SPACE);
		return false;
	}
	if(this->_isBusy) {
		this->_lastError = Error::IS_BUSY;
		debugMessage(Error::IS_BUSY);
		return false;
	}

	// Transfer data between buffers
	if(bytesToWrite_p > 0) {
		memcpy(this->_bufferData, dataBuffer_p, bytesToWrite_p);
	}
	this->_bufferLength = bytesToWrite_p;
	this->_bufferIndex = 0;

	// Processing request
	this->_readWrite = false;
	this->_isBusy = true;
	this->_bytesToProcess = bytesToWrite_p;
	this->_auxRegister = reg_p;

	// Communicate through bus
	switch(this->_interfaceMode) {

	case InterfaceMode::BLOCKING_MODE:	// Using blocking mode
		if(this->_writeBlocking()) {
			// Returns successfully
			this->_lastError = Error::NONE;
			debugMessage(Error::NONE);
			return true;
		}
		return false;

	case InterfaceMode::INTERRUPT_MODE:	// Using interrupt mode
		return this->_writeInterrupt();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	case InterfaceMode::DMA_MODE:		// Using DMA mode
		return this->_writeDma();
#endif

	}

	// Returns error - Ops. How did you arrived here?
	this->_lastError = Error::UNKNOWN;
	debugMessage(Error::UNKNOWN);
	return false;
}

bool Twi::setTwiAddress(uint16_t deviceAddress_p, bool useLongAddress_p)
{
	debugMark();

	// Check for errors
	if(!useLongAddress_p && (deviceAddress_p > 0x7F)) {
		// Returns error
		this->_lastError = Error::TWI_INVALID_DEVICE_ADDRESS;
		debugMessage(Error::TWI_INVALID_DEVICE_ADDRESS);
		return false;
	}

	// Update data members
	this->_deviceAddress = deviceAddress_p;
	this->_useLongAddress = useLongAddress_p;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

Handler::HandlerType Twi::getHandlerType(void)
{
	// Returns handler type
	return Handler::HandlerType::TWI;
}

// 
// Inherited methods - Protected
// 

// NONE

// 
// Class own methods - Public
// 

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
bool Twi::init(I2C_HandleTypeDef *twiHandler_p, uint16_t bufSize_p)
#elif defined(_FUNSAPE_PLATFORM_AVR)
bool Twi::init(TwiInstance twiInstance_p, uint16_t bufSize_p)
#endif
{
	debugMark();

	// Deinitialize peripheral
	if(this->_initialized) {
		this->_reset();
	}

	// Check for errors
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	if(!isPointerValid(twiHandler_p)) {
		// Return error
		this->_lastError = Error::HANDLER_POINTER_NULL;
		debugMessage(Error::HANDLER_POINTER_NULL);
		return false;
	}
#elif defined(_FUNSAPE_PLATFORM_AVR)
	if(twiInstance_p == TwiInstance::NONE) {
		// Return error
		this->_lastError = Error::INSTANCE_INVALID;
		debugMessage(Error::INSTANCE_INVALID);
		return false;
	}
#endif
	if(bufSize_p == 0) {
		// Return error
		this->_lastError = Error::BUFFER_SIZE_ZERO;
		debugMessage(Error::BUFFER_SIZE_ZERO);
		return false;
	} else if(bufSize_p < TWI_MIN_BUFFER_SIZE) {
		// Return error
		this->_lastError = Error::BUFFER_SIZE_TOO_SMALL;
		debugMessage(Error::BUFFER_SIZE_TOO_SMALL);
		return false;
	} else if(bufSize_p > TWI_MAX_BUFFER_SIZE) {
		// Return error
		this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
		debugMessage(Error::BUFFER_SIZE_TOO_LARGE);
		return false;
	}

	// Update data members
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	this->_twiHandler = twiHandler_p;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	this->_twiInstance = twiInstance_p;
#endif
	this->_bufferMaxSize = bufSize_p;

	// Initialize
	if(!this->_initialize()) {
		// Return error
		return false;
	}

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::setTimeOut(uint16_t timeOut_p)
{
	debugMark();

	// Update data members
	this->_timeOut = timeOut_p;

	// Return successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::setInterfaceMode(InterfaceMode interfaceMode_p)
{
	debugMark();

	// Check for error
	switch(interfaceMode_p) {
	case InterfaceMode::BLOCKING_MODE:			// Blocking mode is universally available
		break;

	case InterfaceMode::INTERRUPT_MODE:			// Interrupt mode is unviversally available
		break;

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	case InterfaceMode::DMA_MODE:				// DMA mode is NOT available for AVR platform
		break;
#endif

	default:									// Ops! Something really strange occurred. This option is invalid
		this->_lastError = Error::UNKNOWN;
		debugMessage(Error::UNKNOWN);
		return false;
	}

	// Update data members
	this->_interfaceMode = interfaceMode_p;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::setCallBackFunction(void callBackFunc_p(void))  	// TODO: Implement this function
{
	debugMark();

	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
}

Error Twi::getLastError(void)
{
	// Returns last error
	return this->_lastError;
}

// 
// Class own methods - Private
// 

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
bool Twi::_checkStatus(HAL_StatusTypeDef halStatus_p)
{
	debugMark();

	// Process operation status
	if(halStatus_p == HAL_OK) {					// No error
		return true;
	} else if(halStatus_p == HAL_TIMEOUT) {		// Timeout error
		this->_lastError = Error::COMMUNICATION_TIME_OUT;
	} else if(halStatus_p == HAL_BUSY) {		// Peripheral is busy
		this->_lastError = Error::IS_BUSY;
	} else if(halStatus_p == HAL_ERROR) {		// Other error (asking for more info)
		uint32_t halTwiError = HAL_I2C_GetError(this->_twiHandler);
		switch(halTwiError) {
		case HAL_I2C_ERROR_BERR:						// Bus error
			this->_lastError = Error::TWI_BUS_ERROR;
			break;
		case HAL_I2C_ERROR_ARLO:						// Arbitration lost
			this->_lastError = Error::TWI_ARBITRATION_LOST;
			break;
		case HAL_I2C_ERROR_AF:							// AF flag error
			this->_lastError = Error::TWI_AF_FLAG;
			break;
		case HAL_I2C_ERROR_OVR:							// Overrun error
			this->_lastError = Error::TWI_OVERRUN;
			break;
		case HAL_I2C_ERROR_DMA:							// DMA transfer error
			this->_lastError = Error::DMA_TRANSFER_ERROR;
			break;
		case HAL_I2C_ERROR_TIMEOUT:						// Timeout error
			this->_lastError = Error::COMMUNICATION_TIME_OUT;
			break;
		default:										// Ops...
			// If you arrived here, something really strange happened
			this->_lastError = Error::UNKNOWN;
			break;
		}
	} else {									// Ops...
		// If you arrived here, something really strange happened
		this->_lastError = Error::UNKNOWN;
	}

	// Returns error
	return false;
}
#endif

bool Twi::_reset(void)
{
	debugMark();

	// Reset data members
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	this->_twiHandler					= nullptr;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	this->_twiInstance					= TwiInstance::NONE;
#endif
	this->_initialized					= false;
	if(this->_bufferData != nullptr) {
		free(this->_bufferData);
		this->_bufferData				= nullptr;
	}
	this->_bufferMaxSize				= 0;
	this->_bufferIndex					= 0;
	this->_bufferLength					= 0;
	this->_timeOut						= TWI_DEFAULT_TIME_OUT;
	this->_isBusy						= false;
	this->_readWrite					= false;
	this->_interfaceMode				= InterfaceMode::BLOCKING_MODE;
	this->_deviceAddress				= 0x0000;
	this->_useLongAddress				= false;
	this->_auxRegister					= 0x00;
	this->_bytesToProcess				= 0x00;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_initialize(void)
{
	debugMark();

	// Allocate memory
	this->_bufferData = (uint8_t *)calloc(this->_bufferMaxSize, sizeof(uint8_t));
	if(this->_bufferData == nullptr) {
		this->_reset();
		this->_lastError = Error::MEMORY_ALLOCATION;
		debugMessage(Error::MEMORY_ALLOCATION);
		return false;
	}
	this->_bufferIndex = 0;
	this->_bufferLength = 0;

	// Check peripheral status
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	do {
		HAL_I2C_StateTypeDef twiState = HAL_I2C_STATE_RESET;
		twiState = HAL_I2C_GetState(this->_twiHandler);
		if(twiState != HAL_I2C_STATE_READY) {
			// Return error
			this->_initialized = false;
			this->_lastError = Error::PERIPHERAL_NOT_READY;
			debugMessage(Error::PERIPHERAL_NOT_READY);
			return false;
		}
	} while(0);
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: Implement this part
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#endif

	// Update data members
	this->_initialized = true;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_readBlocking(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// Local variables
	HAL_StatusTypeDef halStatus;

	// Retrieve device address size
	uint16_t auxMemAddSize = I2C_MEMADD_SIZE_8BIT;
	if(this->_useLongAddress) {
		auxMemAddSize = I2C_MEMADD_SIZE_16BIT;
	}

	// Start communication
	halStatus = HAL_I2C_Mem_Read(
					this->_twiHandler,
					(this->_deviceAddress << 1),
					this->_auxRegister,
					auxMemAddSize,
					this->_bufferData,
					this->_bytesToProcess,
					this->_timeOut
			);

	// Check function status
	if(!this->_checkStatus(halStatus)) {
		// Mark peripheral as not busy before leave
		this->_isBusy = false;
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_readInterrupt(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_readDma(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::DMA_NOT_SUPPORTED;
	debugMessage(Error::DMA_NOT_SUPPORTED);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_writeBlocking(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// Local variables
	HAL_StatusTypeDef halStatus;

	// Retrieve device address size
	uint16_t auxMemAddSize = I2C_MEMADD_SIZE_8BIT;
	if(this->_useLongAddress) {
		auxMemAddSize = I2C_MEMADD_SIZE_16BIT;
	}

	// Start communication
	halStatus = HAL_I2C_Mem_Write(
					this->_twiHandler,
					(this->_deviceAddress << 1),
					this->_auxRegister,
					auxMemAddSize,
					this->_bufferData,
					this->_bytesToProcess,
					this->_timeOut
			);
	if(!this->_checkStatus(halStatus)) {
		// Mark peripheral as not busy before leave
		this->_isBusy = false;
		// Returns error
		debugMessage(this->_lastError);
		return false;
	}
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_writeInterrupt(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

bool Twi::_writeDma(void)
{
	debugMark();

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	// TODO: Implement this part
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::UNDER_DEVELOPMENT;
	debugMessage(Error::UNDER_DEVELOPMENT);
	return false;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// Mark peripheral as not busy before leave
	this->_isBusy = false;
	// Returns error
	this->_lastError = Error::DMA_NOT_SUPPORTED;
	debugMessage(Error::DMA_NOT_SUPPORTED);
	return false;
#endif

	// Mark peripheral as not busy before leave
	this->_isBusy = false;

	// Returns successfully
	this->_lastError = Error::NONE;
	debugMessage(Error::NONE);
	return true;
}

// 
// Class own methods - Protected
// 

// NONE

// 
// General public functions definitions
// 

// NONE

// 
// File exclusive - Static functions definitions
// 

// NONE
