/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			l3g4200dTwi.c
 * Module:			L3G4200D - 3-Axis Digital Gyroscope in Two Wire Interface
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Build:			1
 * Last edition:	October 26, 2017
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "l3g4200dTwi.h"
#if __L3G4200DTWI_H != 1
	#error Error 101 - Build mismatch on header and source code files (l3g4200dTwi).
#endif

// -----------------------------------------------------------------------------
// Private function declarations -----------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

l3g4200dConfiguration_t l3g4200dConfiguration;

// -----------------------------------------------------------------------------
// Private functions -----------------------------------------------------------

/* NONE */

// -----------------------------------------------------------------------------
// Public functions ------------------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	l3g4200dInit
 * Purpose:		Initializes the l3g4200d in TWI communication
 * Arguments:	twiAddress		l3g4200dTwiAddress_t enumeration
 * Returns:		TRUE / FALSE
 * Notes:		The TWI module must be configured before calling this function
 * -------------------------------------------------------------------------- */

bool_t l3g4200dInit(l3g4200dTwiAddress_t twiAddress)
{
	uint8 data[2];

	// Select between addresses
	if(twiAddress == L3G4200D_ADDRESS_0x68){
		l3g4200dConfiguration.deviceAddress = 0x68;
	}else{
		l3g4200dConfiguration.deviceAddress = 0x69;
	}

	// Look for L3G4200D
	data[0] = L3G4200D_WHO_AM_I;
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_WRITE, data, 1);
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_READ, data, 1);
	if(data[0] != L3G4200D_WHO_AM_I_VALUE){
		return FALSE;
	}

	// Enables all angles and sets normal mode
	data[0] = L3G4200D_CTRL_REG1;
	data[1] = 0x0F;		// PD, Zen, Yen, Xen
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_WRITE, data, 2);

	return TRUE;
}

void l3g4200dDataGet(int16 * xValue, int16 * yValue, int16 * zValue, l3g4200dDataStatusFlags_t * dataStatus)
{
	uint8 data[6];

	// Read status register
	*dataStatus = 0;
	data[0] = L3G4200D_STATUS_REG;
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_WRITE, data, 1);
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_READ, data, 1);
	if(isBitSet(data[0], 3)){
		*dataStatus += L3G4200D_NEW_DATA;
	}
	if(isBitSet(data[0], 7)){
		*dataStatus += L3G4200D_DATA_LOST;
	}
	data[0] = L3G4200D_OUT_X_L | L3G4200D_AUTO_INCREMENT;
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_WRITE, data, 1);
	twiMasterSendData(l3g4200dConfiguration.deviceAddress, TWI_MASTER_READ, data, 6);
	*xValue = data[1];
	*xValue <<= 8;
	*xValue |= data[0];
	*yValue = data[3];
	*yValue <<= 8;
	*yValue |= data[2];
	*zValue = data[5];
	*zValue <<= 8;
	*zValue |= data[4];

	return;
}
