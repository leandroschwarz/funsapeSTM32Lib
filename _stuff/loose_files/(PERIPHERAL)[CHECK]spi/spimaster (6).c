/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			spiMaster.c
 * Module:			Serial Peripheral Interface master controller
 * Author:			Leandro Schwarz
 *					Fabio Cabral Pacheco
 * Version:			2.0
 * Last edition:	2016-02-16
 * Purpose:			SPI bus controller using the dedicated peripheral (polled
 *					operation)
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "spiMaster.h"
#if __SPIMASTER_H != 20
#error Error 101 - Version mismatch on header and source code files (spiMaster).
#endif

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

spiStatus_t spiStatus;

// -----------------------------------------------------------------------------
// Public function definitions -------------------------------------------------

/* -----------------------------------------------------------------------------
 * Function:	spiMasterInit
 * Purpose:		Sets up the SPI module in master mode
 * Arguments:	none
 * Returns:		SPI_OK
 * Notes:		Since the controller operates in polling mode (software-driven),
 *				the it is suggested to use the minimum prescaler value possible
 *				in order to minimize the dead time until the end of the
 *				transmission
 * -------------------------------------------------------------------------- */

spiResult_t spiMasterInit(void)
{
    uint8 mask = 0;

    // Port configuration
    setBit(SPI_SCLK_DDR, SPI_SCLK_BIT);
    setBit(SPI_MOSI_DDR, SPI_MOSI_BIT);
    setBit(SPI_SS_DDR, SPI_SS_BIT);
    clrBit(SPI_MISO_DDR, SPI_MISO_BIT);

    // Master mode
    setBit(mask, MSTR);

    // SPI enable
    setBit(mask, SPE);

    // Popping register back
    setMaskOffset(SPCR, mask, 0);

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSetClockPrescaler
 * Purpose:		Sets up the SPI clock prescaler
 * Arguments:	prescaler	Value of the prescaler (defined at
 *							spiPrescalerValue_t)
 * Returns:		SPI_OK, SPI_CLOCK_PRESCALER_UNSUPPORTED
 * -------------------------------------------------------------------------- */

spiResult_t spiSetClockPrescaler(spiPrescalerValue_t prescaler)
{
    uint8 reg1 = SPCR;
    uint8 reg2 = SPSR;

    // Clearing registers
    clrMaskOffset(reg1, 0x03, SPR0);
    clrBit(reg2, SPI2X);

    // Prescaler configuration
    switch (prescaler) {
    case SPI_PRESCALER_2:	setBit(reg2, SPI2X);	break;
    case SPI_PRESCALER_4:	break;
    case SPI_PRESCALER_8:	setBit(reg2, SPI2X);	setMaskOffset(reg1, 0x01, SPR0);	break;
    case SPI_PRESCALER_16:	setMaskOffset(reg1, 0x01, SPR0);	break;
    case SPI_PRESCALER_32:	setBit(reg2, SPI2X);	setMaskOffset(reg1, 0x02, SPR0);	break;
    case SPI_PRESCALER_64:	setMaskOffset(reg1, 0x02, SPR0);	break;
    case SPI_PRESCALER_128:	setMaskOffset(reg1, 0x03, SPR0);	break;
    default: 				return	SPI_CLOCK_PRESCALER_UNSUPPORTED;
    }
    spiStatus.prescaler = prescaler;

    // Popping registers back
    SPCR = reg1;
    SPSR = reg2;

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSetClockPolarity
 * Purpose:		Sets up the polarity of the SPI clock
 * Arguments:	polarity	Polarity of the clock (defined in
 *							spiClockPolarity_t)
 * Returns:		SPI_OK, SPI_CLOCK_POLARITY_UNSUPPORTED
 * -------------------------------------------------------------------------- */

spiResult_t spiSetClockPolarity(spiClockPolarity_t polarity)
{
    if (polarity == SPI_POLARITY_IDLE_LOW) {
        clrBit(SPCR, CPOL);
    } else if (polarity == SPI_POLARITY_IDLE_HIGH) {
        setBit(SPCR, CPOL);
    } else {
        return SPI_CLOCK_POLARITY_UNSUPPORTED;
    }

    spiStatus.clockPolarity = polarity;

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSetClockPhase
 * Purpose:		Sets up the phase of the SPI clock
 * Arguments:	phase	Phase of the clock (defined in spiClockPhase_t)
 * Returns:		SPI_OK, SPI_CLOCK_PHASE_UNSUPPORTED
 * -------------------------------------------------------------------------- */

spiResult_t spiSetClockPhase(spiClockPhase_t phase)
{
    if (phase == SPI_SAMPLE_THEN_SETUP) {
        clrBit(SPCR, CPHA);
    } else if (phase == SPI_SETUP_THEN_SAMPLE) {
        setBit(SPCR, CPHA);
    } else {
        return SPI_CLOCK_PHASE_UNSUPPORTED;
    }

    spiStatus.clockPhase = phase;

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSetDataEndianness
 * Purpose:		Sets up the endianness of the data byte
 * Arguments:	endianness	Endianness of the data byte (defined in
 *							spiDataEndianness_t)
 * Returns:		SPI_OK, SPI_DATA_ENDIANNESS_UNSUPPORTED
 * -------------------------------------------------------------------------- */

spiResult_t	spiSetDataEndianness(spiDataEndianness_t endianness)
{
    if (endianness == SPI_DATA_MSB_FIRST) {
        clrBit(SPCR, DORD);
    } else if (endianness == SPI_DATA_LSB_FIRST) {
        setBit(SPCR, DORD);
    } else {
        return SPI_DATA_ENDIANNESS_UNSUPPORTED;
    }

    spiStatus.dataEndianness = endianness;

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSendReceiveByte
 * Purpose:		Sends one byte to the bus while receives another byte from bus
 * Arguments:	data	data byte to be sent to the bus
 * Returns:		one byte received during transmission
 * -------------------------------------------------------------------------- */

uint8 spiSendReceiveByte(uint8 data)
{
    SPDR = data;

    waitUntilBitIsSet(SPSR, SPIF);

    return SPDR;
}

/* -----------------------------------------------------------------------------
 * Function:	spiSendByte
 * Purpose:		Sends one byte to the bus ignoring the byte received
 * Arguments:	data	data byte to be sent to the bus
 * Returns:		SPI_OK
 * -------------------------------------------------------------------------- */

spiResult_t spiSendByte(uint8 data)
{
    spiSendReceiveByte(data);

    return SPI_OK;
}

/* -----------------------------------------------------------------------------
 * Function:	spiReceiveByte
 * Purpose:		Sends a dummy byte to the bus in order to receive one bute from
 *				the bus
 * Arguments:	none
 * Returns:		one byte received during transmission
 * -------------------------------------------------------------------------- */

uint8 spiReceiveByte(void)
{
    return spiSendReceiveByte(0xFF);
}
