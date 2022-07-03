/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibLcd.cpp
 * Module:			Character LCD Module Interface for FunSAPE++ Embedded
 * 					Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibLcd.hpp"
#if __FUNSAPE_LIB_LCD_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibLcd.cpp] Error 102 - Build mismatch on header and source code files!
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define LCD_CLEAR_SCREEN_CMD			0x01
#define LCD_CURSOR_HOME_CMD				0x02
#define LCD_ENTRY_MODE_CMD				0x04
#	define LCD_ENTRY_MODE_DECREMENT				(0 << 1)
#	define LCD_ENTRY_MODE_INCREMENT				(1 << 1)
#	define LCD_ENTRY_MODE_OVERWRITE				(0 << 0)
#	define LCD_ENTRY_MODE_SHIFT					(1 << 0)
#define LCD_DISPLAY_CMD					0x08
#	define LCD_DISPLAY_OFF						(0 << 2)
#	define LCD_DISPLAY_ON						(1 << 2)
#	define LCD_CURSOR_OFF						(0 << 1)
#	define LCD_CURSOR_ON						(1 << 1)
#	define LCD_CURSOR_BLINK_OFF					(0 << 0)
#	define LCD_CURSOR_BLINK_ON					(1 << 0)
#define LCD_MOVE_SCROLL_CMD				0x10
#	define LCD_MOVE_CURSOR						(0 << 3)
#	define LCD_SCROLL_DISPLAY					(1 << 3)
#	define LCD_MOVE_SCROLL_LEFT					(0 << 2)
#	define LCD_MOVE_SCROLL_RIGHT				(1 << 2)
#define LCD_FUNCTION_SET_CMD			0x20
#	define LCD_FUNCTION_4_BITS					(0 << 4)
#	define LCD_FUNCTION_8_BITS					(1 << 4)
#	define LCD_FUNCTION_1_LINE					(0 << 3)
#	define LCD_FUNCTION_2_LINES					(1 << 3)
#	define LCD_FUNCTION_5x8_FONT				(0 << 2)
#	define LCD_FUNCTION_5x10_FONT				(1 << 2)
#define LCD_FUNCTION_RESET_CMD			0x30
#define LCD_CGRAM_ADRESS_CMD			0x40
#define LCD_DDRAM_ADRESS_CMD			0x80

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

// FILE lcdStream = FDEV_SETUP_STREAM(lcdWriteStd, NULL, _FDEV_SETUP_WRITE);
// volatile lcdConfiguration_t *defaultDisplay = NULL;

// =============================================================================
// File exclusive - Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================






#if defined(LCD4D)
lcdResult_t lcdSetDataPort(reg_t *dataDDR, reg_t *dataPORT, uint8_t dataFirst)
#elif defined(LCD4F)
lcdResult_t lcdSetDataPort(reg_t *dataDDR, reg_t *dataPORT, reg_t *dataPIN, uint8_t dataFirst)
#elif defined(LCD8D)
lcdResult_t lcdSetDataPort(reg_t *dataDDR, reg_t *dataPORT)
#elif defined(LCD8F)
lcdResult_t lcdSetDataPort(reg_t *dataDDR, reg_t *dataPORT, reg_t *dataPIN)
#endif
{
	lcd->dataDDR = dataDDR;
	lcd->dataPORT = dataPORT;
#if defined(LCD4F) || defined(LCD8F)
	lcd->dataPIN = dataPIN;
#endif
#if defined(LCD4D) || defined(LCD4F)
	lcd->dataFirst = dataFirst;
#endif
	lcd->dataPortConfigured = true;

	return LCD_OK;
}

#if defined(LCD4D)
lcdResult_t lcdSetControlPort(reg_t *controlDDR, reg_t *controlPORT, uint8_t controlE, uint8_t controlRS)
#elif defined(LCD4F)
lcdResult_t lcdSetControlPort(reg_t *controlDDR, reg_t *controlPORT, uint8_t controlE, uint8_t controlRS,
		uint8_t controlRW)
#elif defined(LCD8D)
lcdResult_t lcdSetControlPort(reg_t *controlDDR, reg_t *controlPORT, uint8_t controlE, uint8_t controlRS)
#elif defined(LCD8F)
lcdResult_t lcdSetControlPort(reg_t *controlDDR, reg_t *controlPORT, uint8_t controlE, uint8_t controlRS,
		uint8_t controlRW)
