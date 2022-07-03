/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			matrixKeypad.c
 * Module:			Matrix keypad controller
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 18, 2018
 * Purpose:			Matrix keypad controller with support to 4x3, 4x4 and 5x3
 *					keypads and configurable debounce time
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "matrixKeypad.h"
#if __MATRIX_KEYPAD_H != 1
#error Error 101 - Build mismatch on header and source code files (matrixKeypad).
#endif

/* -----------------------------------------------------------------------------
 * Function:	matrixKeypadResetConfiguration
 * Purpose:		Resets the keypad configuration struct
 * Arguments:	keypad		Pointer to the keypad struct
 * Returns:		KEYPAD_OK
 * -------------------------------------------------------------------------- */

matrixKeypadResult_t keypadResetConfiguration(matrixKeypad_t *keypad)
{
    keypad->linesDDR = NULL;
    keypad->linesPORT = NULL;
    keypad->linesPIN = NULL;
    keypad->columnsDDR = NULL;
    keypad->columnsPORT = NULL;
    free(keypad->keys);
    keypad->keys = NULL;
    keypad->linesLSB = 0;
    keypad->columnsLSB = 0;
    keypad->type = KEYPAD_TYPE_UNDEFINED;
    keypad->lines = 0;
    keypad->columns = 0;
    keypad->portsConfigured = FALSE;
    keypad->keysConfigured = FALSE;
    keypad->initialized = FALSE;
    keypad->debounceTime = 0;

    return KEYPAD_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	matrixKeypadSetPort
 * Purpose:		Configures the keypad I/O ports
 * Arguments:	keypad			Pointer to the keypad struct
 *				linesDDR		Pointer to I/O Data Direction Register
 *				linesPORT		Pointer to I/O Port Output Register
 *				linesPIN		Pointer to I/O Port Input Register
 *				linesLSB		Position of the first bit of the register
 *				columnsDDR		Pointer to I/O Data Direction Register
 *				columnsPORT		Pointer to I/O Port Output Register
 *				columnsLSB		Position of the first bit of the register
 * Returns:		KEYPAD_OK
 * -------------------------------------------------------------------------- */

matrixKeypadResult_t matrixKeypadSetPort(matrixKeypad_t *keypad, reg_t *linesDDR, reg_t *linesPORT, reg_t *linesPIN,
        uint8_t linesLSB, reg_t *columnsDDR, reg_t *columnsPORT, uint8_t columnsLSB)
{
    keypad->linesDDR = linesDDR;
    keypad->linesPORT = linesPORT;
    keypad->linesPIN = linesPIN;
    keypad->linesLSB = linesLSB;
    keypad->columnsDDR = columnsDDR;
    keypad->columnsPORT = columnsPORT;
    keypad->columnsLSB = columnsLSB;
    keypad->portsConfigured = TRUE;

    return KEYPAD_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	matrixKeypadSetKeys
 * Purpose:		Configures the key layout
 * Arguments:	keypad			Pointer to the keypad struct
 *				type			Size of the keypad (use enumerations at
 *								keypadType_t)
 *				...				List of values to be stored in the keypad struct
 * Returns:		KEYPAD_OK
 *				KEYPAD_TYPE_NOT_ALLOWED
 *				KEYPAD_MEMORY_ALLOCATION_ERROR
 * -------------------------------------------------------------------------- */

matrixKeypadResult_t matrixKeypadSetKeys(matrixKeypad_t *keypad, matrixKeypadType_t type, ...)
{
    uint8_t i;
    uint8_t j;
    va_list args;

    // Keypad type
    switch (type) {
    case KEYPAD_4X4:
        keypad->type = KEYPAD_4X4;
        keypad->lines = 4;
        keypad->columns = 4;
        break;
    case KEYPAD_4X3:
        keypad->type = KEYPAD_4X3;
        keypad->lines = 4;
        keypad->columns = 3;
        break;
    case KEYPAD_5X3:
        keypad->type = KEYPAD_5X3;
        keypad->lines = 5;
        keypad->columns = 3;
        break;
    default:
        return KEYPAD_TYPE_NOT_ALLOWED;
    }

    // Memory allocation
    keypad->keys = (uint8_t *)malloc(keypad->lines * keypad->columns);
    if (keypad->keys == NULL) {
        return KEYPAD_MEMORY_ALLOCATION_ERROR;
    }

    // Keypad keys
    va_start(args, type);
    for (i = 0; i < keypad->lines; i++) {
        for (j = 0; j < keypad->columns; j++) {
            keypad->keys[(keypad->lines * i) + j] = (uint8_t)va_arg(args, uint16_t);
        }
    }
    va_end(args);
    keypad->keysConfigured = TRUE;

    return KEYPAD_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	matrixKeypadInit
 * Purpose:		Performs the keypad initialization
 * Arguments:	keypad			Pointer to the keypad struct
 *				debounceTime	Debouce time in miliseconds
 * Returns:		KEYPAD_OK
 *				KEYPAD_PORTS_NOT_CONFIGURED
 *				KEYPAD_KEYS_NOT_CONFIGURED
 *				KEYPAD_TYPE_NOT_ALLOWED
 * -------------------------------------------------------------------------- */

matrixKeypadResult_t matrixKeypadInit(matrixKeypad_t *keypad, uint8_t debounceTime)
{
    if (keypad->portsConfigured == FALSE) {
        return KEYPAD_PORTS_NOT_CONFIGURED;
    }

    if (keypad->keysConfigured == FALSE) {
        return KEYPAD_KEYS_NOT_CONFIGURED;
    }

    if (keypad->type == KEYPAD_TYPE_UNDEFINED) {
        return KEYPAD_TYPE_NOT_ALLOWED;
    }

    switch (keypad->type) {
    case KEYPAD_4X4:
        clrMaskOffset(*(keypad->linesDDR), 0x0F, keypad->linesLSB);
        setMaskOffset(*(keypad->linesPORT), 0x0F, keypad->linesLSB);
        setMaskOffset(*(keypad->columnsDDR), 0x0F, keypad->columnsLSB);
        setMaskOffset(*(keypad->columnsPORT), 0x0F, keypad->columnsLSB);
        break;
    case KEYPAD_4X3:
        clrMaskOffset(*(keypad->linesDDR), 0x0F, keypad->linesLSB);
        setMaskOffset(*(keypad->linesPORT), 0x0F, keypad->linesLSB);
        setMaskOffset(*(keypad->columnsDDR), 0x07, keypad->columnsLSB);
        setMaskOffset(*(keypad->columnsPORT), 0x07, keypad->columnsLSB);
        break;
    case KEYPAD_5X3:
        clrMaskOffset(*(keypad->linesDDR), 0x1F, keypad->linesLSB);
        setMaskOffset(*(keypad->linesPORT), 0x1F, keypad->linesLSB);
        setMaskOffset(*(keypad->columnsDDR), 0x07, keypad->columnsLSB);
        setMaskOffset(*(keypad->columnsPORT), 0x07, keypad->columnsLSB);
        break;
    default:
        return KEYPAD_TYPE_NOT_ALLOWED;
    }
    keypad->debounceTime = debounceTime;
    keypad->initialized = TRUE;

    return KEYPAD_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	matrixKeypadRead
 * Purpose:		Reads the keypad and returns the key pressed
 * Arguments:	keypad			Pointer to the keypad struct
 * Returns:		Value stored in the keypad stuct, initialized with keypadSetKeys
 * -------------------------------------------------------------------------- */

uint8_t matrixKeypadRead(matrixKeypad_t *keypad)
{
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t aux;
    uint8_t key = 0xFF;

    for (i = 0; i < keypad->columns; i++) {								// For each column
        clrBit(*(keypad->columnsPORT), (i + keypad->columnsLSB));	// Clear one columns
        asm("NOP;NOP;NOP;NOP;NOP;");								// Wait for synchronization
        aux = *(keypad->linesPIN) >> keypad->linesLSB;
        for (j = 0; j < keypad->lines; j++) {							// For each line
            if (isBitClr(aux, j)) {									// Tests if the key is pressed
                key = keypad->keys[(keypad->lines * j) + i];		// Decodes the key using the table
                for (k = 0; k < keypad->debounceTime; k++) {
                    _delay_ms(1);									// Debounce time
                }
            }
            // Wait until key is released
            waitUntilBitIsSet(*(keypad->linesPIN) >> keypad->linesLSB, j);
        }
        setBit(*(keypad->columnsPORT), (i + keypad->columnsLSB));	// Restore column value
    }

    return key;
}
