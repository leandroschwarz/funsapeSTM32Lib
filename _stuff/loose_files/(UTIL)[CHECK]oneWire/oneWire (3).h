/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			oneWire.h
 * Module:			Dallas 1-Wire master interface
 * Authors:			Hazael dos Santos Batista
 *					Leandro Schwarz
 * Build:			1
 * Last edition:	March 18, 2018
 * Purpose:			Controls and interfaces a Dallas 1-Wire bus
 * -------------------------------------------------------------------------- */

#ifndef __ONE_WIRE_H
#define __ONE_WIRE_H 1

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBAL_DEFINES_H != 1
	#error Error 100 - globalDefines.h - wrong build (globalDefines must be build 1).
#endif

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

#define OWI_READ_ROM			0x33
#define OWI_SKIP_ROM			0xCC
#define OWI_MATCH_ROM			0x55
#define OWI_SEARCH_ROM			0xF0
//#define OWI_OVERDRIVE_SKIP_ROM	0x3C	// Not supported yet
//#define OWI_OVERDRIVE_MATCH_ROM	0x69	// Not supported yet

#define OWI_DELAY_A				6
#define OWI_DELAY_B				64
#define OWI_DELAY_C				60
#define OWI_DELAY_D				10
#define OWI_DELAY_E				9
#define OWI_DELAY_F				55
#define OWI_DELAY_G				0
#define OWI_DELAY_H				480
#define OWI_DELAY_I				70
#define OWI_DELAY_J				410

typedef struct owi_t {
    reg_t* ddrReg;
    reg_t* portReg;
    reg_t* pinReg;
    unsigned char pin;
    unsigned char mask;
    unsigned char lastDeviation;
} owi_t;

typedef union owiDevice_t {
    unsigned char address[8];
    struct {
        unsigned char family;
        unsigned char serial[6];
        unsigned char crc;
    };
} owiDevice_t;

void			owiPinConfigure(owi_t* ow, reg_t* ddrReg, reg_t* portReg, reg_t* pinReg, unsigned char pin);
unsigned char	owiDetectPresence(owi_t* ow);
unsigned char	owiReadBit(owi_t* ow);
void			owiSendByte(owi_t* ow, unsigned char data);
unsigned char	owiReceiveByte(owi_t* ow);
void			owiReadRom(owi_t* ow, owiDevice_t* device);
void			owiMatchRom(owi_t* ow, owiDevice_t* device);
unsigned char	owiSearchRom(owi_t *ow, owiDevice_t* device);

#endif