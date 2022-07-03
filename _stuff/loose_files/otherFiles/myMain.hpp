
#ifndef __MY_MAIN_HPP
#define __MY_MAIN_HPP

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// STM32CubeMx and HAL library header files ------------------------------------

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"

// -----------------------------------------------------------------------------
// FunSAPE Library header files ------------------------------------------------

#include "funsapeLibGlobalDefines.hpp"
#include "funsapeLibCircularBuffer.hpp"
#include "funsapeLibDebug.hpp"
#include "funsapeLibGpio.hpp"
#include "funsapeLibTm1637.hpp"

// -----------------------------------------------------------------------------
// FatFs Library header files --------------------------------------------------

// #include "ff.h"

// =============================================================================
// Constant definitions
// =============================================================================

// -----------------------------------------------------------------------------
// System DEBUG related constants ----------------------------------------------

static cuint8_t debugTriggerPulseDelay = 10;

// -----------------------------------------------------------------------------
// ADC1 related constants -------------------------------------------------------

static cuint16_t adc1BytesPerChannel	= 2;	// Bytes per channel
static cuint16_t adc1ChannelsPerSample	= 3;	// Number of channels per sample
static cuint16_t adc1SamplesPerBuffer	= 8;	// Number of samples per buffer (must be even)
static cuint16_t adc1ChannelsPerBuffer	= (adc1ChannelsPerSample *adc1SamplesPerBuffer);
static cuint16_t adc1DmaBuffSizeFull	= adc1ChannelsPerBuffer;
static cuint16_t adc1DmaBuffSizeHalf	= (adc1DmaBuffSizeFull / 2);
static cuint16_t adc1CircBuffSize		= 300;	// Half word (uint16_t) elements

// -----------------------------------------------------------------------------
// ADC3 related constants -------------------------------------------------------

static cuint16_t adc3BytesPerChannel	= 2;	// Bytes per channel
static cuint16_t adc3ChannelsPerSample	= 3;	// Number of channels per sample
static cuint16_t adc3SamplesPerBuffer	= 2;	// Number of samples per buffer (must be even)
static cuint16_t adc3ChannelsPerBuffer	= (adc3ChannelsPerSample *adc3SamplesPerBuffer);
static cuint16_t adc3DmaBuffSizeFull	= adc3ChannelsPerBuffer;
static cuint16_t adc3DmaBuffSizeHalf	= (adc3DmaBuffSizeFull / 2);

// -----------------------------------------------------------------------------
// Timeouts / debounce times ---------------------------------------------------

static cuint8_t twi1Timeout				= 10;	// Value in miliseconds
static cuint8_t twi2Timeout				= 10;	// Value in miliseconds
static cuint8_t spi1Timeout				= 10;	// Value in miliseconds
static cuint8_t spi2Timeout				= 10;	// Value in miliseconds
static cuint8_t uart1Timeout			= 10;	// Value in miliseconds
static cuint8_t uart2Timeout			= 10;	// Value in miliseconds
static cuint8_t uart3Timeout			= 10;	// Value in miliseconds
static cuint8_t encoderButtonDebounce	= 50;	// Value in miliseconds
static cuint8_t encoderClockDebounce	= 50;	// Value in miliseconds

// -----------------------------------------------------------------------------
// Peripheral buffer sizes -----------------------------------------------------

static cuint8_t uart3RxBuffSize			= 2;	// DMA (2)
static cuint16_t uart3TxBuffSize		= 100;	// BLOCKING (100)
// static cuint8_t twi1BuffSize			= 8;	// EEPROM (X), RTC (8), PPG (6)
// static cuint8_t twi2BuffSize			= 6;	// RESP (6)
// static cuint8_t spi1BuffSize			= 6;	// MPU (6)
// static cuint16_t spi2BuffSize			= 512;	// SD (512)
// static cuint8_t uart1RxBuffSize			= 10;
// static cuint16_t uart1TxBuffSize		= 10;
// static cuint8_t uart2RxBuffSize			= 10;
// static cuint16_t uart2TxBuffSize		= 10;
// static cuint8_t usbRxBuffSize			= 2;	// DMA (2)
// static cuint16_t usbTxBuffSize			= 100;	// BLOCKING (100)

// -----------------------------------------------------------------------------
// System voltages related constants -------------------------------------------

// static cuint16_t powerMainResistorTop			= 12;	// Value in kiloohms
// static cuint16_t powerMainResistorBottom		= 33;	// Value in kiloohms
// static cuint16_t powerStepUpResistorTop			= 18;	// Value in kiloohms
// static cuint16_t powerStepUpResistorBottom		= 15;	// Value in kiloohms

// -----------------------------------------------------------------------------
// SD Card related constants ---------------------------------------------------

// static cuint16_t sdCardCircBuffSize		= 2048;
// static cuint16_t sdCardBuffSize			= spi2BuffSize;

