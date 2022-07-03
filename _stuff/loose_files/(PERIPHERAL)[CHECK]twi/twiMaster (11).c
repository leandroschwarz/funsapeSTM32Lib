/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			twiMaster.c
 * Module:			Two Wire Interface module in master mode
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 *					Fábio Cabral Pacheco
 * Build:			1
 * Last edition:	October 10, 2017
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "twiMaster.h"
#if __TWIMASTER_H != 1
	#error Error 101 - Build mismatch on header and source code files (twiMaster).
#endif

// -----------------------------------------------------------------------------
// Private function declarations -----------------------------------------------

bool_t static twiMasterIsBusy(void);
// void static twiMasterGetStatus(void);
void twiMasterReadFromBuffer(uint8 *message, uint8 messageSize);

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

static uint8 twiBufferData[TWI_BUFFER_SIZE];	// Transceiver buffer
static uint8 twiBufferSize;						// Number of bytes to be transmitted
static twiState_t twiState = TWI_NO_STATE;		// twiSatet_t is defined in twiMaster.h
twiStatus_t twiStatus = {.all = 0};					// twiStatus_t is defined in twiMaster.h

// -----------------------------------------------------------------------------
// Private functions -----------------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	twiMasterIsBusy
 * Purpose:		Checks if transceiver is busy
 * Arguments:	none
 * Returns:		bool_t		TRUE / FALSE
 * -------------------------------------------------------------------------- */

bool_t twiMasterIsBusy(void)
{
	if(isBitSet(TWCR, TWIE))
		return TRUE;
	return FALSE;
}

// /* -----------------------------------------------------------------------------
//  * Function:	twiMasterGetStatus
//  * Purpose:		Returns the state of the last transmission
//  * Arguments:	none
//  * Returns:		none
//  * -------------------------------------------------------------------------- */
// 
// void twiMasterGetStatus(void)
// {
// 	while(twiMasterIsBusy())
// 		;	// Wait until TWI has completed the transmission
// 	return;
// }

/* -----------------------------------------------------------------------------
 * Function:	twiMasterReadFromBuffer
 * Purpose:		Reads data from buffer after a reception
 * Arguments:	message				pointer to where data must be copied into
 * 				messageSize			number of bytes to be read from buffer
 * Returns:		none
 * -------------------------------------------------------------------------- */

void twiMasterReadFromBuffer(uint8 *message, uint8 messageSize)
{
	uint8 i;

	while(twiMasterIsBusy())
		;	// Wait until TWI is ready for next transmission
	if(twiStatus.lastTransOK){			// Last transmission competed successfully
		for(i = 0;i < messageSize;i++){	// Copy data from Transceiver buffer
			message[i] = twiBufferData[i + 1];
		}
	}

	return;
}

// -----------------------------------------------------------------------------
// Public functions ------------------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	twiMasterInit
 * Purpose:		Initializes the TWI module in master mode
 * Arguments:	clockSpeed		Approximate value of the SCL clock speed
 * Returns:		none
 * Notes:		Since the controller is interrupt-driven, the interruptions must
 * 				be enabled in the main code just after this function is called
 * -------------------------------------------------------------------------- */

void twiMasterInit(uint32 clockSpeed)
{
	uint32 aux32 = 0;
	uint8 aux8 = 0;

	aux32 = (uint32)F_CPU / (uint32)clockSpeed;

	if(aux32 <= 526){			// Prescaler 1
		aux8 = (uint8)((((uint32)F_CPU / (uint32)clockSpeed) - 16) / 2);
		clrBit(TWSR, TWPS1);
		clrBit(TWSR, TWPS0);
	}else if(aux32 <= 2056){	// Prescaler 4
		aux8 = (uint8)((((uint32)F_CPU / (uint32)clockSpeed) - 16) / 8);
		clrBit(TWSR, TWPS1);
		setBit(TWSR, TWPS0);
	}else if(aux32 <= 8176){	// Prescaler 16
		aux8 = (uint8)((((uint32)F_CPU / (uint32)clockSpeed) - 16) / 32);
		setBit(TWSR, TWPS1);
		clrBit(TWSR, TWPS0);
	}else if(aux32 <= 32656){	// Prescaler 64
		aux8 = (uint8)((((uint32)F_CPU / (uint32)clockSpeed) - 16) / 128);
		setBit(TWSR, TWPS1);
		setBit(TWSR, TWPS0);
	}else{
		return;
	}
	TWBR = aux8;
	TWDR = 0xFF;				// Release SDA
	TWCR = 1 << TWEN;			// Activate TWI interface

	return;
}

