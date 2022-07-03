/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NLED_Pin GPIO_PIN_13
#define NLED_GPIO_Port GPIOC
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define DEBUG0_Pin GPIO_PIN_12
#define DEBUG0_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_11
#define SPI2_CS_GPIO_Port GPIOA
#define DEBUG1_Pin GPIO_PIN_15
#define DEBUG1_GPIO_Port GPIOA
#define DEBUG2_Pin GPIO_PIN_3
#define DEBUG2_GPIO_Port GPIOB
#define DEBUG3_Pin GPIO_PIN_4
#define DEBUG3_GPIO_Port GPIOB
#define DEBUG4_Pin GPIO_PIN_5
#define DEBUG4_GPIO_Port GPIOB
#define DEBUG5_Pin GPIO_PIN_8
#define DEBUG5_GPIO_Port GPIOB
#define DEBUG6_Pin GPIO_PIN_9
#define DEBUG6_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
