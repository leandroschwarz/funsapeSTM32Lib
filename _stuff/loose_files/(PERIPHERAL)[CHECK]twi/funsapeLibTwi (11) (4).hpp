/* 
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTwi.hpp
 * Module:			TWI Peripheral Module for FunSAPE++ Embedded Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// 
// Include guard
// 

#ifndef __FUNSAPE_LIB_TWI_HPP
#define __FUNSAPE_LIB_TWI_HPP					__BUILD_TO_REPLACE__

// 
// Dependencies
// 

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "../funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibTwi.hpp] Error 9 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 10 - Build mismatch between (funsapeLibTwi.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "util/funsapeLibHandler.hpp"
#ifndef __FUNSAPE_LIB_HANDLER_HPP
#	error	[funsapeLibTwi.hpp] Error 12 - Required module (funsapeLibHandler.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_HANDLER_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibTwi.hpp] Error 103 - Required module (funsapeLibHandler.hpp) must be build __BUILD_TO_REPLACE__.
#endif
#include "util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#	error	[funsapeLibTwi.hpp] Error 12 - Required module (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_DEBUG_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibTwi.hpp] Error 103 - Required module (funsapeLibDebug.hpp) must be build __BUILD_TO_REPLACE__.
#endif

// 
// Undefining previous definitions
// 

// NONE

// 
// Constant definitions
// 

// NONE

// 
// Macro-function definitions
// *INDENT-OFF*
// 

// NONE

// *INDENT-ON*

// 
// New data types
// 

// NONE

// 
// Extern global variables
// 

// NONE

// 
// Twi - Class declaration
// 

class Twi : public Handler
{
	// -------------------------------------------------------------------------
	// New data types ----------------------------------------------------------

public:
	// NONE

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
	Twi(
			void
	);
	~Twi(
			void
	);

	// -------------------------------------------------------------------------
	// Methods - Inherited methods ---------------------------------------------

public:
	//     ////////////////////    DATA TRANSFER     ////////////////////     //
	bool readReg(
			uint8_t reg_p,
			uint8_t *buffData_p,
			uint16_t buffSize_p = 1
	);
	bool writeReg(
			uint8_t reg_p,
			uint8_t *buffData_p,
			uint16_t buffSize_p = 1
	);

	//     //////////////////    PROTOCOL SPECIFIC     //////////////////     //
	Handler::HandlerType getHandlerType(
			void
	);
	bool setAddress(
			uint16_t address_p,
			bool useLongAddress_p = false
	);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Methods - Class own methods ---------------------------------------------

public:
	bool init(
#if defined(_FUNSAPE_PLATFORM_ARM_STM32) && defined(HAL_I2C_MODULE_ENABLED)
			// ARM implementation
			I2C_HandleTypeDef *handler_p,
#elif defined(_FUNSAPE_PLATFORM_AVR)
			// AVR implementation
			uint8_t *handler_p,
#else // _FUNSAPE_PLATFORM_AVR
			uint8_t *handler_p,
#endif // NONE OF THE OTHERS
			uint16_t bufSize_p = 20
	);
	Error getLastError(
			void
	);
	bool setTimeout(
			uint16_t timeout_p
	);

private:
	bool _initialize(
			void
	);
	bool _deinitialize(
			void
	);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Properties --------------------------------------------------------------

public:
	// NONE

private:
	//     /////////////////    PERIPHERAL HANDLER     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_ARM_STM32) && defined(HAL_I2C_MODULE_ENABLED)
	// ARM implementation
	I2C_HandleTypeDef *_twiHandler;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	// AVR implementation
	uint8_t *_twiHandler;
#else // _FUNSAPE_PLATFORM_AVR
	uint8_t *_twiHandler;
#endif // NONE OF THE OTHERS

	//     /////////////////    CONTROL AND STATUS     //////////////////     //
	bool				_busy					: 1;
	uint16_t			_devAddress				: 10;
	bool				_devAddressLong			: 1;
	bool				_devAddressSet			: 1;
	bool				_initialized			: 1;
	Error				_lastError;
	uint8_t				_regAddress;
	uint16_t			_timeout;

	//     ////////////////////    DATA BUFFERS      ////////////////////     //
	uint8_t				*_bufferData;
	uint16_t			_bufferIndex;
	uint16_t			_bufferLength;
	uint16_t			_bufferMaxSize;

protected:
	// NONE

protected:
	// NONE

}; // class Twi

// 
// Twi - Class overloading operators
// 

// NONE

// 
// Global variables
// 

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// 
// Twi - Class inline function definitions
// 

// NONE

// 
// General public functions declarations
// 

// NONE

// 
// General inline functions definitions
// 

// NONE

// 
// External default objects
// 

#endif // __FUNSAPE_LIB_TWI_HPP