#endif
{
	lcd->controlDDR = controlDDR;
	lcd->controlPORT = controlPORT;
	lcd->controlE = controlE;
#if defined(LCD4F) || defined(LCD8F)
	lcd->controlRW = controlRW;
#endif
	lcd->controlRS = controlRS;
	lcd->controlPortConfigured = true;

	return LCD_OK;
}

lcdResult_t lcdWriteCommand(uint8_t command)
{
#if defined(LCD4F) || defined(LCD8F)
	clrBit(*(lcd->controlPORT), lcd->controlRW);	// LCD in write mode
#endif
	clrBit(*(lcd->controlPORT), lcd->controlRS);		// LCD in command mode
	clrBit(*(lcd->controlPORT), lcd->controlE);			// Makes sure enable is LOW
#if defined(LCD4D) || defined(LCD4F)
	clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);	// Writes data (higher nibble)
	*(lcd->dataPORT) |= ((command >> 4) << lcd->dataFirst);
	setBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse start
	_delay_us(1);
	clrBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse end
	_delay_us(1);
	clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);	// Writes data (lower nibble)
	*(lcd->dataPORT) |= ((command & 0x0F) << lcd->dataFirst);
#elif
	*(lcd->dataPORT) = command;							// Writes data
#endif
	setBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse start
	_delay_us(1);
	clrBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse end
	_delay_us(1);
	if((command == LCD_CLEAR_SCREEN) || (command == LCD_CURSOR_HOME)) {
#if defined(LCD4D) || defined(LCD8D)
		_delay_ms(2);
#endif
		lcd->cursorLine = 0;
		lcd->cursorColumn = 0;
#if defined(LCD4D) || defined(LCD8D)
	} else {
		_delay_us(40);
#endif
	}

	return LCD_OK;
}

lcdResult_t lcdWriteCharacter(uint8_t character)
{
	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

#if defined(LCD4F) || defined(LCD8F)
	lcdCheckBusyFlag(lcd);
	clrBit(*(lcd->controlPORT), lcd->controlRW);	// LCD in write mode
#endif
	if(lcd->cursorColumn < 40) {
		setBit(*(lcd->controlPORT), lcd->controlRS);		// LCD in command mode
		clrBit(*(lcd->controlPORT), lcd->controlE);			// Makes sure enable is LOW
#if defined(LCD4D) || defined(LCD4F)
		clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);	// Writes data (higher nibble)
		*(lcd->dataPORT) |= ((character >> 4) << lcd->dataFirst);
		setBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse start
		_delay_us(1);
		clrBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse end
		_delay_us(1);
		clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);	// Writes data (lower nibble)
		*(lcd->dataPORT) |= ((character & 0x0F) << lcd->dataFirst);
#elif
		*(lcd->dataPORT) = character;						// Writes data
#endif
		setBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse start
		_delay_us(1);
		clrBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse end
#if defined(LCD4D) || defined(LCD8D)
		_delay_us(40);
#endif
		lcd->cursorColumn++;
	}

	return LCD_OK;
}

int16_t lcdWriteStd(int8 character, FILE *stream)
{
	uint8_t columns = 0;
	uint8_t i = 0;

	if(defaultDisplay->initialized == false) {
		return false;
	}

	switch(defaultDisplay->size) {
	case LCD_8X1:
	case LCD_8X2:
		columns = 8;
		break;
	case LCD_10x2:
		columns = 10;
		break;
	case LCD_12X2:
	case LCD_12X4:
		columns = 12;
		break;
	case LCD_16X1:
	case LCD_16X1b:
	case LCD_16X2:
	case LCD_16X4:
		columns = 16;
		break;
	case LCD_20X1:
	case LCD_20X2:
	case LCD_20X4:
		columns = 20;
		break;
	case LCD_24X1:
	case LCD_24X2:
		columns = 24;
		break;
	case LCD_30X2:
		columns = 30;
		break;
	case LCD_32X2:
		columns = 32;
		break;
	case LCD_40X1:
	case LCD_40X2:
		columns = 40;
		break;
	}

	if(character == '\n') {
		for(i = defaultDisplay->cursorColumn; i < columns; i++) {
			lcdWriteCharacter(defaultDisplay, ' ');
		}
		lcdCursorMoveNextLine(defaultDisplay);
	} else {
		lcdWriteCharacter(defaultDisplay, character);
	}

	return 0;
}

