/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTwi.cpp
 * Module:			TWI Peripheral Interface for FunSAPE++ Embedded Library
 *					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTwi.hpp"
#ifndef __FUNSAPE_LIB_TWI_HPP
#	error	[funsapeLibSpi.cpp] Error 1 - Header file (funsapeLibTwi.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_TWI_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.cpp] Error 9 - Build mismatch between source (funsapeLibTwi.cpp) and header (funsapeLibTwi.hpp) files!
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define		TWI_DEFAULT_TIME_OUT				30
#define		TWI_MIN_BUFFER_SIZE					5
#define		TWI_MAX_BUFFER_SIZE					200

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

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

Twi::Twi(void)
{
	// Reset data members
	this->_twiHandler					= nullptr;
	this->_initialized					= false;
	this->_busy							= false;
	this->_rxBufferData					= nullptr;
	this->_rxBufferMaxSize				= 0;
	this->_rxBufferIndex				= 0;
	this->_rxBufferLength				= 0;
	this->_txBufferData					= nullptr;
	this->_txBufferMaxSize				= 0;
	this->_txBufferIndex				= 0;
	this->_txBufferLength				= 0;
	this->_timeOut						= TWI_DEFAULT_TIME_OUT;

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return;
}

Twi::~Twi(void)
{
	// Return successfully
	return;
}

// =============================================================================
// Class inherited methods - public
// =============================================================================

