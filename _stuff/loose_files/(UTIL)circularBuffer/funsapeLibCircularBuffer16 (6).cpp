/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibCircularBuffer16.cpp
 * Module:			16-bits data-wide circular buffer for FunSAPE++ Embedded
 * 					Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibCircularBuffer16.hpp"
#if __FUNSAPE_LIB_CIRCULAR_BUFFER_16_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibCircularBuffer16.cpp] Error 102 - Build mismatch on header and source code files.
#endif

#include "funsapeLibDebug.hpp"

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

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

CircularBuffer16::CircularBuffer16(uint16_t bufferSize, bool overwrite)
{
	// Locking procedure
	this->_locked = true;						// Locks circular buffer
	this->_rdProtected = true;					// Protects against read operations
	this->_wrProtected = true;					// Protects against write operations

	// Reset data members
	this->_initialized = false;
	this->_rdIndex = 0;;
	this->_wrIndex = 0;
	this->_maxSize = 0;
	this->_occupation = 0;
	this->_data = NULL;;
	this->_empty = true;
	this->_full = false;
	this->_overwriting = false;

	// Check for errors
	if(bufferSize == 0) {						// Zero-sized buffer
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		return;
	}
	if(bufferSize < 2) {						// Size too small
		debugMessage(ERROR_BUFFER_SIZE_TOO_SMALL);
		this->_lastError = ERROR_BUFFER_SIZE_TOO_SMALL;
		return;
	}

	// Allocate memory
	this->_data = (uint16_t *)calloc(bufferSize, sizeof(uint16_t));
	// Was memory allocation successful?
	if(this->_data == NULL) {					// No, trow error
		debugMessage(ERROR_MEMORY_ALLOCATION);
		this->_lastError = ERROR_MEMORY_ALLOCATION;
		return;
	}

	// Update data members
	this->_maxSize = bufferSize;
	this->_overwriting = overwrite;
	this->_initialized = true;

	// Unlock procedure
	this->_locked = false;						// Unlocks circular buffer
	this->_rdProtected = false;					// Allows read operations
	this->_wrProtected = false;					// Allows write operations

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return;
}

CircularBuffer16::~CircularBuffer16()
{
	// Locking procedure
	this->_locked = true;						// Locks circular buffer
	this->_rdProtected = true;					// Protects against read operations
	this->_wrProtected = true;					// Protects against write operations

	// Is there some memory allocated to buffer?
	if(this->_data != NULL) {					// Yes, deallocate it!
		free(this->_data);
	}
	this->_data = NULL;							// Clears pointer

	// Reset data members
	this->_initialized = false;
	this->_rdIndex = 0;
	this->_wrIndex = 0;
	this->_maxSize = 0;
	this->_occupation = 0;
	this->_empty = true;
	this->_full = false;
	this->_overwriting = false;

	// Return successfully (but do NOT unlock)
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return;
}

// =============================================================================
// Class public methods
// =============================================================================

error_e  CircularBuffer16::getLastError(void)
{
	return this->_lastError;
}

uint16_t CircularBuffer16::getOccupation(void)
{
	this->_lastError = ERROR_NONE;
	return this->_occupation;
}

uint16_t CircularBuffer16::getFreeSpace(void)
{
	this->_lastError = ERROR_NONE;
	return (this->_maxSize - this->_occupation);
}

bool CircularBuffer16::isEmpty(void)
{
	this->_lastError = ERROR_NONE;
	return this->_empty;
}

bool CircularBuffer16::isFull(void)
{
	this->_lastError = ERROR_NONE;
	return this->_full;
}

void CircularBuffer16::blockWrite(bool block)
{
	this->_lastError = ERROR_NONE;
	this->_wrProtected = block;
}

void CircularBuffer16::blockRead(bool block)
{
	this->_lastError = ERROR_NONE;
	this->_rdProtected = block;
}

bool CircularBuffer16::flush(bool bypassProtection)
{
	// Check for errors
	if(!this->_checkInitialized()) {			// Circular buffer is not initialized
		return false;
	}
	if(this->_checkLocked()) {					// Circular buffer is locked
		return false;
	}
	// Must bypass read and write protection?
	if(!bypassProtection) {					// No, lets see if any protection is on!
		if(this->_checkReadProtected()) {		// Circular buffer is read protected
			return false;
		}
		if(this->_checkWriteProtected()) {		// Circular buffer is write protected
			return false;
		}
	}

	// Locking procedure
	this->_locked = true;						// Locks circular buffer
	this->_rdProtected = true;					// Protects against read operations
	this->_wrProtected = true;					// Protects against write operations

	// Flushes data
	this->_rdIndex = 0;;
	this->_wrIndex = 0;
	this->_occupation = 0;
	this->_empty = true;
	this->_full = false;

	// Unlock procedure (also resets protection)
	this->_locked = false;						// Unlocks circular buffer
	this->_rdProtected = false;					// Allows read operations
	this->_wrProtected = false;					// Allows write operations

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return true;
}