#if defined(LCD4F) || defined(LCD8F)
lcdResult_t lcdCheckBusyFlag(void)
{
	uint8_t busyFlag = 0;
#	if defined(LCD8F)
	*(lcd->dataPORT) = 0x00;
	*(lcd->dataDDR) = 0x00;
#	elif defined(LCD4F)
	clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);
	clrMask(*(lcd->dataDDR), 0x0F, lcd->dataFirst);
#	endif
	clrBit(*(lcd->controlPORT), lcd->controlRS);	// LCD in command mode
	setBit(*(lcd->controlPORT), lcd->controlRW);	// LCD in write mode
	clrBit(*(lcd->controlPORT), lcd->controlE);		// Makes sure enable is LOW
	do {
		busyFlag = 0;
		setBit(*(lcd->controlPORT), lcd->controlE);		// Enable pulse start
		_delay_us(1);
		busyFlag = *(lcd->dataPIN);
#	if defined(LCD8F)
		busyFlag &= 0x80;
#	elif defined(LCD4F)
		busyFlag &= (0x08 << lcd->dataFirst);
#	endif
		clrBit(*(lcd->controlPORT), lcd->controlE);		// Enable pulse end
		_delay_us(1);
#	if defined(LCD4F)
		setBit(*(lcd->controlPORT), lcd->controlE);		// Enable pulse start
		_delay_us(1);
		clrBit(*(lcd->controlPORT), lcd->controlE);		// Enable pulse end
		_delay_us(1);
#	endif
	} while(busyFlag);
	clrBit(*(lcd->controlPORT), lcd->controlRW);		// LCD in write mode
#	if defined(LCD8F)
	*(lcd->dataPORT) = 0x00;
	*(lcd->dataDDR) = 0xFF;
#	elif defined(LCD4F)
	clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);
	setMask(*(lcd->dataDDR), 0x0F, lcd->dataFirst);
#	endif

	return LCD_OK;
}
#endif

#if defined(LCD4D) || defined(LCD4F)
lcdResult_t lcdFunctionSet8Bits(uint8_t command)
{
#	if defined(LCD4F)
	clrBit(*(lcd->controlPORT), lcd->controlRW);		// LCD in write mode
#	endif
	clrBit(*(lcd->controlPORT), lcd->controlRS);		// LCD in command mode
	clrBit(*(lcd->controlPORT), lcd->controlE);			// Makes sure enable is LOW
	clrMask(*(lcd->dataPORT), 0x0F, lcd->dataFirst);	// Writes data
	*(lcd->dataPORT) |= ((command >> 4) << lcd->dataFirst);
	setBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse start
	_delay_us(1);
	clrBit(*(lcd->controlPORT), lcd->controlE);			// Enable pulse end
	_delay_us(1);
#	endif

	return LCD_OK;
}
#endif

lcdResult_t lcdDisplayShift(direction_t dir)
{
	uint8_t command = 0;

	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

#if defined(LCD4F) || defined(LCD8F)
	lcdCheckBusyFlag(lcd);
#endif

	if(dir == LEFT) {
		lcd->cursorColumn--;
		command = 0x18;
	} else {
		lcd->cursorColumn++;
		command = 0x1C;
	}

	return lcdWriteCommand(command);
}

lcdResult_t lcdCursorMove(direction_t dir)
{
	uint8_t command = 0;

	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

#if defined(LCD4F) || defined(LCD8F)
	lcdCheckBusyFlag(lcd);
#endif

	if(dir == LEFT) {
		lcd->cursorColumn--;
		command = 0x10;
	} else {
		lcd->cursorColumn++;
		command = 0x14;
	}

	return lcdWriteCommand(command);
}

lcdResult_t lcdCursorMoveFirstLine(void)
{
	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

	return lcdCursorHome(lcd);
}

