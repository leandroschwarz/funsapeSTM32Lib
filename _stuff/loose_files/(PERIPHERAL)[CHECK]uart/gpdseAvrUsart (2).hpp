/* =============================================================================
 * Project:		GPSDE++ AVR Library
 * File name:	gpdseAvrUsart.hpp
 * Module:		USART Module Interface for GPDSE++ AVR Library project
 * Author:		Leandro Schwarz
 * Build:		__BUILD_MACRO_TO_BE_CHANGED__
 * Date:		__DATE_MACRO_TO_BE_CHANGED__
 * ========================================================================== */

// =============================================================================
// File build
// =============================================================================

#ifndef __GPDSE_AVR_USART_HPP
#define __GPDSE_AVR_USART_HPP			__BUILD_MACRO_TO_BE_CHANGED__

// =============================================================================
// System file dependencies
// =============================================================================

#include <gpdseAvrGlobalDefines.hpp>
#if __GPDSE_AVR_GLOBAL_DEFINES_HPP != __BUILD_MACRO_TO_BE_CHANGED__
#	error	Global definitions file (gpdseAvrGlobalDefines) must be build __BUILD_MACRO_TO_BE_CHANGED__.
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
// Macro-functions
// =============================================================================

// NONE

// =============================================================================
// New data types - Single variables
// =============================================================================

// NONE

// =============================================================================
// New data types - Enumerations (logic values)
// =============================================================================

// NONE

// =============================================================================
// New data types - Enumerations (small and finite lists)
// =============================================================================

// NONE

// =============================================================================
// New data types - Enumerations (large or expansible lists)
// =============================================================================

typedef enum usartBaudRate_e {
	// Standardized Baud Rates from 75 baud
	USART_BAUD_RATE_75					= 75,			// Used in most old modems
	USART_BAUD_RATE_150					= 150,			// 2x	75 bauds
	USART_BAUD_RATE_300					= 300,			// 2x	150 bauds
	USART_BAUD_RATE_600					= 600,			// 2x	300 bauds
	USART_BAUD_RATE_1200				= 1200,			// 2x	600 bauds
	USART_BAUD_RATE_1800				= 1800,			// 1.5x	1200 bauds
	USART_BAUD_RATE_2400				= 2400,			// 2x	1200 bauds
	USART_BAUD_RATE_4800				= 4800,			// 2x	2400 bauds
	USART_BAUD_RATE_9600				= 9600,			// 2x	4800 bauds
	USART_BAUD_RATE_14400				= 14400,		// 1.5x	9600 bauds
	USART_BAUD_RATE_19200				= 19200,		// 2x	9600 bauds
	USART_BAUD_RATE_28800				= 28800,		// 1.5x	19200 bauds
	USART_BAUD_RATE_38400				= 38400,		// 2x	19200 bauds

	// Standardized Baud Rates from 1600 baud
	USART_BAUD_RATE_1600				= 1600,			// Used in 4.8 kbit/s modems
	USART_BAUD_RATE_3200				= 3200,			// 2x	1600 bauds

	// Standardized Baud Rates from 56000 baud
	USART_BAUD_RATE_56000				= 56000,		// Analog telephone line limit
	USART_BAUD_RATE_128000				= 128000,		// 2x	56000 bauds
	USART_BAUD_RATE_256000				= 256000,		// 2x	128000 bauds

	// Standardized Baud Rates from 57600 baud
	USART_BAUD_RATE_57600				= 57600,		// 1.5x	38400 bauds
	USART_BAUD_RATE_115200				= 115200,		// 2x	57600 bauds
	USART_BAUD_RATE_230400				= 230400,		// 2x	115200 bauds
	USART_BAUD_RATE_460800				= 460800,		// 2x	230400 bauds
	USART_BAUD_RATE_921600				= 921600,		// 2x	460800 bauds

	// Standardized Baud Rates from 250000 baud
	USART_BAUD_RATE_250000				= 250000,		// Standard baud
	USART_BAUD_RATE_500000				= 500000,		// 2x	250000 bauds
	USART_BAUD_RATE_1000000				= 1000000,		// 2x	500000 bauds

	// Other Rarely Used Baud Rates
	USART_BAUD_RATE_60					= 60,			// Used in some old teletypewriters
	USART_BAUD_RATE_110					= 110,			// Used in some old modems
	USART_BAUD_RATE_3429				= 3429,			// Used in 33.6 and some 56 kbit/s modems
	USART_BAUD_RATE_8000				= 8000,			// Used in some 56 kbit/s modems
} usartBaudRate_e;