/* -----------------------------------------------------------------------------
 * Function:	twiMasterSendData
 * Purpose:		Sends data from master to slave device
 * Arguments:	deviceAddress		Bus address of the slave device or
 * 									TWI_GENERAL_CALL_ADDRESS for a general call
 * 				readWrite			twiOperation_t enumeration
 * 				message				message to be transmitted
 * 				messageSize			number of bytes to be sent or read
 * Returns:		none
 * Notes:		When reading the device, the bytes received will be available
 * 				in message argument
 * -------------------------------------------------------------------------- */

void twiMasterSendData(uint8 deviceAddress, twiOperation_t readWrite, uint8 *message, uint8 messageSize)
{
	uint8 i;

	while(twiMasterIsBusy())
		;	// Wait until TWI is ready for next transmission.

	twiBufferData[0] = (deviceAddress << 1) |  readWrite;
	twiBufferSize = messageSize + 1;
	if(readWrite == TWI_MASTER_WRITE){
		for(i = 0;i < messageSize;i++)
			twiBufferData[i + 1] = message[i];
	}
	twiStatus.all = 0;
	twiState = TWI_NO_STATE;
	TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTA);
	if(readWrite == TWI_MASTER_READ){
		twiMasterReadFromBuffer(message, messageSize);
	}

	return;
}

/* -----------------------------------------------------------------------------
 * Function:	twiMasterResendData
 * Purpose:		Resends the data of the buffer to the slave device
 * Arguments:	none
 * Returns:		none
 * -------------------------------------------------------------------------- */

void twiMasterResendData(void)
{
	while(twiMasterIsBusy())
		;	// Wait until TWI is ready for next transmission
	twiStatus.all = 0;
	twiState = TWI_NO_STATE;
	TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTA);

	return;
}

/* -----------------------------------------------------------------------------
 * Function:	twiMasterErrorHandler
 * Purpose:		Returns the state of the last transmission and resends the
 * 				message if necessary
 * Arguments:	none
 * Returns:		twiState_t		error flags
 * -------------------------------------------------------------------------- */

twiState_t twiMasterErrorHandler(twiState_t twiErrorCode)
{
	if((twiErrorCode == TWI_MTX_ADR_NACK) || (twiErrorCode == TWI_MRX_ADR_NACK))
		twiMasterResendData();
	return twiErrorCode;
}

// -----------------------------------------------------------------------------
// Interruption handlers -------------------------------------------------------

/* -----------------------------------------------------------------------------
 * Handler:		TWI_vect
 * Purpose:		Manages the TWI interruption
 * -------------------------------------------------------------------------- */

ISR(TWI_vect)
{
	static uint8 twiBufferPointer;

	switch(TWSR & 0xFC){
	case TWI_START:			// START has been transmitted
	case TWI_REP_START:		// Repeated START has been transmitted
		twiBufferPointer = 0;	// Set buffer pointer to the TWI Address location
	case TWI_MTX_ADR_ACK:		// SLA+W has been transmitted and ACK received
	case TWI_MTX_DATA_ACK:		// Data byte has been transmitted and ACK received
		if(twiBufferPointer < twiBufferSize){
			TWDR = twiBufferData[twiBufferPointer++];
			TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
		}else{			// Send STOP after last byte
			twiStatus.lastTransOK = TRUE;	// Set status bits to completed successfully
			TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
		}
		break;
	case TWI_MRX_DATA_ACK:		// Data byte has been received and ACK transmitted
		twiBufferData[twiBufferPointer++] = TWDR;
	case TWI_MRX_ADR_ACK:		// SLA+R has been transmitted and ACK received
		if(twiBufferPointer < (twiBufferSize - 1))	// Detect the last byte to NACK it
			TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
		else					// Send NACK after next reception
			TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
		break;
	case TWI_MRX_DATA_NACK:		// Data byte has been received and NACK transmitted
		twiBufferData[twiBufferPointer] = TWDR;
		twiStatus.lastTransOK = TRUE;	// Set status bits to completed successfully
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
		break;
	case TWI_ARB_LOST:			// Arbitration lost
		TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTA);
		break;
	case TWI_MTX_ADR_NACK:		// SLA+W has been transmitted and NACK received
	case TWI_MRX_ADR_NACK:		// SLA+R has been transmitted and NACK received    
	case TWI_MTX_DATA_NACK:		// Data byte has been transmitted and NACK received
	case TWI_BUS_ERROR:			// Bus error due to an illegal START or STOP condition
	default:
		twiState = TWSR;		// Store TWSR and automatically sets clears noErrors bit
		TWCR = (1 << TWEN);		// Reset TWI Interface
		break;
	}
}