lcdResult_t lcdCursorMoveNextLine(void)
{
	uint8_t line = 0;

	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

	switch(lcd->size) {
	case LCD_8X1:
	case LCD_16X1:
	case LCD_16X1b:
	case LCD_20X1:
	case LCD_24X1:
	case LCD_40X1:
		return lcdCursorGoTo((line + 1), 1);
	case LCD_8X2:
	case LCD_10x2:
	case LCD_12X2:
	case LCD_16X2:
	case LCD_20X2:
	case LCD_24X2:
	case LCD_30X2:
	case LCD_32X2:
	case LCD_40X2:
		line = (lcd->cursorLine == 1) ? 0 : 1;
		return lcdCursorGoTo((line + 1), 1);
	case LCD_12X4:
	case LCD_16X4:
	case LCD_20X4:
		line = (lcd->cursorLine == 3) ? 0 : (lcd->cursorLine + 1);
		return lcdCursorGoTo((line + 1), 1);
	default:
		return LCD_UNSUPPORTED_DISPLAY_SIZE;
	}
}

lcdResult_t lcdStdio(void)
{
	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

	stdin = stdout = stderr = &lcdStream;
	defaultDisplay = lcd;

	return LCD_OK;
}

lcdResult_t lcdCursorGoTo(uint8_t line, uint8_t column)
{
	uint8_t address = 0x00;

	if(lcd->initialized == false) {
		return LCD_NOT_INITIALIZED;
	}

	if(line == 1) {
		switch(lcd->size) {
		case LCD_8X1:
		case LCD_16X1:
		case LCD_16X1b:
		case LCD_20X1:
		case LCD_24X1:
		case LCD_40X1:
		case LCD_8X2:
		case LCD_10x2:
		case LCD_12X2:
		case LCD_16X2:
		case LCD_20X2:
		case LCD_24X2:
		case LCD_30X2:
		case LCD_32X2:
		case LCD_40X2:
		case LCD_12X4:
		case LCD_16X4:
		case LCD_20X4:
			address += (column - 1);
			break;
		default:
			return LCD_UNSUPPORTED_DISPLAY_SIZE;
		}
	} else if(line == 2) {
		switch(lcd->size) {
		case LCD_8X1:
		case LCD_16X1:
		case LCD_16X1b:
		case LCD_20X1:
		case LCD_24X1:
		case LCD_40X1:
			return LCD_UNSUPPORTED_PARAMETER;
		case LCD_8X2:
		case LCD_10x2:
		case LCD_12X2:
		case LCD_16X2:
		case LCD_20X2:
		case LCD_24X2:
		case LCD_30X2:
		case LCD_32X2:
		case LCD_40X2:
		case LCD_12X4:
		case LCD_16X4:
		case LCD_20X4:
			address += (0x40 + column - 1);
			break;
		default:
			return LCD_UNSUPPORTED_DISPLAY_SIZE;
		}
	} else if(line == 3) {
		switch(lcd->size) {
		case LCD_8X1:
		case LCD_16X1:
		case LCD_16X1b:
		case LCD_20X1:
		case LCD_24X1:
		case LCD_40X1:
		case LCD_8X2:
		case LCD_10x2:
		case LCD_12X2:
		case LCD_16X2:
		case LCD_20X2:
		case LCD_24X2:
		case LCD_30X2:
		case LCD_32X2:
		case LCD_40X2:
			return LCD_UNSUPPORTED_PARAMETER;
		case LCD_12X4:
			address += (0x0C + column - 1);
			break;
		case LCD_16X4:
			address += (0x10 + column - 1);
			break;
		case LCD_20X4:
			address += (0x14 + column - 1);
			break;
		default:
			return LCD_UNSUPPORTED_DISPLAY_SIZE;
		}
	} else {
		switch(lcd->size) {
		case LCD_8X1:
		case LCD_16X1:
		case LCD_16X1b:
		case LCD_20X1:
		case LCD_24X1:
		case LCD_40X1:
		case LCD_8X2:
		case LCD_10x2:
		case LCD_12X2:
		case LCD_16X2:
		case LCD_20X2:
		case LCD_24X2:
		case LCD_30X2:
		case LCD_32X2:
		case LCD_40X2:
			return LCD_UNSUPPORTED_PARAMETER;
		case LCD_12X4:
			address += (0x4C + column - 1);
			break;
		case LCD_16X4:
			address += (0x50 + column - 1);
			break;
		case LCD_20X4:
			address += (0x54 + column - 1);
			break;
		default:
			return LCD_UNSUPPORTED_DISPLAY_SIZE;
		}
	}

	lcd->cursorLine = line - 1;
	lcd->cursorColumn = column - 1;

	return lcdWriteCommand((LCD_DDRAM_ADRESS | address));
}
