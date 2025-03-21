/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PI8   ------> PWR_WKUP3
     PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
     PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
     PI11   ------> PWR_WKUP4
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LS_OUT_9_Pin|LS_OUT_10_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, WAKE_UP_FB_1_Pin|WAKE_UP_FB_2_Pin|SD_PWR_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, HS_OUT_5_Pin|HS_OUT_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LIN_RESET_GPIO_Port, LIN_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LS_OUT_6_Pin|LS_OUT_7_Pin|LS_OUT_8_Pin|LS_OUT_5_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LIN_SLEEP_Pin|HS_OUT_7_Pin|HS_OUT_8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LED_ERROR_Pin|LED_RUN_Pin|RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = LS_OUT_9_Pin|LS_OUT_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = WAKE_UP_FB_1_Pin|WAKE_UP_FB_2_Pin|SD_PWR_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SLEEP_KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SLEEP_KEY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = HS_OUT_5_Pin|HS_OUT_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin */
  GPIO_InitStruct.Pin = DIO_IN_1_Pin|DIO_IN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = DIO_IN_3_Pin|DIO_IN_4_Pin|DIO_IN_5_Pin|DIO_IN_7_Pin
                          |DIO_IN_8_Pin|DIO_IN_9_Pin|DIO_IN_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DIO_IN_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DIO_IN_6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LIN_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LIN_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = LS_OUT_6_Pin|LS_OUT_7_Pin|LS_OUT_8_Pin|LS_OUT_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = LIN_SLEEP_Pin|HS_OUT_7_Pin|HS_OUT_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = LED_ERROR_Pin|LED_RUN_Pin|RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IMU_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(IMU_INT2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = IMU_INT1_Pin|SDIO0_CD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin */
  GPIO_InitStruct.Pin = ID_5_Pin|ID_4_Pin|ID_3_Pin|ID_2_Pin
                          |ID_1_Pin|ID_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void GPIO_Set_LedRun(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_Set_LedError(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_Set_ReBoot(void)
{
    HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
}

void GPIO_Set_SDPower(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(SD_PWR_ON_GPIO_Port, SD_PWR_ON_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(SD_PWR_ON_GPIO_Port, SD_PWR_ON_Pin, GPIO_PIN_SET);
    }
}

void GPIO_SetHSOut5(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(HS_OUT_5_GPIO_Port, HS_OUT_5_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(HS_OUT_5_GPIO_Port, HS_OUT_5_Pin, GPIO_PIN_SET);
    }
}

void GPIO_SetHSOut6(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(HS_OUT_6_GPIO_Port, HS_OUT_6_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(HS_OUT_6_GPIO_Port, HS_OUT_6_Pin, GPIO_PIN_SET);
    }
}

void GPIO_SetHSOut7(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(HS_OUT_7_GPIO_Port, HS_OUT_7_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(HS_OUT_7_GPIO_Port, HS_OUT_7_Pin, GPIO_PIN_SET);
    }
}

void GPIO_SetHSOut8(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(HS_OUT_8_GPIO_Port, HS_OUT_8_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(HS_OUT_8_GPIO_Port, HS_OUT_8_Pin, GPIO_PIN_SET);
    }
}

void GPIO_SetLSOut5(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_5_GPIO_Port, LS_OUT_5_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_5_GPIO_Port, LS_OUT_5_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_SetLSOut6(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_6_GPIO_Port, LS_OUT_6_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_6_GPIO_Port, LS_OUT_6_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_SetLSOut7(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_7_GPIO_Port, LS_OUT_7_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_7_GPIO_Port, LS_OUT_7_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_SetLSOut8(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_8_GPIO_Port, LS_OUT_8_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_8_GPIO_Port, LS_OUT_8_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_SetLSOut9(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_9_GPIO_Port, LS_OUT_9_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_9_GPIO_Port, LS_OUT_9_Pin, GPIO_PIN_RESET);
    }
}

void GPIO_SetLSOut10(Switch_OnOff onoff)
{
    if(onoff == Switch_Off)
    {
        HAL_GPIO_WritePin(LS_OUT_10_GPIO_Port, LS_OUT_10_Pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(LS_OUT_10_GPIO_Port, LS_OUT_10_Pin, GPIO_PIN_RESET);
    }
}

uint8_t GPIO_GetDioIn1(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_1_GPIO_Port, DIO_IN_1_Pin);
}

uint8_t GPIO_GetDioIn2(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_2_GPIO_Port, DIO_IN_2_Pin);
}

uint8_t GPIO_GetDioIn3(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_3_GPIO_Port, DIO_IN_3_Pin);
}

uint8_t GPIO_GetDioIn4(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_4_GPIO_Port, DIO_IN_4_Pin);
}

uint8_t GPIO_GetDioIn5(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_5_GPIO_Port, DIO_IN_5_Pin);
}

uint8_t GPIO_GetDioIn6(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_6_GPIO_Port, DIO_IN_6_Pin);
}

uint8_t GPIO_GetDioIn7(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_7_GPIO_Port, DIO_IN_7_Pin);
}

uint8_t GPIO_GetDioIn8(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_8_GPIO_Port, DIO_IN_8_Pin);
}

uint8_t GPIO_GetDioIn9(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_9_GPIO_Port, DIO_IN_9_Pin);
}

uint8_t GPIO_GetDioIn10(void)
{
    return HAL_GPIO_ReadPin(DIO_IN_10_GPIO_Port, DIO_IN_10_Pin);
}

uint8_t GPIO_GetIDs(void)
{
    uint8_t id = 0;
    id |= HAL_GPIO_ReadPin(ID_0_GPIO_Port, ID_0_Pin)&0x1;
    id |= ((HAL_GPIO_ReadPin(ID_1_GPIO_Port, ID_1_Pin)&0x1)<<1);
    id |= ((HAL_GPIO_ReadPin(ID_2_GPIO_Port, ID_2_Pin)&0x1)<<2);
    id |= ((HAL_GPIO_ReadPin(ID_3_GPIO_Port, ID_3_Pin)&0x1)<<3);
    id |= ((HAL_GPIO_ReadPin(ID_4_GPIO_Port, ID_4_Pin)&0x1)<<4);
    id |= ((HAL_GPIO_ReadPin(ID_5_GPIO_Port, ID_5_Pin)&0x1)<<5);
	return id;
}
/* USER CODE END 2 */
