/* 
 * Project:		FunSAPE++ Library
 * File name:	funsapeLibSystemStatus.hpp
 * Module:		System status Class for FunSAPE++ Library project
 * Author(s):	__AUTHORS_MACRO_TO_BE_CHANGED__
 * Build:		__BUILD_MACRO_TO_BE_CHANGED__
 * Date:		__DATE_MACRO_TO_BE_CHANGED__
 * ========================================================================== */

// 
// File build
// 

#ifndef __FUNSAPE_LIB_SYSTEM_STATUS_HPP
#define __FUNSAPE_LIB_SYSTEM_STATUS_HPP			__BUILD_MACRO_TO_BE_CHANGED__

// 
// System file dependencies
// 

#include "funsapeLibGlobalDefines.hpp"
#if __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_MACRO_TO_BE_CHANGED__
#	error	Global definitions file (funsapeLibGlobalDefines) must be build __BUILD_MACRO_TO_BE_CHANGED__.
#endif

// 
// Constants
// 

// -----------------------------------------------------------------------------
// Undefining previous definitions
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Defining new constants
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Defining macro-functions
// -----------------------------------------------------------------------------

// NONE

// 
// New data types
// 

// -----------------------------------------------------------------------------
// Single variables
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations - Logic values
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations - Finite lists
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations - Expansible lists
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations - Lists that can be algebraically manipulated
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations - Lists that can be manipulated using bitwise operations
// -----------------------------------------------------------------------------

// NONE

// 
// Global variable declaration
// 

// NONE

// 
// Class declaration
// 

// -----------------------------------------------------------------------------
// Class SystemStatus - Start
// -----------------------------------------------------------------------------

class SystemStatus
{
	// -------------------------------------------------------------------------
	// New data types
	// -------------------------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// New data declaration ----------------------------------------------------
private:

	// NONE

	// -------------------------------------------------------------------------
	// New data overloading operators ------------------------------------------
private:

	// NONE

	// -------------------------------------------------------------------------
	// Constructors
	// -------------------------------------------------------------------------
public:

	SystemStatus(void);									// Automatic constructor

	~SystemStatus(void);								// Automatic destructor

	// -------------------------------------------------------------------------
	// Public methods
	// -------------------------------------------------------------------------
public:

	//     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
	bool setClockPrescaler(								// Set system clock prescaler
		systemClockPrescaler_e prescaler					// Prescaler value
	);

	uint32_t getCpuClock(void);							// Returns CPU clock

	//     //////////////////////    STOPWATCH     //////////////////////     //
	uint32_t readStopwatch(void);
	void resumeStopwatch(void);
	void pauseStopwatch(void);
	void resetStopwatch(void);
	void setStopwatchMark(void);
	void incrementStopwatch(void);

	uint32_t getElapsedTime(							// Returns elapsed time between marks
		bool setNewMark = true								// Erase old time mark
	);

	//     ////////////////////     CHECK STATUS     ////////////////////     //
	error_e getLastError(void);							// Returns last error

	// -------------------------------------------------------------------------
	// Private methods
	// -------------------------------------------------------------------------
private:

	uint32_t _elapsedTime(uint32_t customMark);

	// -------------------------------------------------------------------------
	// Protected methods
	// -------------------------------------------------------------------------
protected:

	//     ///////////////////////     TO  DO     ///////////////////////     //

	// NONE

	// -------------------------------------------------------------------------
	// Private properties
	// -------------------------------------------------------------------------
private:

	//     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
	uint32_t					_sourceClockValue;
	systemClockPrescaler_e		_clockPrescaler;
	uint32_t					_cpuClockValue;

	//     //////////////////////    STOPWATCH     //////////////////////     //
	volatile uint32_t			_stopwatchValue;
	volatile uint32_t			_stopwatchMark;
	bool						_stopwatchHalted		: 1;

	//     ////////////////////     CHECK STATUS     ////////////////////     //
	error_e						_lastError;

	// -------------------------------------------------------------------------
	// Protected properties
	// -------------------------------------------------------------------------
protected:

	//     ///////////////////////     TO  DO     ///////////////////////     //

	// NONE

}; // class SystemStatus

// -----------------------------------------------------------------------------
// Class SystemStatus - Class overloading operators
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Class SystemStatus - Class inline functions definitions
// -----------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Class SystemStatus - End
// -----------------------------------------------------------------------------

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

extern SystemStatus systemStatus;

#endif // __FUNSAPE_LIB_SYSTEM_STATUS_HPP