typedef enum usartDataLength_e {
	USART_DATA_LENGTH_4_BITS			= 4,
	USART_DATA_LENGTH_5_BITS			= 5,
	USART_DATA_LENGTH_6_BITS			= 6,
	USART_DATA_LENGTH_7_BITS			= 7,
	USART_DATA_LENGTH_8_BITS			= 8,
	USART_DATA_LENGTH_9_BITS			= 9,
	USART_DATA_LENGTH_10_BITS			= 10,
	USART_DATA_LENGTH_11_BITS			= 11,
	USART_DATA_LENGTH_12_BITS			= 12,
	USART_DATA_LENGTH_13_BITS			= 13,
	USART_DATA_LENGTH_14_BITS			= 14,
	USART_DATA_LENGTH_15_BITS			= 15,
	USART_DATA_LENGTH_16_BITS			= 0,
} usartDataLength_e;

typedef enum usartFrameFormat_e : uint16_t {
	// *INDENT-OFF*						= 0b0000000'DDDD'PPP'SS
	//									            DDDD        -> Number of data bits {4=(4)...15=(15); 0=(16)}
	//									                 PPP    -> Parity {0=(NONE); 1=(ODD); 2=(EVEN); 3=(MARK); 4=(SPACE)}
	//									                     SS -> Number of stop bits {0=(1); 1=(1.5); 2=(2)}
	USART_FRAME_FORMAT_8_N_1			= 0b0000000'1000'000'00,
	USART_FRAME_FORMAT_8_O_1			= 0b0000000'1000'001'00,
	USART_FRAME_FORMAT_8_E_1			= 0b0000000'1000'010'00,
	USART_FRAME_FORMAT_8_N_2			= 0b0000000'1000'000'10,
	USART_FRAME_FORMAT_8_O_2			= 0b0000000'1000'001'10,
	USART_FRAME_FORMAT_8_E_2			= 0b0000000'1000'010'10,
	USART_FRAME_FORMAT_9_N_1			= 0b0000000'1001'000'00,
	USART_FRAME_FORMAT_9_O_1			= 0b0000000'1001'001'00,
	USART_FRAME_FORMAT_9_E_1			= 0b0000000'1001'010'00,
	USART_FRAME_FORMAT_9_N_2			= 0b0000000'1001'000'10,
	USART_FRAME_FORMAT_9_O_2			= 0b0000000'1001'001'10,
	USART_FRAME_FORMAT_9_E_2			= 0b0000000'1001'010'10,
	USART_FRAME_FORMAT_5_N_1			= 0b0000000'0101'000'00,
	USART_FRAME_FORMAT_5_O_1			= 0b0000000'0101'001'00,
	USART_FRAME_FORMAT_5_E_1			= 0b0000000'0101'010'00,
	USART_FRAME_FORMAT_5_N_2			= 0b0000000'0101'000'10,
	USART_FRAME_FORMAT_5_O_2			= 0b0000000'0101'001'10,
	USART_FRAME_FORMAT_5_E_2			= 0b0000000'0101'010'10,
	USART_FRAME_FORMAT_6_N_1			= 0b0000000'0110'000'00,
	USART_FRAME_FORMAT_6_O_1			= 0b0000000'0110'001'00,
	USART_FRAME_FORMAT_6_E_1			= 0b0000000'0110'010'00,
	USART_FRAME_FORMAT_6_N_2			= 0b0000000'0110'000'10,
	USART_FRAME_FORMAT_6_O_2			= 0b0000000'0110'001'10,
	USART_FRAME_FORMAT_6_E_2			= 0b0000000'0110'010'10,
	USART_FRAME_FORMAT_7_N_1			= 0b0000000'0111'000'00,
	USART_FRAME_FORMAT_7_O_1			= 0b0000000'0111'001'00,
	USART_FRAME_FORMAT_7_E_1			= 0b0000000'0111'010'00,
	USART_FRAME_FORMAT_7_N_2			= 0b0000000'0111'000'10,
	USART_FRAME_FORMAT_7_O_2			= 0b0000000'0111'001'10,
	USART_FRAME_FORMAT_7_E_2			= 0b0000000'0111'010'10
	// *INDENT-ON*
} usartFrameFormat_e;

