/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			circularBuffer.c
 * Module:			Circular Buffer Implementation for generic size variables
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 18, 2018
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "circularBuffer.h"
#if __CIRCULAR_BUFFER_H != 1
	#error Error 101 - Build mismatch on header and source code files (circularBuffer64).
#endif

/* -----------------------------------------------------------------------------
 * Initializes the circular buffer, allocating memory.
 * -------------------------------------------------------------------------- */

bool_t circularBufferInit(circularBuffer_t * buffer, uint16_t bufferSize, uint8_t variableSize)
{
	if(bufferSize == 0) {
		return FALSE;
	}

	// Memory allocation
	buffer->data = (uint8_t *)malloc(bufferSize * variableSize);
	if(buffer->data == NULL) {
		return FALSE;
	}

	buffer->size = bufferSize * variableSize;
	buffer->varSize = variableSize;
	buffer->nextRead = 0;
	buffer->nextWrite = 0;
	buffer->occupation = 0;

	return TRUE;
}

/* -----------------------------------------------------------------------------
 * Pushes data into circular buffer. The function returns FALSE if buffer is full.
 * -------------------------------------------------------------------------- */

bool_t circularBufferPushData(circularBuffer_t * buffer, void * data)
{
	uint8_t * castData = data;
	uint8_t tempSize = buffer->varSize;

	if(buffer->occupation == 0 || buffer->nextWrite != buffer->nextRead) {
		while(tempSize > 0) {
			buffer->data[buffer->nextWrite] = *castData;
			buffer->nextWrite++;
			castData++;
			tempSize--;
		}
		buffer->nextWrite %= buffer->size;
		buffer->occupation++;

		return TRUE;
	}

	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Pops data from the circular buffer. If the buffer is empty, the last
 * retrieved data will be stored into data and the function return FALSE. The
 * internal pointer will not be changed. The circularBufferIsEmpty() function
 * must be called to check if there is data to be read in the buffer. Returned
 * data must be immediately copied, since the pointed data can now be changed
 * by circularBufferPushData() calls.
 * -------------------------------------------------------------------------- */

bool_t	circularBufferPopData(circularBuffer_t * buffer, void * data)
{
	data = buffer->data + buffer->nextRead;

	if(buffer->occupation > 0) {
		buffer->nextRead = (buffer->nextRead + buffer->varSize) % buffer->size;
		buffer->occupation--;

		return TRUE;
	}

	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Verifies if there is data unread in the circular buffer. Must be called
 * before reading the buffer. Returns TRUE if there is unread data into buffer.
 * -------------------------------------------------------------------------- */

bool_t circularBufferIsEmpty(circularBuffer_t * buffer)
{
	if(buffer->occupation == 0) {
		return TRUE;
	}

	return FALSE;
}