bool Twi::sendData(uint8_t *buffData_p, uint16_t buffSize_p)
{
	// Check for errors
	if (!this->_initialized) {							// ERROR - peripheral not initialized
		this->_lastError = ERROR_NOT_INITIALIZED;
		debugMessage(ERROR_NOT_INITIALIZED);
		return false;
	}
	if (buffData_p == nullptr) {						// ERROR - transmission buffer data is null pointer
		this->_lastError = ERROR_BUFFER_POINTER_NULL;
		debugMessage(ERROR_BUFFER_POINTER_NULL);
		return false;
	}
	if (buffSize_p == 0) {								// ERROR - no bytes to send/receive
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	}
	if ((buffSize_p > this->_rxBufferMaxSize) ||
		(buffSize_p > this->_txBufferMaxSize)) {		// ERROR - message is too large to handle
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	}
	if (this->_busy) {									// ERROR - peripheral is busy
		this->_lastError = ERROR_IS_BUSY;
		debugMessage(ERROR_IS_BUSY);
		return false;
	}

	// Transfer data between buffers
	memcpy(this->_txBufferData, buffData_p, buffSize_p);
	this->_txBufferLength = buffSize_p;
	this->_txBufferIndex = 0;

	// Send data
	if (!this->_transmit()) {
		return false;
	}

	// Transfer data between buffers
	memcpy(buffData_p, this->_rxBufferData, buffSize_p);
	this->_rxBufferLength = buffSize_p;
	this->_rxBufferIndex = 0;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::sendData(uint8_t *txBuffData_p, uint8_t *rxBuffData_p, uint16_t buffSize_p)
{
	// Check for errors
	if (!this->_initialized) {							// ERROR - peripheral not initialized
		this->_lastError = ERROR_NOT_INITIALIZED;
		debugMessage(ERROR_NOT_INITIALIZED);
		return false;
	}
	if ((txBuffData_p == nullptr) ||
		(rxBuffData_p == nullptr)) {					// ERROR - transmission buffer data is null pointer
		this->_lastError = ERROR_BUFFER_POINTER_NULL;
		debugMessage(ERROR_BUFFER_POINTER_NULL);
		return false;
	}
	if (buffSize_p == 0) {								// ERROR - no bytes to send/receive
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	}
	if ((buffSize_p > this->_rxBufferMaxSize) ||
		(buffSize_p > this->_txBufferMaxSize)) {		// ERROR - message is too large to handle
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	}
	if (this->_busy) {									// ERROR - peripheral is busy
		this->_lastError = ERROR_IS_BUSY;
		debugMessage(ERROR_IS_BUSY);
		return false;
	}

	// Transfer data between buffers
	memcpy(this->_txBufferData, txBuffData_p, buffSize_p);
	this->_txBufferLength = buffSize_p;
	this->_txBufferIndex = 0;

	// Send data
	if (!this->_transmit()) {
		return false;
	}

	// Transfer data between buffers
	memcpy(rxBuffData_p, this->_rxBufferData, buffSize_p);
	this->_rxBufferLength = buffSize_p;
	this->_rxBufferIndex = 0;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::sendData(uint8_t reg_p, uint8_t *buffData_p, uint16_t buffSize_p)
{
	// Check for errors
	if (!this->_initialized) {							// ERROR - peripheral not initialized
		this->_lastError = ERROR_NOT_INITIALIZED;
		debugMessage(ERROR_NOT_INITIALIZED);
		return false;
	}
	if (buffData_p == nullptr) {						// ERROR - transmission buffer data is null pointer
		this->_lastError = ERROR_BUFFER_POINTER_NULL;
		debugMessage(ERROR_BUFFER_POINTER_NULL);
		return false;
	}
	if (buffSize_p == 0) {								// ERROR - no bytes to send/receive
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	}
	if (((buffSize_p + 1) > this->_rxBufferMaxSize) ||
		((buffSize_p + 1) > this->_txBufferMaxSize)) {	// ERROR - message is too large to handle
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	}
	if (this->_busy) {									// ERROR - peripheral is busy
		this->_lastError = ERROR_IS_BUSY;
		debugMessage(ERROR_IS_BUSY);
		return false;
	}

	// Transfer data between buffers
	this->_txBufferData[0] = reg_p;
	memcpy(&this->_txBufferData[1], buffData_p, buffSize_p);
	this->_txBufferLength = buffSize_p + 1;
	this->_txBufferIndex = 0;

	// Send data
	if (!this->_transmit()) {
		return false;
	}

	// Transfer data between buffers
	memcpy(buffData_p, &this->_rxBufferData[1], buffSize_p);
	this->_rxBufferLength = buffSize_p;
	this->_rxBufferIndex = 0;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::sendData(uint8_t reg_p, uint8_t *txBuffData_p, uint8_t *rxBuffData_p, uint16_t buffSize_p)
{
	// Check for errors
	if (!this->_initialized) {							// ERROR - peripheral not initialized
		this->_lastError = ERROR_NOT_INITIALIZED;
		debugMessage(ERROR_NOT_INITIALIZED);
		return false;
	}
	if ((txBuffData_p == nullptr) ||
		(rxBuffData_p == nullptr)) {					// ERROR - transmission buffer data is null pointer
		this->_lastError = ERROR_BUFFER_POINTER_NULL;
		debugMessage(ERROR_BUFFER_POINTER_NULL);
		return false;
	}
	if (buffSize_p == 0) {								// ERROR - no bytes to send/receive
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	}
	if (((buffSize_p + 1) > this->_rxBufferMaxSize) ||
		((buffSize_p + 1) > this->_txBufferMaxSize)) {	// ERROR - message is too large to handle
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	}
	if (this->_busy) {									// ERROR - peripheral is busy
		this->_lastError = ERROR_IS_BUSY;
		debugMessage(ERROR_IS_BUSY);
		return false;
	}

	// Transfer data between buffers
	this->_txBufferData[0] = reg_p;
	memcpy(&this->_txBufferData[1], txBuffData_p, buffSize_p);
	this->_txBufferLength = buffSize_p + 1;
	this->_txBufferIndex = 0;

	// Send data
	if (!this->_transmit()) {
		return false;
	}

	// Transfer data between buffers
	memcpy(rxBuffData_p, &this->_rxBufferData[1], buffSize_p);
	this->_rxBufferLength = buffSize_p;
	this->_rxBufferIndex = 0;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::setDevice(void (* actFunc_p)(void), void (* deactFunc_p)(void))
{
	// Returns ERROR
	this->_lastError = ERROR_UNKNOWN;
	debugMessage(ERROR_UNKNOWN);
	return false;
}

Handler::handlerType_e Twi::getHandlerType(void)
{
	debugMessage(ERROR_NONE);
	return Handler::HANDLER_TYPE_TWI;
}

// =============================================================================
// Class own methods - public
// =============================================================================

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
bool Twi::init(I2C_HandleTypeDef *handler_p, uint16_t bufSize_p)
#elif defined(_FUNSAPE_PLATFORM_AVR)							// TODO: AVR implementation
bool Twi::init(uint8_t *handler_p, uint16_t bufSize_p)
#endif
{
	// Deinitialize peripheral
	if (this->_initialized) {
		this->_deinitialize();
	}

	// Check for errors
	if (handler_p == nullptr) {
		this->_lastError = ERROR_HANDLER_POINTER_NULL;
		debugMessage(ERROR_HANDLER_POINTER_NULL);
		return false;
	}
	if (bufSize_p == 0) {
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	} else if (bufSize_p < TWI_MIN_BUFFER_SIZE) {
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	} else if (bufSize_p > TWI_MAX_BUFFER_SIZE) {
		this->_lastError = ERROR_BUFFER_SIZE_TOO_LARGE;
		debugMessage(ERROR_BUFFER_SIZE_TOO_LARGE);
		return false;
	}

	// Update data members
	this->_twiHandler = handler_p;
	this->_rxBufferMaxSize = bufSize_p;
	this->_txBufferMaxSize = bufSize_p;

	// Initialize
	if (!this->_initialize()) {
		// Return error
		return false;
	}

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
bool Twi::init(I2C_HandleTypeDef *handler_p, uint16_t rxBufSize_p, uint16_t txBufSize_p)
#elif defined(_FUNSAPE_PLATFORM_AVR)							// TODO: AVR implementation
bool Twi::init(uint8_t *handler_p, uint16_t rxBufSize_p, uint16_t txBufSize_p)
#endif
{
	// Deinitialize peripheral
	if (this->_initialized) {
		this->_deinitialize();
	}

	// Check for errors
	if (handler_p == nullptr) {
		this->_lastError = ERROR_HANDLER_POINTER_NULL;
		debugMessage(ERROR_HANDLER_POINTER_NULL);
		return false;
	}
	if ((rxBufSize_p == 0) || (txBufSize_p == 0)) {
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		return false;
	} else if ((rxBufSize_p < TWI_MIN_BUFFER_SIZE) || (txBufSize_p < TWI_MIN_BUFFER_SIZE)) {
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		return false;
	} else if ((rxBufSize_p > TWI_MAX_BUFFER_SIZE) || (txBufSize_p > TWI_MAX_BUFFER_SIZE)) {
		this->_lastError = ERROR_BUFFER_SIZE_TOO_LARGE;
		debugMessage(ERROR_BUFFER_SIZE_TOO_LARGE);
		return false;
	}

	// Update data members
	this->_twiHandler = handler_p;
	this->_rxBufferMaxSize = rxBufSize_p;
	this->_txBufferMaxSize = txBufSize_p;

	// Initialize
	if (!this->_initialize()) {
		// Return error
		return false;
	}

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::setTimeOut(uint16_t timeOut_p)
{
	// Update data members
	this->_timeOut = timeOut_p;

	// Return successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

error_e Twi::getLastError(void)
{
	// Return error
	return this->_lastError;
}

// =============================================================================
// Class own methods - private
// =============================================================================

bool Twi::_deinitialize(void)
{
	// Reset data members
	this->_twiHandler					= nullptr;
	this->_initialized					= false;
	this->_busy							= false;
	if (this->_rxBufferData != nullptr) {
		free(this->_rxBufferData);
		this->_rxBufferData				= nullptr;
	}
	this->_rxBufferMaxSize				= 0;
	this->_rxBufferIndex				= 0;
	this->_rxBufferLength				= 0;
	if (this->_txBufferData != nullptr) {
		free(this->_txBufferData);
		this->_txBufferData				= nullptr;
	}
	this->_txBufferMaxSize				= 0;
	this->_txBufferIndex				= 0;
	this->_txBufferLength				= 0;
	this->_timeOut						= TWI_DEFAULT_TIME_OUT;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::_initialize(void)
{
	// Allocate memory
	this->_rxBufferData = (uint8_t *)calloc(this->_rxBufferMaxSize, sizeof(uint8_t));
	this->_txBufferData = (uint8_t *)calloc(this->_txBufferMaxSize, sizeof(uint8_t));
	if ((this->_rxBufferData == nullptr) || (this->_txBufferData == nullptr)) {
		this->_deinitialize();
		this->_lastError = ERROR_MEMORY_ALLOCATION;
		debugMessage(ERROR_MEMORY_ALLOCATION);
		return false;
	}
	this->_rxBufferIndex = 0;
	this->_rxBufferLength = 0;
	this->_txBufferIndex = 0;
	this->_txBufferLength = 0;

	// Check peripheral status
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	do {
		HAL_I2C_StateTypeDef twiState = HAL_I2C_STATE_RESET;
		twiState = HAL_I2C_GetState(this->_twiHandler);
		if (twiState != HAL_I2C_STATE_READY) {
			// Return error
			this->_initialized = false;
			this->_lastError = ERROR_PERIPHERAL_NOT_READY;
			debugMessage(ERROR_PERIPHERAL_NOT_READY);
			return false;
		}
	} while (0);
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// TODO: AVR implementation
#endif

	// Update data members
	this->_initialized = true;

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
}

bool Twi::_transmit(void)
{
	/*
	// Send data by pooling
	this->_busy = true;							// Mark peripheral as busy
	#if defined(_FUNSAPE_PLATFORM_ARM_STM32)		// Try to transmit (ARM_STM32)
	HAL_StatusTypeDef halStatus = HAL_I2C_Master_Transmit(
			this->_spiHandler,
			this->_txBufferData,
			this->_rxBufferData,
			this->_txBufferLength,
			this->_timeOut
		);
	#elif defined(_FUNSAPE_PLATFORM_AVR)			// Try to transmit (AVR)
	// TODO: AVR implementation
	#endif
	this->_deactivateDefaultDevice();			// Deselect slave device
	#if defined(_FUNSAPE_PLATFORM_ARM_STM32)		// Check transmission status (ARM_STM32)
	if (halStatus == HAL_TIMEOUT) {
		this->_lastError = ERROR_COMMUNICATION_TIME_OUT;
		debugMessage(ERROR_COMMUNICATION_TIME_OUT);
		// Mark peripheral as not busy before leave
		this->_busy = false;
		return false;
	}
	if (halStatus == HAL_ERROR) {
		uint32_t halSpiError = HAL_SPI_GetError(this->_spiHandler);
		switch (halSpiError) {
			case HAL_SPI_ERROR_FLAG:
				this->_lastError = ERROR_SPI_BUSY_FLAG;
				debugMessage(ERROR_SPI_BUSY_FLAG);
				break;
			case HAL_SPI_ERROR_CRC:
				this->_lastError = ERROR_SPI_CRC;
				debugMessage(ERROR_SPI_CRC);
				break;
			case HAL_SPI_ERROR_OVR:
				this->_lastError = ERROR_SPI_OVERRUN;
				debugMessage(ERROR_SPI_OVERRUN);
				break;
			case HAL_SPI_ERROR_MODF:
				this->_lastError = ERROR_SPI_MODE_FAULT;
				debugMessage(ERROR_SPI_MODE_FAULT);
				break;
			case HAL_SPI_ERROR_DMA:
				this->_lastError = ERROR_SPI_DMA;
				debugMessage(ERROR_SPI_DMA);
				break;
			default:
				// If you arrived here, something really strange happened
				this->_lastError = ERROR_UNKNOWN;
				debugMessage(ERROR_UNKNOWN);
				break;
		}
		// Mark peripheral as not busy before leave
		this->_busy = false;
		return false;
	}
	#elif defined(_FUNSAPE_PLATFORM_AVR)			// Check transmission status (AVR)
	// TODO: AVR implementation
	#endif
	this->_busy = false;						// Mark peripheral as not busy

	// Returns successfully
	this->_lastError = ERROR_NONE;
	debugMessage(ERROR_NONE);
	return true;
	*/
}

// =============================================================================
// Class own methods - protected
// =============================================================================

// NONE
