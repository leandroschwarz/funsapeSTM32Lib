/* -----------------------------------------------------------------------------
 * Project:			Counter using a 4-digit multiplexed 7-Segments Display
 * File:			muxDisplayCounter.c
 * Author:			Leandro Schwarz
 * Version:			1.0
 * Last edition:	March 18, 2018
 * Purpose:			Controls a 4-digit multiplexed 7-Segments Display Common
 *					Anode and increments its value cyclically. TIMER1 in CTC
 *					mode is used to update the counter value (2 Hz) and TIMER0
 *					in CTC mode is used for display multiplexing (1 kHz). The
 *					MCU Clock frequency is 16 MHz, and the device is an
 *					ATmega328P.
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// System definitions ----------------------------------------------------------

#define F_CPU 16000000UL

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include <globalDefines.h>
#include <timer0.h>
#include <timer1.h>
#include <util/hexToSevenSegments.h>

// -----------------------------------------------------------------------------
// Project definitions ---------------------------------------------------------

#define DISPLAY_SEGMENTS_DDR	DDRD
#define DISPLAY_SEGMENTS_PORT	PORTD
#define DISPLAY_CONTROL_DDR		DDRB
#define DISPLAY_CONTROL_PORT	PORTB
#define DISPLAY_CONTROL_FIRST	PB2

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef volatile union {
    struct {
        bool_t	showDigit	: 1;
        uint8_t	digit		: 2;
        uint8_t	unusedBits	: 5;
    };
    uint8_t allFlags;
} systemFlags_t;

// -----------------------------------------------------------------------------
// Function declaration --------------------------------------------------------

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

systemFlags_t systemFlags;
vuint16_t counter = 1802;

// -----------------------------------------------------------------------------
// Main function ---------------------------------------------------------------

int main(void)
{
    // Variable declaration

    // Variable initialization
    systemFlags.allFlags = 0;

    // DISPLAY configuration
    DISPLAY_SEGMENTS_PORT = 0xFF;
    DISPLAY_SEGMENTS_DDR = 0xFF;
    setMaskOffset(DISPLAY_CONTROL_PORT, 0x0F, DISPLAY_CONTROL_FIRST);
    setMaskOffset(DISPLAY_CONTROL_DDR, 0x0F, DISPLAY_CONTROL_FIRST);

    // TIMER0 configuration
    timer0Config(TIMER0_MODE_CTC, TIMER0_PRESCALER_64);
    timer0SetCompareAValue(250);
    timer0ActivateCompareAInterrupt();

    // TIMER1 configuration
    timer1Config(TIMER1_MODE_CTC_OCRA, TIMER1_PRESCALER_256);
    timer1SetCompareAValue(31250);
    timer1ActivateCompareAInterrupt();

    // Enable Global Interrupts
    sei();

    while (1) {
        if (systemFlags.showDigit) {
            setMaskOffset(DISPLAY_CONTROL_PORT, 0x0F, DISPLAY_CONTROL_FIRST);
            switch (systemFlags.digit) {
            case 0:
                DISPLAY_SEGMENTS_PORT = hexToSevenSegments(counter % 10, DISPLAY_COMMON_ANODE, FALSE);
                break;
            case 1:
                DISPLAY_SEGMENTS_PORT = hexToSevenSegments((counter / 10) % 10, DISPLAY_COMMON_ANODE, FALSE);
                break;
            case 2:
                DISPLAY_SEGMENTS_PORT = hexToSevenSegments((counter / 100) % 10, DISPLAY_COMMON_ANODE, FALSE);
                break;
            case 3:
                DISPLAY_SEGMENTS_PORT = hexToSevenSegments((counter / 1000) % 10, DISPLAY_COMMON_ANODE, FALSE);
                break;
            }
            clrBit(DISPLAY_CONTROL_PORT, DISPLAY_CONTROL_FIRST + systemFlags.digit);
            systemFlags.digit = (systemFlags.digit == 3) ? 0 : (systemFlags.digit + 1);
            systemFlags.showDigit = FALSE;
        }
    }

    return 0;
}

// -----------------------------------------------------------------------------
// Interruption handlers -------------------------------------------------------

ISR(TIMER0_COMPA_vect)
{
    systemFlags.showDigit = TRUE;
}

ISR(TIMER1_COMPA_vect)
{
    counter = (counter == 9999) ? 0 : (counter + 1);
}

// -----------------------------------------------------------------------------
// Function definitions --------------------------------------------------------
