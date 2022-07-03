/* =============================================================================
 * Project:		GPSDE++ AVR Library
 * File name:	circularBuffer8.cpp
 * Module:		8-bits data-wide circular buffer for GPDSE++ Library project
 * Authors:		Leandro Schwarz
 *				Hazael dos Santos Batista
 * Build:		1002
 * Date:		June 06, 2018
 * ========================================================================== */

// =============================================================================
// Dependencies
// =============================================================================

#include "circularBuffer8.hpp"
#if __CIRCULAR_BUFFER_8_HPP != 1002
#	error [circularBuffer8.cpp] Error 102 - Build mismatch on header and source code files.
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

/* NONE */

// =============================================================================
// File exclusive - New data types
// =============================================================================

/* NONE */

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

/* NONE */

// =============================================================================
// Global variables
// =============================================================================

/* NONE */

// =============================================================================
// Class constructors
// =============================================================================

CircularBuffer8::CircularBuffer8(uint16_t bufferSize)
{
	// Locks circular buffer
	this->locked_ = true;
	this->rdProtected_ = true;
	this->wrProtected_ = true;

	// Reset data members
	this->initialized_ = false;
	this->rdIndex_ = 0;;
	this->wrIndex_ = 0;
	this->maxSize_ = 0;
	this->occupation_ = 0;
	this->data_ = NULL;;
	this->empty_ = true;
	this->full_ = false;

	// Check for errors - Buffer size
	if (bufferSize == 0) {
		this->lastError_ = ERROR_BUFFER_SIZE_ZERO;
		return;
	} else if (bufferSize < 2) {
		this->lastError_ = ERROR_BUFFER_SIZE_TOO_SMALL;
		return;
	}

	// Allocate memory
	this->data_ = (uint8_t *)calloc(bufferSize, sizeof(uint8_t));
	if (this->data_ == NULL) {
		this->lastError_ = ERROR_MEMORY_ALLOCATION;
		return;
	}

	// Update data members
	this->maxSize_ = bufferSize;
	this->initialized_ = true;

	// Unlocks circular buffer
	this->locked_ = false;
	this->rdProtected_ = false;
	this->wrProtected_ = false;
	this->lastError_ = ERROR_NONE;

	return;
}

CircularBuffer8::~CircularBuffer8()
{
	// Locks circular buffer
	this->locked_ = true;
	this->rdProtected_ = true;
	this->wrProtected_ = true;

	// Deallocate memory if needed
	if (this->data_ != NULL) {
		free(this->data_);
	}
	this->data_ = NULL;

	// Reset data members
	this->initialized_ = false;
	this->rdIndex_ = 0;;
	this->wrIndex_ = 0;
	this->maxSize_ = 0;
	this->occupation_ = 0;
	this->empty_ = true;
	this->full_ = false;

	this->lastError_ = ERROR_NONE;
	return;
}

// =============================================================================
// Class public methods
// =============================================================================

uint16_t CircularBuffer8::getOccupation(void)
{
	this->lastError_ = ERROR_NONE;
	return this->occupation_;
}

bool CircularBuffer8::isEmpty(void)
{
	this->lastError_ = ERROR_NONE;
	return this->empty_;
}

bool CircularBuffer8::isFull(void)
{
	this->lastError_ = ERROR_NONE;
	return this->full_;
}

void CircularBuffer8::blockWrite(bool block)
{
	this->lastError_ = ERROR_NONE;
	this->wrProtected_ = block;
}

void CircularBuffer8::blockRead(bool block)
{
	this->lastError_ = ERROR_NONE;
	this->rdProtected_ = block;
}

bool CircularBuffer8::flush(void)
{
	// Locks circular buffer
	this->locked_ = true;
	this->rdProtected_ = true;
	this->wrProtected_ = true;

	// Flushes data
	this->rdIndex_ = 0;;
	this->wrIndex_ = 0;
	this->occupation_ = 0;
	this->empty_ = true;
	this->full_ = false;

	// Unlocks circular buffer
	this->locked_ = false;
	this->rdProtected_ = false;
	this->wrProtected_ = false;

	this->lastError_ = ERROR_NONE;
	return true;
}

bool CircularBuffer8::push(uint8_t data)
{
	// Check for errors - Not initialized
	if (!this->isInitialized()) {
		return false;
	}
	// Check for errors - Write protected
	if (this->isWriteProtected()) {
		return false;
	}
	// Check for errors - Buffer full
	if (this->full_) {
		this->lastError_ = ERROR_BUFFER_FULL;
		return false;
	}
	// Check for errors - Buffer locked
	if (this->isLocked()) {
		this->lastError_ = ERROR_LOCKED;
		return false;
	}

	// Locks circular buffer
	this->locked_ = true;

	// Stores data
	this->data_[this->wrIndex_] = data;							// Push data into buffer
	this->wrIndex_ = ((this->wrIndex_ + 1) % this->maxSize_);	// Calculates next write index
	this->occupation_++;										// Updates occupation
	this->full_ = (this->occupation_ == this->maxSize_);		// Updates full status
	this->empty_ = false;										// Updates empty status

	// Unlocks circular buffer
	this->locked_ = false;
	this->lastError_ = ERROR_NONE;
	return true;
}

bool CircularBuffer8::pop(uint8_t * data)
{
	// Check for errors - Not initialized
	if (!this->isInitialized()) {
		return false;
	}
	// Check for errors - Read protected
	if (this->isReadProtected()) {
		return false;
	}
	// Check for errors - Buffer empty
	if (this->empty_) {
		this->lastError_ = ERROR_BUFFER_EMPTY;
		return false;
	}
	// Check for errors - Buffer locked
	if (this->isLocked()) {
		this->lastError_ = ERROR_LOCKED;
		return false;
	}

	// Locks circular buffer
	this->locked_ = true;

	// Retrieves data
	*data = this->data_[this->wrIndex_];						// Pop data from buffer
	this->rdIndex_ = ((this->rdIndex_ + 1) % this->maxSize_);	// Calculates next read index
	this->occupation_--;										// Updates occupation
	this->full_ = false;										// Updates full status
	this->empty_ = (this->occupation_ == 0);					// Updates empty status

	// Unlocks circular buffer
	this->locked_ = false;
	this->lastError_ = ERROR_NONE;
	return true;
}

// =============================================================================
// Class private methods
// =============================================================================

bool CircularBuffer8::isLocked(void)
{
	if (this->locked_) {
		this->lastError_ = ERROR_LOCKED;
	}

	return this->locked_;
}

bool CircularBuffer8::isInitialized(void)
{
	if (!this->initialized_) {
		this->lastError_ = ERROR_NOT_INITIALIZED;
	}

	return this->initialized_;
}

bool CircularBuffer8::isWriteProtected(void)
{
	if (this->wrProtected_) {
		this->lastError_ = ERROR_WRITE_PROTECTED;
	}

	return this->wrProtected_;
}

bool CircularBuffer8::isReadProtected(void)
{
	if (!this->rdProtected_) {
		this->lastError_ = ERROR_READ_PROTECTED;
	}

	return this->rdProtected_;
}

// =============================================================================
// Class protected methods
// =============================================================================

/* NONE */

// =============================================================================
// General public functions definitions
// =============================================================================

/* NONE */

// =============================================================================
// Public functions definitions
// =============================================================================

/* NONE */
