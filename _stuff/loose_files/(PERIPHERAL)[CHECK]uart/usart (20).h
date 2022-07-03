/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			usart.h
 * Module:			USART module
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 18, 2018
 * -------------------------------------------------------------------------- */

#ifndef __USART_H
#define __USART_H 1

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBAL_DEFINES_H != 1
	#error Error 100 - globalDefines.h - wrong build (globalDefines must be build 1).
#endif
#include <stdio.h>

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum usartError_t {
	USART_NO_ERRORS = 0,
	USART_FRAME_ERROR = 1,
	USART_PARITY_ERROR  = 2,
	USART_BUFFER_OVERFLOW_ERROR = 4
} usartError_t;

typedef enum usartDataBits_t {
	USART_DATA_BITS_5 = 0,
	USART_DATA_BITS_6,
	USART_DATA_BITS_7,
	USART_DATA_BITS_8,
	USART_DATA_BITS_9,
	USART_DATA_BITS_NO_CHANGE = 0xFF
} usartDataBits_t;

typedef enum usartStopBits_t {
	USART_STOP_BIT_SINGLE = 0,
	USART_STOP_BIT_DOUBLE,
	USART_STOP_BIT_NO_CHANGE = 0xFF
} usartStopBits_t;

typedef enum usartParity_t {
	USART_PARITY_NONE = 0,
	USART_PARITY_ODD,
	USART_PARITY_EVEN,
	USART_PARITY_NO_CHANGE = 0xFF
} usartParity_t;

typedef enum usartMode_t {
	USART_MODE_ASYNCHRONOUS = 0,
	USART_MODE_ASYNCHRONOUS_DOUBLE_SPEED,
	USART_MODE_SYNCHRONOUS_XCK_FALLING,
	USART_MODE_SYNCHRONOUS_XCK_RISING,
	USART_MODE_SYNCHRONOUS_SPI,
	USART_MODE_NO_CHANGE = 0xFF
} usartMode_t;

typedef enum usartBaudRate_t {
	USART_BAUD_600 = 600UL,
	USART_BAUD_1200 = 1200UL,
	USART_BAUD_1800 = 1800UL,
	USART_BAUD_2400 = 2400UL,
	USART_BAUD_4800 = 4800UL,
	USART_BAUD_9600 = 9600UL,
	USART_BAUD_14400 = 14400UL,
	USART_BAUD_19200 = 19200UL,
	USART_BAUD_28800 = 28800UL,
	USART_BAUD_38400 = 38400UL,
	USART_BAUD_56000 = 56000UL,
	USART_BAUD_57600 = 57600UL,
	USART_BAUD_115200 = 115200UL,
	USART_BAUD_128000 = 128000UL,
	USART_BAUD_230400 = 230400UL,
	USART_BAUD_256000 = 256000UL,
	USART_BAUD_NO_CHANGE = 0xFFFFFFFFUL
} usartBaudRate_t;

// -----------------------------------------------------------------------------
// Global variable declarations ------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Macrofunctions --------------------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

void			usartInit(usartMode_t mode, usartBaudRate_t baudRate, usartDataBits_t dataBits, usartParity_t parity, usartStopBits_t stopBits);
void			usartEnableReceiver(void);
void			usartDisableReceiver(void);
void			usartEnableTransmitter(void);
void			usartDisableTransmitter(void);
void			usartActivateReceptionCompleteInterrupt(void);
void			usartDeactivateReceptionCompleteInterrupt(void);
void			usartActivateTransmissionCompleteInterrupt(void);
void			usartDeactivateTransmissionCompleteInterrupt(void);
void			usartActivateBufferEmptyInterrupt(void);
void			usartDeactivateBufferEmptyInterrupt(void);
bool_t			usartIsReceptionComplete(void);
bool_t			usartIsTransmissionComplete(void);
bool_t			usartIsBufferEmpty(void);
usartError_t	usartCheckErrors(void);
void			usartTransmit(uint8_t data);
void			usartTransmit9bits(uint16_t data);
uint8_t			usartReceive(void);
uint16_t			usartReceive9bits(void);
void			usartFlushReceptionBuffer(void);
void			usartStdio(void);

#endif
