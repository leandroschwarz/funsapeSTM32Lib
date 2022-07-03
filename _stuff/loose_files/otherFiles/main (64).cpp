/* =============================================================================
 * Project:			STM32_2
 * File name:		main.cpp
 * Module:			Main source code file
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Module
// =============================================================================
// 	ADC power chain
// 		-
// 	ADC ECG channels
// 		-
// 	ECG + RESP
// 		-
// 	MPU9250
// 		-
// 	MAX30102
// 		-
// 	SD Card
// 		-
// 	TFT Display
// 		-
// =============================================================================

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// STM32CubeMx and HAL library header files ------------------------------------

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"

// -----------------------------------------------------------------------------
// FunSAPE Library header files ------------------------------------------------

#include "myMain.hpp"
#include "funsapeLibGlobalDefines.hpp"
#include "funsapeLibCircularBuffer.hpp"
#include "funsapeLibDebug.hpp"
#include "funsapeLibGpio.hpp"
#include "funsapeLibTm1637.hpp"

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

//     /////////////////////    ERROR AND DEBUG     /////////////////////     //
Gpio						debug1(DEBUG1_GPIO_Port, DEBUG1_Pin);
Gpio						debug2(DEBUG2_GPIO_Port, DEBUG2_Pin);
Gpio						debug3(DEBUG3_GPIO_Port, DEBUG3_Pin);
Gpio						debug4(DEBUG4_GPIO_Port, DEBUG4_Pin);
Gpio						debug5(DEBUG5_GPIO_Port, DEBUG5_Pin);
Gpio						debug6(DEBUG6_GPIO_Port, DEBUG6_Pin);
Gpio						debug7(DEBUG7_GPIO_Port, DEBUG7_Pin);
Gpio						debug8(DEBUG8_GPIO_Port, DEBUG8_Pin);
Error						funsapeStatus;
HAL_StatusTypeDef			halStatus;
Gpio						led(NLED_GPIO_Port, NLED_Pin);
systemFlags_f				systemFlags;


uint8_t errorAnimationState = 0x01;

//     /////////////////     PERIPHERAL BUS HANDLER     /////////////////     //
// Spi							spi1;
// Spi							spi2;
// Twi							twi1;
// Twi							twi2;

//     ////////////////////////     ADC DATA     ////////////////////////     //
CircularBuffer<uint16_t>	adc1CircBuffer(adc1CircBuffSize, true);
uint16_t					adc1DmaBuffer[adc1DmaBuffSizeFull];
uint16_t					adc3DmaBuffer[adc3DmaBuffSizeFull];
CircularBuffer<char>			uart3RxCircBuffer(20, true);
uint8_t							uart3RxDmaBuffer[uart3RxBuffSize];
char							uart3TxBuffer[uart3TxBuffSize];

Gpio displayClk(TFT_DATA0_GPIO_Port, TFT_DATA0_Pin);
Gpio displayData(TFT_DATA1_GPIO_Port, TFT_DATA1_Pin);
Tm1637 display(&displayData, &displayClk);

// =============================================================================
// Import external variables
// =============================================================================

// extern __IO uint32_t					uwTick;
// extern HAL_TickFreqTypeDef				uwTickFreq;

// =============================================================================
// File exclusive - Inline function definitions
// =============================================================================

// NONE

// =============================================================================
// Function declarations
// =============================================================================

// NONE

void delayUs(uint16_t delay_p)
{
	uint16_t mark = delay_p * 3;

	htim1.Instance->CNT = 0;
	while(htim1.Instance->CNT < mark);
}

// =============================================================================
// Main function
// =============================================================================

int main(void)
{
	//     ////////////////////     SYSTEM FLAGS    /////////////////////     //
	systemFlags.allFlags = 0;

	//     ///////////////////     INITIALIZATION    ////////////////////     //
	setupHal();
	setupDebug();
	setupUart3();
	setupUart2();
	setupAdc1();
	setupAdc3();
	setupTimer1();
	setupTimer3();
	setupTimer8();
	// setupTwi1();
	// setupTwi2();
	// setupSpi1();
	// setupSpi2();
	// setupUart1();

	// =========================================================================
	// Main loop - Start
	// =========================================================================




	HAL_TIM_Base_Start(&htim1);
	delayMs(2000);
	display.writeDisplayData(0x00, 1, false);
	display.writeDisplayData(0x00, 2, false);
	display.writeDisplayData(0x00, 3, false);
	display.writeDisplayData(0x00, 4, false);
	display.setDisplayContrast(Tm1637::Constrast::PERCENT_26);
	display.showDisplay(true);
	uint8_t x = 0;

	while(1) {
		if(systemFlags.errorAnimationUpdate) {
			display.writeDisplayData(errorAnimationState, 4, false);
			errorAnimationState = (errorAnimationState == 0x20) ? 0x01 : errorAnimationState << 1;
			systemFlags.errorAnimationUpdate = false;
			x++;
		}
		if(x == 100) {
			myErrorHandler(0x13AF);
			x = 0;
		}

		/*
				uint16_t circBuffFree = adc1CircBuffer.getFreeSpace();
				uint16_t circBuffOccupation = adc1CircBuffer.getOccupation();

				if(circBuffOccupation > 12) {
					uint16_t aux16Buff[12];
					adc1CircBuffer.popBuffer(aux16Buff, 12);
					// strcpy(uart3TxBuffer, "");
					// sprintf(uart3TxBuffer, "%u,%u,%u\r%u,%u,%u\r%u,%u,%u\r%u,%u,%u\r\n",
					// 		aux16Buff[0], aux16Buff[1], aux16Buff[2],
					// 		aux16Buff[3], aux16Buff[4], aux16Buff[5],
					// 		aux16Buff[6], aux16Buff[7], aux16Buff[8],
					// 		aux16Buff[9], aux16Buff[10], aux16Buff[11]
					// );
					// HAL_UART_Transmit(&huart3, (uint8_t *)uart3TxBuffer, strlen(uart3TxBuffer), uart2Timeout);
					HAL_UART_Transmit(&huart3, (uint8_t *)aux16Buff, 24, uart2Timeout);
				}

		*/

		// ---------------------------------------------------------------------
		// Process the events --------------------------------------------------

		// //     ////////////    ROTARY ENCODER - ROTATION     ////////////     //
		// if(systemFlags.encoderValueUpdated) {
		// 	processEventEncoderRotation();

		// 	// Clearing flag before leave
		// 	systemFlags.encoderValueUpdated = false;
		// }

		// //     //////////    ROTARY ENCODER - BUTTON PRESS     //////////     //
		// if(systemFlags.encoderButtonPressed) {
		// 	processEventEncoderButtonPress();

		// 	// Clearing flag before leave
		// 	systemFlags.encoderButtonPressed = false;
		// }

		// //     /////////////    SYSTEM VOLTAGES UPDATED     /////////////     //
		// if(systemFlags.systemVoltagesUpdated) {
		// 	processEventSystemVoltagesUpdated();

		// 	// Clearing flag before leave
		// 	systemFlags.systemVoltagesUpdated = false;
		// }

		// //     /////////////    ACQUISITION - START NEW     /////////////     //
		// if(systemFlags.acquisitionStartNew) {
		// 	processEventAcquisitionStartNew();

		// 	// Clearing flag before leave
		// 	systemFlags.acquisitionStartNew = false;
		// }

		// //     //////////////     SD CARD - WRITE DATA     //////////////     //
		// if(systemFlags.acquisitionRunning && (sdCardCircBuffer.getOccupation() >= SD_CARD_BUFF_SIZE)) {
		// 	processEventSdCardWriteData();

		// 	// No flag to clear (just leave)
		// }

		// //     //////////////////////////////////////////////////////////     //
		// //     //////////////////     TESTING CODE     //////////////////     //
		// //     //////////////////////////////////////////////////////////     //
		// if(timer1s.isTimedOut()) {
		// 	char auxString[1000];

		// 	sprintf(auxString, "%u\r", sdCardCircBuffer.getOccupation());
		// 	HAL_UART_Transmit(&huart3, (uint8_t *)auxString, strlen(auxString), uart3TimeoutUART3_TIMEOUT);
		// 	ledToggle();
		// }

	} // End of main loop

	return 0;
}

// =============================================================================
// Interrupt callback function definitions
// =============================================================================

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);

// =============================================================================
// Function definitions
// =============================================================================

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_ADC
			| RCC_PERIPHCLK_USB;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
	if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
}

// =============================================================================
// Weak functions overriding
// =============================================================================

void HAL_IncTick(void)
{
	uwTick += uwTickFreq;
}