typedef enum usartMode_e {
	USART_MODE_ASYNCHRONOUS				= 0,
	USART_MODE_SYNCHRONOUS_SLAVE		= 1,
	USART_MODE_SYNCHRONOUS_MASTER		= 2,
	USART_MODE_SPI_EMULATION_MASTER		= 3
} usartMode_e;

typedef enum usartParity_e {
	USART_PARITY_NONE					= 0,
	USART_PARITY_ODD					= 1,
	USART_PARITY_EVEN					= 2,
	USART_PARITY_MARK					= 3,
	USART_PARITY_SPACE					= 4
} usartParity_e;

typedef enum usartStopBits_e {
	USART_STOP_BIT_SINGLE				= 0,
	USART_STOP_BIT_ONE_HALF				= 1,
	USART_STOP_BIT_DOUBLE				= 2
} usartStopBits_e;

// =============================================================================
// New data types - Enumerations (algebraic operated list elements)
// =============================================================================

// NONE

// =============================================================================
// New data types - Enumerations (bitwise operated flags)
// =============================================================================

typedef enum usartError_f {
	USART_ERROR_NONE					= 0x00,
	USART_ERROR_FRAME					= 0x01,
	USART_ERROR_PARITY					= 0x02,
	USART_ERROR_BUFFER_OVERFLOW			= 0x04,
	USART_ERROR_ALL						= 0x07
} usartError_f;

inlined usartError_f operator|(usartError_f a, usartError_f b)
{
	return static_cast<usartError_f>(static_cast<int>(a) | static_cast<int>(b));
}

inlined usartError_f& operator|=(usartError_f& a, usartError_f b)
{
	return a = a | b;
}

inlined usartError_f operator&(usartError_f a, usartError_f b)
{
	return static_cast<usartError_f>(static_cast<int>(a) & static_cast<int>(b));
}

inlined usartError_f& operator&=(usartError_f& a, usartError_f b)
{
	return a = a & b;
}

inlined usartError_f operator~(usartError_f a)
{
	return static_cast<usartError_f>(static_cast<int>(USART_ERROR_ALL) ^ static_cast<int>(a));
}

// =============================================================================
// Extern global variables
// =============================================================================

extern FILE usartStream;

// =============================================================================
// Usart - Class declaration
// =============================================================================

// -----------------------------------------------------------------------------
// Usart0 ----------------------------------------------------------------------

#if USART0_EXISTS
class Usart0
{
	// -------------------------------------------------------------------------
	// New data types
	// -------------------------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Operators overloading
	// -------------------------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Constructors
	// -------------------------------------------------------------------------

public:
	Usart0(	usartBaudRate_e baudRate,
			usartMode_e mode			= USART_MODE_ASYNCHRONOUS,
			usartFrameFormat_e format	= USART_FRAME_FORMAT_8_N_1
		  );
	Usart0(void);

	// -------------------------------------------------------------------------
	// Methods
	// -------------------------------------------------------------------------

public:
	//     ///////////////////     INITIALIZATION     ///////////////////     //
	bool deinitialize(void);
	void flushDataReceptionBuffer(void);
	bool initialize(void);
	inlined void setReceiver(bool enabled);
	inlined void setTransmitter(bool enabled);

	//     ///////////////     PROTOCOL CONFIGURATION     ///////////////     //
	bool setBaudRate(usartBaudRate_e baudRate);
	bool setDataLength(usartDataLength_e length);
	bool setMode(usartMode_e mode, usartBaudRate_e baudRate);
	bool setParity(usartParity_e parity);
	bool setStopBits(usartStopBits_e stopBit);

	//     ////////////////////     CHECK STATUS     ////////////////////     //
	error_e getLastError(void);
	bool getLastReceptionError(usartError_f * receptionError);
	inlined bool isDataBufferEmpty(void);
	inlined bool isReceptionComplete(void);
	inlined bool isTransmissionComplete(void);

	//     //////////////     COMMUNICATION  INTERFACE     //////////////     //
	bool receiveData(uint8_t * data);
	bool receiveData(uint16_t * data);
	bool sendData(uint8_t data);
	bool sendData(uint16_t data);

	//     ///////////////////     DATA STREAMING     ///////////////////     //
	char receiveDataStd(FILE *stream);
	inlined void remapStdio(void);
	int_t sendDataStd(char data, FILE *stream);

	//     ////////////////////     INTERRUPTION     ////////////////////     //
	inlined void setInterruptDataBufferEmpty(bool enabled);
	inlined void setInterruptReceptionComplete(bool enabled);
	inlined void setInterruptTransmissionComplete(bool enabled);

private:
	//     ////////////////     DATA MEMBER UPDATING     ////////////////     //
	void _resetDataMembers(void);

