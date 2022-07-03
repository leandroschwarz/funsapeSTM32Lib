/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTwi.hpp
 * Module:			TWI Peripheral Interface for FunSAPE++ Embedded Library
 *					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_TWI_HPP
#define __FUNSAPE_LIB_TWI_HPP					__BUILD_TO_REPLACE__

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibTwi.hpp] Error 10 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 11 - Build mismatch between (funsapeLibTwi.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "util/funsapeLibHandler.hpp"
#ifndef __FUNSAPE_LIB_HANDLER_HPP
#	error	[funsapeLibTwi.hpp] Error 12 - Required module (funsapeLibHandler.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_HANDLER_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 103 - Required module (funsapeLibHandler.hpp) must be build __BUILD_TO_REPLACE__.
#endif
#include "util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#	error	[funsapeLibTwi.hpp] Error 12 - Required module (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_DEBUG_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 103 - Required module (funsapeLibDebug.hpp) must be build __BUILD_TO_REPLACE__.
#endif

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// Macro-function definitions
// *INDENT-OFF*
// =============================================================================

// NONE

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Twi - Class declaration
// =============================================================================

class Twi : public Handler
{
	// -------------------------------------------------------------------------
	// New data types ----------------------------------------------------------

public:
	typedef enum twiOperation_t {
		TWI_WRITE	= 0x00,
		TWI_READ	= 0x01
	} twiOperation_t;

private:
	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Operators overloading ---------------------------------------------------

public:
	// NONE

private:
	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Constructors ------------------------------------------------------------

public:
	Twi(void);
	~Twi(void);													// TODO: Implement function

	// -------------------------------------------------------------------------
	// Methods - Inherited public methods --------------------------------------

public:
	bool sendData(uint8_t *buffData, uint16_t buffSize = 1);
	bool sendData(uint8_t *txBuffData, uint8_t *rxBuffData, uint16_t buffSize = 1);
	bool sendData(uint8_t reg, uint8_t *buffData, uint16_t buffSize = 1);
	bool sendData(uint8_t reg, uint8_t *txBuffData, uint8_t *rxBuffData, uint16_t buffSize = 1);
	bool setDevice(void (* actFunc)(void), void (* deactFunc)(void));
	Handler::handlerType_e getHandlerType(void);

private:
	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Methods - Own methods ---------------------------------------------------

public:
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
	bool init(I2C_HandleTypeDef *handler, uint16_t bufSize = 20);
	bool init(I2C_HandleTypeDef *handler, uint16_t rxBufSize, uint16_t txBufSize);
#elif defined(_FUNSAPE_PLATFORM_AVR)							// AVR implementation
	// TODO: AVR implementation
	bool init(uint8_t *handler, uint16_t bufSize = 20);
	bool init(uint8_t *handler, uint16_t rxBufSize, uint16_t txBufSize);
#endif
	// NONE
	bool setTimeOut(uint16_t timeOut);
	error_e getLastError(void);

private:
	bool _deinitialize(void);
	bool _initialize(void);
	bool _transmit(void);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Properties  -------------------------------------------------------------

public:
	// NONE

private:
	//     /////////////////    PERIPHERAL HANDLER     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
	I2C_HandleTypeDef *_twiHandler;
#elif defined(_FUNSAPE_PLATFORM_AVR)							// AVR implementation
	uint8_t *_twiHandler;										// TODO: AVR implementation
#endif

	//     /////////////////    CONTROL AND STATUS     //////////////////     //
	bool	_initialized						: 1;
	bool	_busy								: 1;
	error_e	_lastError;

	//     ////////////////////    DATA BUFFERS      ////////////////////     //
	uint8_t		*_rxBufferData;
	uint16_t	_rxBufferMaxSize;
	uint16_t	_rxBufferIndex;
	uint16_t	_rxBufferLength;
	uint8_t		*_txBufferData;
	uint16_t	_txBufferMaxSize;
	uint16_t	_txBufferIndex;
	uint16_t	_txBufferLength;
	uint16_t	_timeOut;

protected:
	// NONE

}; // class Twi

// =============================================================================
// Twi - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Twi - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
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

#endif // __FUNSAPE_LIB_TWI_HPP
