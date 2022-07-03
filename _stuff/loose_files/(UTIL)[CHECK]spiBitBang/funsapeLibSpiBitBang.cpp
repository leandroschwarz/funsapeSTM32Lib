/* 
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibSpiBitBang.cpp
 * Module:			Bit Bang Spi Module for FunSAPE++ Embedded Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// 
// System file dependencies
// 

#include "funsapeLibSpiBitBang.hpp"
#if __FUNSAPE_LIB_SPI_BIT_BANG_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibSpiBitBang.cpp] Error 102 - Build mismatch on header and source code files.
#endif

// 
// File exclusive - Constants
// 

// NONE

// 
// File exclusive - New data types
// 

// NONE

// 
// File exclusive - Macro-functions
// 

// NONE

// 
// Global variables
// 

// NONE

// 
// Static functions declarations
// 

// NONE

// 
// Class constructors
// 

SpiBitBang::SpiBitBang(void)
{
	this->_clockPolarity	= false;
	this->_slave			= false;

	return;
}

// 
// Class public methods
// 

bool SpiBitBang::sendData(uint8_t *buffData, uint16_t buffSize)
{
	this->_activateDevice();
	for (uint8_t i = 0; i < buffSize; i++) {
		this->_txByte = buffData[i];
		this->_transmitReceiveByte();
		buffData[i] = this->_rxByte;
	}
	this->_deactivateDevice();

	return true;
}

bool SpiBitBang::sendData(uint8_t *txBuffData, uint8_t *rxBuffData, uint8_t buffSize)
{
	this->_activateDevice();
	for (uint8_t i = 0; i < buffSize; i++) {
		this->_txByte = txBuffData[i];
		this->_transmitReceiveByte();
		rxBuffData[i] = this->_rxByte;
	}
	this->_deactivateDevice();

	return true;
}

bool SpiBitBang::sendData(uint8_t reg, uint8_t *txBuffData, uint8_t *rxBuffData, uint8_t buffSize)
{
	this->_activateDevice();
	this->_txByte = reg;
	this->_transmitReceiveByte();
	for (uint8_t i = 0; i < buffSize; i++) {
		this->_txByte = txBuffData[i];
		this->_transmitReceiveByte();
		rxBuffData[i] = this->_rxByte;
	}
	this->_deactivateDevice();

	// Return successfully
	return true;
}

bool SpiBitBang::sendData(uint8_t reg, uint8_t *buffData, uint8_t buffSize)
{
	this->_activateDevice();
	this->_txByte = reg;
	this->_transmitReceiveByte();
	for (uint8_t i = 0; i < buffSize; i++) {
		this->_txByte = buffData[i];
		this->_transmitReceiveByte();
		buffData[i] = this->_rxByte;
	}

	return true;
	// Return successfully
	return true;
}

Handler::handlerType_e SpiBitBang::getHandlerType(void)
{
	return Handler::HANDLER_TYPE_SPI;
}

bool SpiBitBang::setDevice(void (* actFunc)(void), void (* deactFunc)(void))
{
	this->_activateDevice = actFunc;
	this->_deactivateDevice = deactFunc;

	return true;
}

bool SpiBitBang::init(bool setSlave)
{
	this->_slave = setSlave;
	this->_configIos();
	SPI_BIT_BANG_MOSI_HIGH();
	SPI_BIT_BANG_SCLK_HIGH();

	return true;
}

bool SpiBitBang::setClockPolarity(bool clkPolarity)
{
	this->_clockPolarity = clkPolarity;

	return true;
}

// 
// Class private methods
// 

bool SpiBitBang::_transmitReceiveByte(void)
{
	this->_rxByte = 0x00;

	for (uint8_t i = 0; i < 8; i++) {
		SPI_BIT_BANG_SCLK_LOW();
		(isBitSet(this->_txByte, (7 - i))) ? SPI_BIT_BANG_MOSI_HIGH() : SPI_BIT_BANG_MOSI_LOW();
		SPI_BIT_BANG_DELAY();
		SPI_BIT_BANG_SCLK_HIGH();
		(SPI_BIT_BANG_MISO_STATE()) ? setBit(this->_rxByte, (7 - i)) : clrBit(this->_rxByte, (7 - i));
		SPI_BIT_BANG_DELAY();
	}

	return true;
}

bool SpiBitBang::_configIos(void)
{
	GPIO_InitTypeDef gpioStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// SCLK
	gpioStruct.Pin = SPI2_SCLK_Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI2_SCLK_GPIO_Port, &gpioStruct);

	// MOSI
	gpioStruct.Pin = SPI2_MOSI_Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI2_MOSI_GPIO_Port, &gpioStruct);

	// MISO
	gpioStruct.Pin = SPI2_MISO_Pin;
	gpioStruct.Mode = GPIO_MODE_INPUT;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI2_MISO_GPIO_Port, &gpioStruct);

	return true;
}

// 
// Class protected methods
// 

// NONE

// 
// General public functions definitions
// 

// NONE

// 
// Public functions definitions
// 

// NONE