bool CircularBuffer16::push(uint16_t data)
{
	// Check for errors
	if(!this->_checkInitialized()) {			// Circular buffer is not initialized
		return false;
	}
	if(this->_checkLocked()) {					// Circular buffer is locked
		return false;
	}
	if(this->_checkWriteProtected()) {			// Circular buffer is write protected
		return false;
	}

	// Locking procedure
	this->_locked = true;						// Locks circular buffer

	// Is buffer full?
	if(!this->_full) {							// No, normal operation!
		this->_data[this->_wrIndex] = data;				// Stores data
		this->_moveWritePointer();						// Moves WRITE pointer only
	} else {									// Yes, must check what to do!
		// Is overwriting allowed?
		if(this->_overwriting) {						// Yes, overwrites old data!
			this->_data[this->_wrIndex] = data;					// Stores data
			this->_moveBothPointers();							// Moves BOTH pointers
		} else {										// No, trow error!
			debugMessage(ERROR_BUFFER_FULL);
			this->_lastError = ERROR_BUFFER_FULL;
			// Unlocking procedure before exit
			this->_locked = false;
			return false;
		}
	}

	// Unlocking procedure
	this->_locked = false;						// Unlocks circular buffer

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return true;
}

bool CircularBuffer16::pop(uint16_t *data, bool keepData)
{
	// Check for errors
	if(data == NULL) {							// Argument is a NULL pointer
		debugMessage(ERROR_ARGUMENT_POINTER_NULL);
		this->_lastError = ERROR_ARGUMENT_POINTER_NULL;
		return false;
	}
	if(!this->_checkInitialized()) {			// Circular buffer is not initialized
		return false;
	}
	if(this->_checkLocked()) {					// Circular buffer is locked
		return false;
	}
	if(this->_checkReadProtected()) {			// Circular buffer is read protected
		return false;
	}
	if(this->_empty) {							// Circular buffer is empty
		debugMessage(ERROR_BUFFER_EMPTY);
		this->_lastError = ERROR_BUFFER_EMPTY;
		return false;
	}

	// Locking procedure
	this->_locked = true;						// Locks circular buffer

	// Gets data
	*data = this->_data[this->_rdIndex];		// Retrieves data
	// Must move pointer?
	if(!keepData) {							// Yes, pointer must be moved!
		this->_moveReadPointer();						// Moves pointer
	}

	// Unlocking procedure
	this->_locked = false;						// Unlocks circular buffer

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return true;
}

bool CircularBuffer16::pushBuffer(uint16_t *bufData, uint16_t bufSize)
{
	// Check for errors
	if(bufData == NULL) {				// Argument is a NULL pointer
		debugMessage(ERROR_ARGUMENT_POINTER_NULL);
		this->_lastError = ERROR_ARGUMENT_POINTER_NULL;
		return false;
	}
	if(bufSize == 0) {					// Buffer is zero-sized
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		return false;
	}
	if(!this->_checkInitialized()) {	// Circular buffer is not initialized
		return false;
	}
	if(this->_checkLocked()) {			// Circular buffer is locked
		return false;
	}
	if(this->_checkWriteProtected()) {	// Circular buffer is write protected
		return false;
	}

	// Locking procedure
	this->_locked = true;						// Locks circular buffer

	uint16_t freeSpace = this->_maxSize - this->_occupation;
	// Is there enough space?
	if(freeSpace >= bufSize) {					// Yes, normal operation!
		for(uint16_t i = 0; i < bufSize; i++) {
			this->_data[this->_wrIndex] = bufData[i];	// Stores data
			this->_moveWritePointer();					// Moves WRITE pointer
		}
	} else {									// No, must check what to do!
		// Is overwriting allowed?
		if(this->_overwriting) {						// Yes, split operation!
			for(uint16_t i = 0; i < bufSize; i++) {
				this->_data[this->_wrIndex] = bufData[i];		// Stores data
				// Is buffer full?
				if(this->_full) {								// Yes, move BOTH pointers!
					this->_moveBothPointers();
				} else {										// No, move WRITE pointer only!
					this->_moveWritePointer();
				}
			}
		} else {										// No, trow error!
			debugMessage(ERROR_BUFFER_NOT_ENOUGH_SPACE);
			this->_lastError = ERROR_BUFFER_NOT_ENOUGH_SPACE;
			// Unlocking procedure before exit
			this->_locked = false;
			return false;
		}
	}

	// Unlocking procedure
	this->_locked = false;						// Unlocks circular buffer

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return true;
}

