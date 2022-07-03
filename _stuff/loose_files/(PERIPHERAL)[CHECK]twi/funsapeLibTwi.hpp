/* 
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTwi.hpp
 * Module:			TWI Peripheral Interface for FunSAPE++ Embedded Library
 * 					project
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

#include "funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibTwi.hpp] Error 9 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 10 - Build mismatch between (funsapeLibTwi.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "../util/funsapeLibHandler.hpp"
#ifndef __FUNSAPE_LIB_HANDLER_HPP
#	error	[funsapeLibTwi.hpp] Error 1 - Header file (funsapeLibHandler.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_HANDLER_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 2 - Build mismatch between (funsapeLibTwi.hpp) and (funsapeLibHandler.hpp) header files!
#endif
#include "../util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#	error	[funsapeLibTwi.hpp] Error 1 - Header file (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_DEBUG_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTwi.hpp] Error 2 - Build mismatch between (funsapeLibTwi.hpp) and (funsapeLibDebug.hpp) header files!
#endif

// -----------------------------------------------------------------------------
// Header files - STM32 HAL header files ---------------------------------------

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
#	include "stm32f1xx_hal_i2c.h"
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

enum class TwiInstance {
	NONE								= 0,
	/*
	#if (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA48)   || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA48A)   || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA48P)   || \
	(_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA48PA) || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA48PB)  || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA88)    || \
	(_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA88A)  || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA88P)   || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA88PA)  || \
	(_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA88PB) || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA168)   || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA168A)  || \
	(_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA168P) || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA168PA) || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA168PB) || \
	(_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA328)  || (_FUNSAPE_MCU == _FUNSAPE_AVR_ATMEGA328P)
	TWI0								= 1,
	#endif
	*/
};

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
	// New data types
	// -------------------------------------------------------------------------

public:
	enum class TwiOperation {
		WRITE	= 0x00,
		READ	= 0x01
	};

private:
	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Operators overloading
	// -------------------------------------------------------------------------

public:
	// NONE

private:
	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Constructors
	// -------------------------------------------------------------------------

public:
	Twi(void);
	~Twi(void);

	// -------------------------------------------------------------------------
	// Methods - Inherited methods
	// -------------------------------------------------------------------------

public:

	bool read(
			uint8_t reg_p,						// TODO: Describe paramater
			uint8_t *dataBuffer_p,				// TODO: Describe paramater
			uint16_t bytesToRead_p				// TODO: Describe paramater
	);
	bool write(
			uint8_t reg_p,						// TODO: Describe paramater
			uint8_t *dataBuffer_p,				// TODO: Describe paramater
			uint16_t bytesToWrite_p				// TODO: Describe paramater
	);
	Handler::HandlerType getHandlerType(void);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Methods - Class own methods
	// -------------------------------------------------------------------------

public:
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)						// ARM implementation
	bool init(
			I2C_HandleTypeDef *twiHandler_p,	// TODO: Describe paramater
			uint16_t bufSize_p = 20				// TODO: Describe paramater
	);
#elif defined(_FUNSAPE_PLATFORM_AVR)							// AVR implementation
	bool init(
			TwiInstance twiInstance_p,			// TODO: Describe paramater
			uint16_t bufSize_p = 20				// TODO: Describe paramater
	);
#endif
	bool setTimeOut(
			uint16_t timeOut_p					// TODO: Describe paramater
	);
	bool setInterfaceMode(
			InterfaceMode interfaceMode_p		// TODO: Describe parameter
	);
	bool setCallBackFunction(
			void callBackFunc_p(void)			// TODO: Describe parameter
	);
	bool setTwiAddress(
			uint16_t twiAddress_p,				// TODO: Describe parameter
			bool useLongAddress = false			// TODO: Describe parameter
	);
	Error getLastError(void);

private:
	bool _reset(void);
	bool _initialize(void);
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	bool _checkStatus(HAL_StatusTypeDef halStatus_p);
#endif
	bool _readBlocking(void);
	bool _readInterrupt(void);
	bool _readDma(void);
	bool _writeBlocking(void);
	bool _writeInterrupt(void);
	bool _writeDma(void);
	bool _transmit(void);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Properties
	// -------------------------------------------------------------------------

public:
	// NONE

private:
	//     /////////////////    PERIPHERAL HANDLER     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
	I2C_HandleTypeDef	*_twiHandler;
#elif defined(_FUNSAPE_PLATFORM_AVR)
	TwiInstance			_twiInstance;
#endif

	//     //////////////    CONFIGURATION AND STATUS     ///////////////     //
	bool				_initialized			: 1;
	InterfaceMode		_interfaceMode;
	bool				_isBusy					: 1;
	Error				_lastError;
	uint16_t			_timeOut;
	bool				_readWrite				: 1;	// true = read, false = write
	uint16_t			_deviceAddress			: 11;
	bool				_useLongAddress			: 1;

	//     ////////////////////     DATA BUFFER      ////////////////////     //
	uint8_t				*_bufferData;
	uint16_t			_bufferIndex;
	uint16_t			_bufferLength;
	uint16_t			_bufferMaxSize;

	//     ////////////////////     DATA BUFFER      ////////////////////     //
	uint8_t				_auxRegister;
	uint8_t				_bytesToProcess;

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

// NONE
void showError(uint8_t errorCode);

#endif // __FUNSAPE_LIB_TWI_HPP
