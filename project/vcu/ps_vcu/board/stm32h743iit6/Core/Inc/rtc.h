/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
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
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
/**
 * @brief 设置时间
 *
 * @param time
 * @param date
 */
void MX_RTC_SetTime(RTC_TimeTypeDef time,RTC_DateTypeDef date);
/**
 * @brief 获取格式化时间戳
 *
 * @param buff
 * @param len
 * @return int
 */
int RTC_GetTimestampsStr(char *buff, int len);

/**
 * @brief 获取时间�?
 *
 * @return long
 */
long RTC_GetTimestamps(void);

int RTC_IsTimeSet(void);

int RTC_GetWeekDay(uint16_t year, uint8_t month, uint8_t day);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