bool CircularBuffer16::popBuffer(uint16_t *bufData, uint16_t bufSize, bool keepData)
{
	// Check for errors
	if(bufData == NULL) {						// Argument is a NULL pointer
		debugMessage(ERROR_ARGUMENT_POINTER_NULL);
		this->_lastError = ERROR_ARGUMENT_POINTER_NULL;
		return false;
	}
	if(bufSize == 0) {							// Buffer is zero-sized
		debugMessage(ERROR_BUFFER_SIZE_ZERO);
		this->_lastError = ERROR_BUFFER_SIZE_ZERO;
		return false;
	}
	if(!this->_checkInitialized()) {			// Circular buffer is not initialized
		return false;
	}
	if(this->_checkLocked()) {					// Circular buffer is locked
		return false;
	}
	if(this->_checkReadProtected()) {			// Circular buffer is read protected
		return false;
	}
	if(this->_occupation < bufSize) {			// There is not enough elements to get from buffer
		debugMessage(ERROR_BUFFER_NOT_ENOUGH_ELEMENTS);
		this->_lastError = ERROR_BUFFER_NOT_ENOUGH_ELEMENTS;
		return false;
	}

	// Locking procedure
	this->_locked = true;						// Locks circular buffer

	// Keep record of current buffer status
	uint16_t rdIndexOld = this->_rdIndex;
	uint16_t occupationOld = this->_occupation;
	bool emptyOld = this->_empty;
	bool fullOld = this->_full;

	// Get elements from buffer
	for(uint16_t i = 0; i < bufSize; i++) {
		bufData[i] = this->_data[this->_rdIndex];	// Retrieves data
		this->_moveReadPointer();					// Moves READ pointer
	}

	// Must keep old data?
	if(keepData) {								// Yes, load old status!
		this->_rdIndex = rdIndexOld;
		this->_occupation = occupationOld;
		this->_empty = emptyOld;
		this->_full = fullOld;
	}

	// Unlocking procedure
	this->_locked = false;						// Unlocks circular buffer

	// Return successfully
	debugMessage(ERROR_NONE);
	this->_lastError = ERROR_NONE;
	return true;
}

// =============================================================================
// Class private methods
// =============================================================================

bool inline __attribute__((always_inline)) CircularBuffer16::_checkLocked(void)
{
	if(this->_locked) {
		debugMessage(ERROR_LOCKED);
		this->_lastError = ERROR_LOCKED;
	}

	return this->_locked;
}

bool inline __attribute__((always_inline)) CircularBuffer16::_checkInitialized(void)
{
	if(!this->_initialized) {
		debugMessage(ERROR_NOT_INITIALIZED);
		this->_lastError = ERROR_NOT_INITIALIZED;
	}

	return this->_initialized;
}

bool inline __attribute__((always_inline)) CircularBuffer16::_checkWriteProtected(void)
{
	if(this->_wrProtected) {
		debugMessage(ERROR_WRITE_PROTECTED);
		this->_lastError = ERROR_WRITE_PROTECTED;
	}

	return this->_wrProtected;
}

bool inline __attribute__((always_inline)) CircularBuffer16::_checkReadProtected(void)
{
	if(!this->_rdProtected) {
		debugMessage(ERROR_READ_PROTECTED);
		this->_lastError = ERROR_READ_PROTECTED;
	}

	return this->_rdProtected;
}

void inline __attribute__((always_inline)) CircularBuffer16::_moveReadPointer(void)
{
	this->_rdIndex++;							// Increments read pointer
	this->_rdIndex %= this->_maxSize;			// Resolves read pointer overflow
	this->_occupation--;						// Decreases occupation number
	this->_full = false;						// Not full anymore
	this->_empty = (this->_occupation == 0);	// Resolves empty status

	return;
}

void inline __attribute__((always_inline)) CircularBuffer16::_moveWritePointer(void)
{
	this->_wrIndex++;							// Increments write pointer
	this->_wrIndex %= this->_maxSize;			// Resolves write pointer overflow
	this->_occupation++;						// Increases occupation number
	this->_full = (this->_occupation == this->_maxSize);	// Resolves full status
	this->_empty = false;						// Not empty anymore

	return;
}

void inline __attribute__((always_inline)) CircularBuffer16::_moveBothPointers(void)
{
	this->_wrIndex++;							// Increments write pointer
	this->_wrIndex %= this->_maxSize;			// Resolves write pointer overflow
	this->_rdIndex++;							// Increments read pointer
	this->_rdIndex %= this->_maxSize;			// Resolves read pointer overflow
	this->_full = (this->_occupation == this->_maxSize);	// Resolves full status
	this->_empty = (this->_occupation == 0);	// Resolves empty status

	return;
}

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Public functions definitions
// =============================================================================

// NONE
