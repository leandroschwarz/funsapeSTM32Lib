/* =============================================================================
 * Project:		Package Tester
 * File name:	main.cpp
 * Author:		Leandro Schwarz
 * Date:		September 05, 2018
 * Purpose:		Tool to generate and test API Packages using USART interface.
 * ========================================================================== */

// =============================================================================
// Include files
// =============================================================================

#include <gpdseAvrGlobalDefines.hpp>
#include <avr/interrupt.h>
#include <gpdseAvrUsart.hpp>
#include <gpdseAvrLcd.hpp>

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// Data Stored in Flash
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

typedef enum errorCodes_e {
	ERROR_CODE_LCD_OBJECT_CREATION				= 1,
	ERROR_CODE_LCD_INITIALIZATION				= 2,
	ERROR_CODE_USART_OBJECT_CREATION			= 3,
	ERROR_CODE_USART_INITIALIZATION				= 4,
} errorCodes_e;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Function declarations
// =============================================================================

void reportError(uint8_t errorCode);
void reportError(error_e error)
{
	usart0.remapStdio();
	printf("ERROR CODE: %d\r", error);
	systemHalt();
}

// -----------------------------------------------------------------------------
// Main Function ---------------------------------------------------------------

int main(void)
{
	// =========================================================================
	// General Purpose Variables
	// =========================================================================

	uint8_t counter = 0;

	// =========================================================================
	// Variable Initialization
	// =========================================================================

	// NONE

	// =========================================================================
	// LED Configuration
	// =========================================================================

	ledEnable();
	ledTurnOff();

	// =========================================================================
	// Lcd Configuration
	// =========================================================================

	Lcd display;
	if (display.getLastError()) {
		reportError(ERROR_CODE_LCD_OBJECT_CREATION);
	}
	if (!display.initialize()) {
		reportError(ERROR_CODE_LCD_INITIALIZATION);
	}
	display.remapStdio();
	printf(" Package Tester \n\n");
	_delay_ms(3000);
	display.clearScreen();

	// =========================================================================
	// Usart0 Configuration
	// =========================================================================

	if (usart0.getLastError()) {
		reportError(ERROR_CODE_USART_OBJECT_CREATION);
	}
	usart0.setTransmitter(ACTIVATION_ON);
	usart0.setReceiver(ACTIVATION_ON);
	if (!usart0.initialize()) {
		reportError(ERROR_CODE_USART_INITIALIZATION);
	}

	// =========================================================================
	// Enable Global Interrupts
	// =========================================================================

	sei();

	// -------------------------------------------------------------------------
	// Main Loop ---------------------------------------------------------------
	while (1) {
		usart0.sendData(counter);

		_delay_ms(100);
	}

	// -------------------------------------------------------------------------
	// Never Reached Return ----------------------------------------------------
	return 0;
}

// =============================================================================
// Interruption Handlers
// =============================================================================

// NONE

// =============================================================================
// Function Definitions
// =============================================================================

void reportError(uint8_t errorCode)
{
	while (1) {
		uint8_t i = errorCode;
		do {
			ledTurnOn();
			_delay_ms(200);
			ledTurnOff();
			_delay_ms(200);
		} while (--i);
		_delay_ms(2000);
	}
}