	//     //////////////////     DATA  VALIDATION     //////////////////     //
	bool _validateDataLength(usartDataLength_e dataLength);
	bool _validateModeAndBaudRate(usartMode_e mode, usartBaudRate_e baudRate);
	bool _validateParity(usartParity_e parity);
	bool _validateStopBits(usartStopBits_e stopBits);

	//     ////////////////////     CHECK STATUS     ////////////////////     //
	bool _checkReceptionErrors(void);

	// -------------------------------------------------------------------------
	// Properties
	// -------------------------------------------------------------------------

private:
	//     ///////////////////     INITIALIZATION     ///////////////////     //
	bool				_initialized					: 1;
	bool				_receiverEnabled				: 1;
	bool				_transmitterEnabled				: 1;

	//     ///////////////     PROTOCOL CONFIGURATION     ///////////////     //
	usartBaudRate_e		_baudRate						: 20;
	usartDataLength_e	_dataLength						: 4;
	bool				_doubleSpeed					: 1;
	usartMode_e			_mode							: 2;
	usartParity_e		_parity							: 3;
	usartStopBits_e		_stopBits						: 2;

	//     ///////////////////     ERROR MESSAGES     ///////////////////     //
	error_e				_lastError;
	usartError_f		_lastReceptionErrors			: 3;

	//     /////////////////////     INTERRUPTS     /////////////////////     //
	bool				_intDataBufEmptyEnabled			: 1;
	bool				_intRecepComplEnabled			: 1;
	bool				_intTransComplEnabled			: 1;

	//     ///////////////////////     TO  DO     ///////////////////////     //
	bool				_multiProcessorEnabled			: 1;
	bool				_clockPolarityInverted			: 1;
	bool				_masterRoleEnabled				: 1;

}; // class Usart0

// =============================================================================
// Usart0 - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Usart0 - Class inline function definitions
// =============================================================================

inlined bool Usart0::isDataBufferEmpty(void)
{
	return isBitSet(UCSR0A, UDRE0);
}

inlined bool Usart0::isReceptionComplete(void)
{
	return isBitSet(UCSR0A, RXC0);
}

inlined bool Usart0::isTransmissionComplete(void)
{
	return isBitSet(UCSR0A, TXC0);
}

inlined void Usart0::remapStdio(void)
{
	stdin = stdout = stderr = &usartStream;
	return;
}

inlined void Usart0::setInterruptDataBufferEmpty(bool enabled)
{
	this->_intDataBufEmptyEnabled = enabled;
	if (enabled) {
		setBit(UCSR0B, UDRIE0);
	} else {
		clrBit(UCSR0B, UDRIE0);
	}
	return;
}

inlined void Usart0::setInterruptReceptionComplete(bool enabled)
{
	this->_intRecepComplEnabled = enabled;
	if (enabled) {
		setBit(UCSR0B, RXCIE0);
	} else {
		clrBit(UCSR0B, RXCIE0);
	}
	return;
}

inlined void Usart0::setInterruptTransmissionComplete(bool enabled)
{
	this->_intTransComplEnabled = enabled;
	if (enabled) {
		setBit(UCSR0B, TXCIE0);
	} else {
		clrBit(UCSR0B, TXCIE0);
	}
	return;
}

inlined void Usart0::setReceiver(bool enabled)
{
	this->_receiverEnabled = enabled;
	if (enabled) {
		setBit(UCSR0B, RXEN0);
	} else {
		clrBit(UCSR0B, RXEN0);
	}
	return;
}

inlined void Usart0::setTransmitter(bool enabled)
{
	this->_transmitterEnabled = enabled;
	if (enabled) {
		setBit(UCSR0B, TXEN0);
	} else {
		clrBit(UCSR0B, TXEN0);
	}
	return;
}
#endif // USART0_EXISTS

// -----------------------------------------------------------------------------
// Usart1
// -----------------------------------------------------------------------------

#if USART1_EXISTS

// =============================================================================
// Usart1 - Class declaration
// =============================================================================

class Usart1
{

}; // class Usart1

#endif // USART1_EXISTS

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

#if USART0_EXISTS
extern Usart0 usart0;
#endif // USART0_EXISTS

#if USART1_EXISTS
extern Usart1 usart1;
#endif // USART1_EXISTS

#endif // __GPDSE_AVR_USART_HPP
