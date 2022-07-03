/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibMpu9250.hpp
 * Module:			MPU-9250 interface module for FunSAPE++ Embedded Library
 * 					project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_MPU9250_HPP
#define __FUNSAPE_LIB_MPU9250_HPP				__BUILD_TO_REPLACE__

// =============================================================================
// System file dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "..\funsapeLibGlobalDefines.hpp"
#if __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibCircularBuffer16.hpp] Error 101 - Global definitions file (funsapeLibGlobalDefines.hpp) must be build __BUILD_TO_REPLACE__.
#endif

// -----------------------------------------------------------------------------
// Other header files ----------------------------------------------------------

#include "../util/funsapeLibHandler.hpp"
#if __FUNSAPE_LIB_HANDLER_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibMpu9250.hpp] Error 103 - Required module (funsapeLibHandler.hpp) must be build __BUILD_TO_REPLACE__.
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
#define isPointerValid(ptr)				((ptr) ? (bool)true : (bool)false)

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// -----------------------------------------------------------------------------
// Single variables ------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (logic values) -------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (small and finite lists) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (large or expansible lists) ------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (algebraic operated list elements) -----------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Mpu9250 - Class declaration
// =============================================================================

class Mpu9250
{
	// -------------------------------------------------------------------------
	// New data types ----------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Operators overloading ---------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Constructors ------------------------------------------------------------

public:
	Mpu9250(void);
	Mpu9250(Handler *hdlr);
	~Mpu9250(void);

	// -------------------------------------------------------------------------
	// Methods -----------------------------------------------------------------

public:
	bool setHandler(Handler *hdlr);
	bool setDevice(void (* actFunc)(void), void (* deactFunc)(void));
	error_e getLastError(void);
	bool init(void);
	bool configAccel();					// TODO
	bool configGyro();					// TODO
	bool configFifo();					// TODO
	bool configInterrupts();			// TODO
	// TODO: Add magnetometer implementation

private:
	bool _runSelfTest(void);
	bool _writeData(void);
	bool _readData(void);
	inlined void _resetDataMembers(void);

	// NONE

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Properties  -------------------------------------------------------------

public:
	// NONE

private:
	bool		_callbacksConfig		: 1;
	bool		_initialized			: 1;
	bool		_twiSpi					: 1;	// interface mode: TWI (0), SPI (1)
	error_e		_lastError;
	Handler		*_handler;
	uint8_t		_bufferData[14];
	uint8_t		_bufferLength;
	void	(* _activateDevice)(void);
	void	(* _deactivateDevice)(void);

protected:
	// NONE

};	// class Mpu9250

// =============================================================================
// Mpu9250 - Class inline function definitions
// =============================================================================

inlined void Mpu9250::_resetDataMembers(void)
{
	// Reset data members
	this->_activateDevice	= nullptr;
	this->_deactivateDevice	= nullptr;
	this->_callbacksConfig	= false;
	this->_initialized		= false;
	this->_twiSpi			= false;
	this->_handler			= nullptr;
	this->_register			= 0x00;
	this->_bufferLength		= 0;

	// Returns
	return;
}

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

#endif	// __FUNSAPE_LIB_MPU9250_HPP
