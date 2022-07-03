/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibCircularBuffer.hpp
 * Module:			Generic data-wide circular buffer for FunSAPE++ Embedded
 * 					Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_CIRCULAR_BUFFER_HPP
#define __FUNSAPE_LIB_CIRCULAR_BUFFER_HPP		__BUILD_TO_REPLACE__

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "../funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibCircularBuffer.hpp] Error 9 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibCircularBuffer.hpp] Error 10 - Build mismatch between (funsapeLibCircularBuffer.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
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
// CircularBuffer - Class declaration
// =============================================================================

template<typename T>
class CircularBuffer
{
	// -------------------------------------------------------------------------
	// New data types
	// -------------------------------------------------------------------------

public:
	// NONE

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
	CircularBuffer(
			uint16_t	bufferSize			= 20,
			bool		overwrite			= false
	);
	~CircularBuffer(void);

// -------------------------------------------------------------------------
// Methods - Inherited methods
// -------------------------------------------------------------------------

public:
// NONE

protected:
// NONE

// -------------------------------------------------------------------------
// Methods - Class own methods
// -------------------------------------------------------------------------

public:
	//     //////////////////    DATA MANIPULATION     //////////////////     //
	//		Flushes all circular buffer data
	bool     flush(bool bypassProtection = false);
	//		Pushes data into circular buffer
	bool     push(T data);
	//		Pops data from circular buffer
	bool     pop(T *data, bool keepData = false);
	//		Pushes an entire buffer into circular buffer
	bool     pushBuffer(T *bufData, uint16_t bufSize);
	//		Pops an entire buffer into circular buffer
	bool     popBuffer(T *bufData, uint16_t bufSize, bool keepData = false);

	//     /////////////////     BUFFER INFORMATION     /////////////////     //
	//		Check if circular buffer is empty
	bool     isEmpty(void);
	//		Check if circular buffer is full
	bool     isFull(void);
	//		Gets the number of occupied elements of the circular buffer
	uint16_t getOccupation(void);
	//		Gets the number of free elements of the circular buffer
	uint16_t getFreeSpace(void);
	//		Returns error state from last operation
	Error  getLastError(void);

	//     ///////////////////     BUFFER CONTROL     ///////////////////     //
	//		Blocks write access to circular buffer
	void     blockWrite(bool block);
	//		Blocks read access to circular buffer
	void     blockRead(bool block);

private:
	//     ///////////////////     ??????????????     ///////////////////     //
	bool     _checkLocked(void);			// Check if buffer is locked
	bool     _checkInitialized(void);		// Check if buffer is initialized
	bool     _checkWriteProtected(void);	// Check if buffer is write protected
	bool     _checkReadProtected(void);		// Check if buffer is read protected
	void     _moveReadPointer(void);		// Moves read pointer one position
	void     _moveWritePointer(void);		// Moves write pointer one position
	void     _moveBothPointers(void);		// Moves read and write pointer one position

protected:
	// NONE

// -------------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------------

public:
// NONE

private:
	//     ///////////////////////     STATUS     ///////////////////////     //
	bool		_empty					: 1;
	bool		_full					: 1;
	bool		_initialized			: 1;
	bool		_locked					: 1;
	bool		_overwriting			: 1;
	bool		_rdProtected			: 1;
	bool		_wrProtected			: 1;

	//     ////////////////////    CONFIGURATION     ////////////////////     //
	uint16_t	_maxSize;

	//     /////////////////////    BUFFER DATA     /////////////////////     //
	T			*_data;
	uint16_t	_rdIndex;
	uint16_t	_wrIndex;
	uint16_t	_occupation;

	//     ///////////////////     ERROR MESSAGES     ///////////////////     //
	Error		_lastError;

protected:
// NONE

};  // class CircularBuffer

// =============================================================================
// CircularBuffer - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// =============================================================================
// CircularBuffer - Class inline function definitions
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

// =============================================================================
// External default objects
// =============================================================================

// NONE

// =============================================================================
// Include template implementation
// =============================================================================

#include "funsapeLibCircularBufferImp.hpp"
#ifndef __FUNSAPE_LIB_CIRCULAR_BUFFER_IMP_HPP
#	error	[funsapeLibCircularBuffer.hpp] Error 1 - Header file (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_CIRCULAR_BUFFER_IMP_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibCircularBuffer.hpp] Error 2 - Build mismatch between (funsapeLibCircularBuffer.hpp) and (funsapeLibDebug.hpp) header files!
#endif

#endif // __FUNSAPE_LIB_CIRCULAR_BUFFER_HPP
