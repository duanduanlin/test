/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
// void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOB
#define MCP2515_CS_Pin GPIO_PIN_8
#define MCP2515_CS_GPIO_Port GPIOH
#define BRAKE_LIMIT_Pin GPIO_PIN_3
#define BRAKE_LIMIT_GPIO_Port GPIOF
#define TURN_LEFT_LIMIT_Pin GPIO_PIN_2
#define TURN_LEFT_LIMIT_GPIO_Port GPIOF
#define TURN_RIGHT_LIMIT_Pin GPIO_PIN_4
#define TURN_RIGHT_LIMIT_GPIO_Port GPIOF
#define IMU_CS_Pin GPIO_PIN_13
#define IMU_CS_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOG
#define LED_BLUE_Pin GPIO_PIN_6
#define LED_BLUE_GPIO_Port GPIOG
#define SD_POWER_ON_Pin GPIO_PIN_0
#define SD_POWER_ON_GPIO_Port GPIOI
#define SDMMC_SD_Pin GPIO_PIN_4
#define SDMMC_SD_GPIO_Port GPIOD
#define ETH_RESET_Pin GPIO_PIN_15
#define ETH_RESET_GPIO_Port GPIOG
#define GPIO_NSLP_Pin GPIO_PIN_12
#define GPIO_NSLP_GPIO_Port GPIOH
#define GPIO_OPEN_LIGHT_Pin  GPIO_PIN_3
#define GPIO_OPEN_LIGHT_GPIO_Port GPIOD
#define OPEN_SW1_4_Pin  GPIO_PIN_11
#define OPEN_SW1_4_GPIO_Port GPIOI
#define OPEN_Ultrasonic_Pin   GPIO_PIN_3
#define OPEN_Ultrasonic_GPIO_Port GPIOH
#define SPI2_NSS_1_Pin  GPIO_PIN_4
#define SPI2_NSS_1_GPIO_Port      GPIOH
#define SPI2_NSS_2_Pin  GPIO_PIN_5
#define SPI2_NSS_2_GPIO_Port      GPIOH

/* USER CODE BEGIN Private defines */
#define __DEBUG__

#ifdef __DEBUG__
    #define DEBUG(format,...) printf("%s:"format"",__func__, ##__VA_ARGS__)
#else
    #define DEBUG(format,...)
#endif

#define LOG(format,...) printf(""format"", ##__VA_ARGS__)

#define ERROR(format,...) printf("ERROR:%s %s %d: "format"",__FILE__, __func__,__LINE__, ##__VA_ARGS__)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