// =============================================================================
// New data types
// =============================================================================

// -----------------------------------------------------------------------------
// System control and status flags ---------------------------------------------

typedef union {
	uint32_t allFlags;
	struct {
		// Interrupt management
		// bool		systemVoltagesUpdated		: 1;

		// Acquisition control
		// bool		acquisitionStartNew			: 1;
		// bool		acquisitionRunning			: 1;
		// bool		acquisitionStopping			: 1;

		// Encoder control
		// bool		encoderValueUpdated			: 1;
		// bool		encoderButtonPressed		: 1;

		// Error control
		bool		errorAnimationUpdate		: 1;
		// bool		encoderButtonPressed		: 1;

		// Free to use
		uint32_t	unusedFlags					: 26;
	};
} systemFlags_f;

// -----------------------------------------------------------------------------
// System voltages -------------------------------------------------------------

// typedef struct {
// 	uint16_t	rtcBattery;
// 	uint16_t	mainBattery;
// 	uint16_t	stepUpConverter;
// } systemVoltages_t;

// -----------------------------------------------------------------------------
// Rotary encoder --------------------------------------------------------------

// typedef struct {
// 	uint32_t	ticksSinceLastEdge;
// 	uint32_t	ticksSinceLastPress;
// 	int16_t		value					: 14;
// 	Rotation	rotation;
// } encoderData_s;

// -----------------------------------------------------------------------------
// SD Card ---------------------------------------------------------------------

// typedef struct {
// 	FATFS		disk;
// 	bool		diskIsMounted;
// 	FIL			fileHandler;
// 	bool		fileIsOpenned;
// 	char		fileName[13];
// 	uint16_t	fileNumber				: 14;
// 	FRESULT		result;
// } sdCard_s;

// =============================================================================
// Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

//     /////////////////////    ERROR AND DEBUG     /////////////////////     //
extern Gpio debug1;
extern Gpio debug2;
extern Gpio debug3;
extern Gpio debug4;
extern Gpio debug5;
extern Gpio debug6;
extern Gpio debug7;
extern Gpio debug8;
extern Gpio led;
extern systemFlags_f systemFlags;
extern Error funsapeStatus;
extern HAL_StatusTypeDef halStatus;
extern Tm1637 display;

//     /////////////////     PERIPHERAL BUS HANDLER     /////////////////     //
// extern Spi spi1;
// extern Spi spi2;
// extern Twi twi1;
// extern Twi twi2;

//     ////////////////////////     ADC DATA     ////////////////////////     //
extern CircularBuffer<uint16_t> adc1CircBuffer;
extern uint16_t adc1DmaBuffer[adc1DmaBuffSizeFull];
extern uint16_t adc3DmaBuffer[adc3DmaBuffSizeFull];

//     /////////////////////////    MPU9250     /////////////////////////     //
// extern Mpu9250 mpu1;
// extern Mpu9250 mpu2;
// extern Mpu9250 mpu3;
// extern Mpu9250 mpu4;

//     /////////////////////////    SD CARD     /////////////////////////     //
// sdCard_s						sdCard;
// CircularBuffer<uint8_t>			sdCardCircBuffer(sdCardCircBuffSize, true);

//     /////////////////////////    ENCODER     /////////////////////////     //
// encoderData_s					encoder;

//     //////////////////////////     UART     //////////////////////////     //
extern CircularBuffer<char> uart3RxCircBuffer;
extern uint8_t uart3RxDmaBuffer[uart3RxBuffSize];
extern char uart3TxBuffer[uart3TxBuffSize];

// =============================================================================
// File exclusive - Inline function definitions
// =============================================================================

// -----------------------------------------------------------------------------
// Debug trigger pulse ---------------------------------------------------------

inlined void debugTriggerPulse(void)
{
	debug8.low();
	delayMs(debugTriggerPulseDelay);
	debug8.high();
	delayMs(debugTriggerPulseDelay);
	debug8.low();

	return;
}

// =============================================================================
// Function declarations
// =============================================================================

void Error_Handler(void);						// HAL Library
void Error_Handler(uint16_t errorCode_p);
void processAdc1DmaData(bool isFirstBank_p);
void processAdc3DmaData(bool isFirstBank_p);
// void processEventAcquisitionStartNew(void);
// void processEventEncoderButtonPress(void);
// void processEventEncoderRotation(void);
// void processEventSdCardWriteData(void);
// void processEventSystemVoltagesUpdated(void);
void setupAdc1(void);
void setupAdc3(void);
void setupDebug(void);
void setupHal(void);
void setupTwi1(void);
void setupTwi2(void);
void setupSpi1(void);
void setupSpi2(void);
void setupTimer1(void);
void setupTimer3(void);
void setupTimer8(void);
void setupUart1(void);
void setupUart2(void);
void setupUart3(void);
void SystemClock_Config(void);					// HAL Library
void delayUs(uint16_t delay_p);

#endif
