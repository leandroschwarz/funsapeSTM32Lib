/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibSpiBitBang.hpp
 * Module:			Bit Bang Spi Module for FunSAPE++ Embedded Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_SPI_BIT_BANG_HPP
#define __FUNSAPE_LIB_SPI_BIT_BANG_HPP			__BUILD_TO_REPLACE__

// =============================================================================
// System file dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "util/funsapeLibHandler.hpp"
#if __FUNSAPE_LIB_HANDLER_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibSpiBitBang.hpp] Error 103 - Required module (funsapeLibHandler.hpp) must be build __BUILD_TO_REPLACE__.
#endif

// -----------------------------------------------------------------------------
// Other header files ----------------------------------------------------------

// NONE

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

#define SPI2_SCLK_GPIO_Port				GPIOA
#define SPI2_SCLK_Pin					GPIO_PIN_8
#define SPI2_MISO_GPIO_Port				GPIOA
#define SPI2_MISO_Pin					GPIO_PIN_9
#define SPI2_MOSI_GPIO_Port				GPIOA
#define SPI2_MOSI_Pin					GPIO_PIN_10

// =============================================================================
// Macro-function definitions
// *INDENT-OFF*
// =============================================================================

#define SPI_BIT_BANG_SCLK_LOW()			HAL_GPIO_WritePin(SPI2_SCLK_GPIO_Port, SPI2_SCLK_Pin, GPIO_PIN_RESET)
#define SPI_BIT_BANG_SCLK_HIGH()		HAL_GPIO_WritePin(SPI2_SCLK_GPIO_Port, SPI2_SCLK_Pin, GPIO_PIN_SET)
#define SPI_BIT_BANG_MISO_STATE()		(bool)HAL_GPIO_ReadPin(SPI2_MISO_GPIO_Port, SPI2_MISO_Pin)
#define SPI_BIT_BANG_MOSI_LOW()			HAL_GPIO_WritePin(SPI2_MOSI_GPIO_Port, SPI2_MOSI_Pin, GPIO_PIN_RESET)
#define SPI_BIT_BANG_MOSI_HIGH()		HAL_GPIO_WritePin(SPI2_MOSI_GPIO_Port, SPI2_MOSI_Pin, GPIO_PIN_SET)
#define SPI_BIT_BANG_DELAY()			do{__ASM("NOP");}while(0)

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// -----------------------------------------------------------------------------
// Single variables ------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (logic values) -------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (small and finite lists) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (large or expansible lists) ------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (algebraic operated list elements) -----------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// SpiBitBang - Class declaration
// =============================================================================

class SpiBitBang : public Handler
{
	// -------------------------------------------------------------------------
	// New data types ----------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Operators overloading ---------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Constructors ------------------------------------------------------------

public:
	SpiBitBang(void);

	// -------------------------------------------------------------------------
	// Methods - Inherited public methods --------------------------------------
public:
	bool sendData(uint8_t *buffData, uint16_t buffSize = 1);
	bool sendData(uint8_t *txBuffData, uint8_t *rxBuffData, uint16_t buffSize = 1);
	bool setDevice(void (* actFunc)(void), void (* deactFunc)(void));
	bool sendData(uint8_t reg, uint8_t *txBuffData, uint8_t *rxBuffData, uint16_t buffSize = 1);
	bool sendData(uint8_t reg, uint8_t *buffData, uint16_t buffSize = 1);
	Handler::handlerType_e getHandlerType(void);

	// -------------------------------------------------------------------------
	// Methods - Inherited public methods --------------------------------------
public:

	bool init(bool setSlave = false);
	bool setClockPolarity(bool clkPolarity);
	// void spi_write_uint8(uint8_t x);
	// void spi_write_uint16(uint16_t x);
	// uint8_t spi_read_uint8(void);
	// void spi_read(uint8_t *s, uint8_t len);

private:
	bool	_transmitReceiveByte(void);
	bool	_configIos(void);

protected:
	// NONE

	// -------------------------------------------------------------------------
	// Properties  -------------------------------------------------------------

public:
	// NONE

private:
	bool	_clockPolarity				: 1;
	bool	_slave						: 1;
	uint8_t	_txByte;
	uint8_t	_rxByte;
	void	(* _activateDevice)(void);
	void	(* _deactivateDevice)(void);
protected:
	// NONE

};	// class SpiBitBang

// =============================================================================
// SpiBitBang - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

#endif	// __FUNSAPE_LIB_SPI_BIT_BANG_HPP
