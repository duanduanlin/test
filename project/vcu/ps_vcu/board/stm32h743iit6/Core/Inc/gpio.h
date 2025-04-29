/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef enum switch_on_off
{
    Switch_Off = 0x0,
    Switch_On = 0x1,
} Switch_OnOff;
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
/**
 * @brief set run led(Low effectiveness)
 *
 * @param onoff
 */
void GPIO_Set_LedRun(Switch_OnOff onoff);
/**
 * @brief set error led(Low effectiveness)
 *
 * @param onoff
 */
void GPIO_Set_LedError(Switch_OnOff onoff);

/**
 * @brief reboot
 *
 */
void GPIO_Set_ReBoot(void);

/**
 * @brief set tf-sd card power(high effectiveness)
 *
 * @param onoff
 */
void GPIO_Set_SDPower(Switch_OnOff onoff);

void GPIO_SetHSOut5(Switch_OnOff onoff);
void GPIO_SetHSOut6(Switch_OnOff onoff);
void GPIO_SetHSOut7(Switch_OnOff onoff);
void GPIO_SetHSOut8(Switch_OnOff onoff);
void GPIO_SetLSOut5(Switch_OnOff onoff);
void GPIO_SetLSOut6(Switch_OnOff onoff);
void GPIO_SetLSOut7(Switch_OnOff onoff);
void GPIO_SetLSOut8(Switch_OnOff onoff);
void GPIO_SetLSOut9(Switch_OnOff onoff);
void GPIO_SetLSOut10(Switch_OnOff onoff);

uint8_t GPIO_GetDioIn1(void);
uint8_t GPIO_GetDioIn2(void);
uint8_t GPIO_GetDioIn3(void);
uint8_t GPIO_GetDioIn4(void);
uint8_t GPIO_GetDioIn5(void);
uint8_t GPIO_GetDioIn6(void);
uint8_t GPIO_GetDioIn7(void);
uint8_t GPIO_GetDioIn8(void);
uint8_t GPIO_GetDioIn9(void);
uint8_t GPIO_GetDioIn10(void);

uint8_t GPIO_GetIDs(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

