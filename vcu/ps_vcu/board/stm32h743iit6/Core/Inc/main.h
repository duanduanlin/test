/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
void PWR_EnterStopMode(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LS_OUT_9_Pin GPIO_PIN_3
#define LS_OUT_9_GPIO_Port GPIOE
#define LS_OUT_10_Pin GPIO_PIN_4
#define LS_OUT_10_GPIO_Port GPIOE
#define LS_OUT_11_Pin GPIO_PIN_5
#define LS_OUT_11_GPIO_Port GPIOE
#define LS_OUT_12_Pin GPIO_PIN_6
#define LS_OUT_12_GPIO_Port GPIOE
#define WAKE_UP_1_Pin GPIO_PIN_8
#define WAKE_UP_1_GPIO_Port GPIOI
#define WAKE_UP_FB_1_Pin GPIO_PIN_9
#define WAKE_UP_FB_1_GPIO_Port GPIOI
#define WAKE_UP_FB_2_Pin GPIO_PIN_10
#define WAKE_UP_FB_2_GPIO_Port GPIOI
#define WAKE_UP_2_Pin GPIO_PIN_11
#define WAKE_UP_2_GPIO_Port GPIOI
#define ADC_DC12_Pin GPIO_PIN_0
#define ADC_DC12_GPIO_Port GPIOA
#define ADC_IN_1_Pin GPIO_PIN_1
#define ADC_IN_1_GPIO_Port GPIOA
#define ADC_IN_2_Pin GPIO_PIN_2
#define ADC_IN_2_GPIO_Port GPIOA
#define SLEEP_KEY_Pin GPIO_PIN_3
#define SLEEP_KEY_GPIO_Port GPIOH
#define ADC_IN_3_Pin GPIO_PIN_3
#define ADC_IN_3_GPIO_Port GPIOA
#define ADC_IN_4_Pin GPIO_PIN_4
#define ADC_IN_4_GPIO_Port GPIOA
#define ADC_IN_5_Pin GPIO_PIN_5
#define ADC_IN_5_GPIO_Port GPIOA
#define ADC_IN_6_Pin GPIO_PIN_6
#define ADC_IN_6_GPIO_Port GPIOA
#define ADC_IN_7_Pin GPIO_PIN_7
#define ADC_IN_7_GPIO_Port GPIOA
#define HS_OUT_5_Pin GPIO_PIN_4
#define HS_OUT_5_GPIO_Port GPIOC
#define HS_OUT_6_Pin GPIO_PIN_5
#define HS_OUT_6_GPIO_Port GPIOC
#define ADC_IN_8_Pin GPIO_PIN_0
#define ADC_IN_8_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOB
#define DIO_IN_1_Pin GPIO_PIN_0
#define DIO_IN_1_GPIO_Port GPIOG
#define DIO_IN_2_Pin GPIO_PIN_1
#define DIO_IN_2_GPIO_Port GPIOG
#define DIO_IN_3_Pin GPIO_PIN_7
#define DIO_IN_3_GPIO_Port GPIOE
#define DIO_IN_4_Pin GPIO_PIN_8
#define DIO_IN_4_GPIO_Port GPIOE
#define DIO_IN_5_Pin GPIO_PIN_9
#define DIO_IN_5_GPIO_Port GPIOE
#define DIO_IN_6_Pin GPIO_PIN_10
#define DIO_IN_6_GPIO_Port GPIOE
#define DIO_IN_7_Pin GPIO_PIN_11
#define DIO_IN_7_GPIO_Port GPIOE
#define DIO_IN_8_Pin GPIO_PIN_12
#define DIO_IN_8_GPIO_Port GPIOE
#define DIO_IN_9_Pin GPIO_PIN_13
#define DIO_IN_9_GPIO_Port GPIOE
#define DIO_IN_10_Pin GPIO_PIN_14
#define DIO_IN_10_GPIO_Port GPIOE
#define LIN_TX_Pin GPIO_PIN_10
#define LIN_TX_GPIO_Port GPIOB
#define LIN_RX_Pin GPIO_PIN_11
#define LIN_RX_GPIO_Port GPIOB
#define CCAN_RX_Pin GPIO_PIN_12
#define CCAN_RX_GPIO_Port GPIOB
#define CCAN_TX_Pin GPIO_PIN_13
#define CCAN_TX_GPIO_Port GPIOB
#define LIN_RESET_Pin GPIO_PIN_14
#define LIN_RESET_GPIO_Port GPIOB
#define LS_OUT_4_Pin GPIO_PIN_15
#define LS_OUT_4_GPIO_Port GPIOB
#define LS_OUT_6_Pin GPIO_PIN_8
#define LS_OUT_6_GPIO_Port GPIOD
#define LS_OUT_7_Pin GPIO_PIN_9
#define LS_OUT_7_GPIO_Port GPIOD
#define LS_OUT_8_Pin GPIO_PIN_10
#define LS_OUT_8_GPIO_Port GPIOD
#define LIN_SLEEP_Pin GPIO_PIN_11
#define LIN_SLEEP_GPIO_Port GPIOD
#define LED_ERROR_Pin GPIO_PIN_5
#define LED_ERROR_GPIO_Port GPIOG
#define LED_RUN_Pin GPIO_PIN_6
#define LED_RUN_GPIO_Port GPIOG
#define RESET_Pin GPIO_PIN_7
#define RESET_GPIO_Port GPIOG
#define LOG_TX_Pin GPIO_PIN_9
#define LOG_TX_GPIO_Port GPIOA
#define LOG_RX_Pin GPIO_PIN_10
#define LOG_RX_GPIO_Port GPIOA
#define ACAN_TX_Pin GPIO_PIN_13
#define ACAN_TX_GPIO_Port GPIOH
#define ACAN_RX_Pin GPIO_PIN_14
#define ACAN_RX_GPIO_Port GPIOH
#define IMU_INT2_Pin GPIO_PIN_15
#define IMU_INT2_GPIO_Port GPIOA
#define IMU_INT1_Pin GPIO_PIN_0
#define IMU_INT1_GPIO_Port GPIOD
#define SDIO0_CD_Pin GPIO_PIN_1
#define SDIO0_CD_GPIO_Port GPIOD
#define HS_OUT_7_Pin GPIO_PIN_3
#define HS_OUT_7_GPIO_Port GPIOD
#define HS_OUT_8_Pin GPIO_PIN_4
#define HS_OUT_8_GPIO_Port GPIOD
#define LS_OUT_5_Pin GPIO_PIN_7
#define LS_OUT_5_GPIO_Port GPIOD
#define ID_5_Pin GPIO_PIN_9
#define ID_5_GPIO_Port GPIOG
#define ID_4_Pin GPIO_PIN_10
#define ID_4_GPIO_Port GPIOG
#define ID_3_Pin GPIO_PIN_11
#define ID_3_GPIO_Port GPIOG
#define ID_2_Pin GPIO_PIN_12
#define ID_2_GPIO_Port GPIOG
#define ID_1_Pin GPIO_PIN_13
#define ID_1_GPIO_Port GPIOG
#define ID_0_Pin GPIO_PIN_14
#define ID_0_GPIO_Port GPIOG
#define HS_OUT_1_Pin GPIO_PIN_3
#define HS_OUT_1_GPIO_Port GPIOB
#define HS_OUT_2_Pin GPIO_PIN_4
#define HS_OUT_2_GPIO_Port GPIOB
#define HS_OUT_3_Pin GPIO_PIN_5
#define HS_OUT_3_GPIO_Port GPIOB
#define HS_OUT_4_Pin GPIO_PIN_6
#define HS_OUT_4_GPIO_Port GPIOB
#define LS_OUT_1_Pin GPIO_PIN_7
#define LS_OUT_1_GPIO_Port GPIOB
#define LS_OUT_2_Pin GPIO_PIN_8
#define LS_OUT_2_GPIO_Port GPIOB
#define LS_OUT_3_Pin GPIO_PIN_9
#define LS_OUT_3_GPIO_Port GPIOB
#define SD_PWR_ON_Pin GPIO_PIN_5
#define SD_PWR_ON_GPIO_Port GPIOI
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
