/**
  ******************************************************************************
  * @file    sdmmc.c
  * @brief   This file provides code for the configuration
  *          of the SDMMC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sdmmc.h"
SD_HandleTypeDef hsd1;
/* USER CODE BEGIN 0 */
#define STD_CAPACITY_SD_CARD_V1_1             ((uint32_t)0x00000000U)
#define STD_CAPACITY_SD_CARD_V2_0             ((uint32_t)0x00000001U)
#define HIGH_CAPACITY_SD_CARD                 ((uint32_t)0x00000002U)
#define MULTIMEDIA_CARD                       ((uint32_t)0x00000003U)
#define SECURE_DIGITAL_IO_CARD                ((uint32_t)0x00000004U)
#define HIGH_SPEED_MULTIMEDIA_CARD            ((uint32_t)0x00000005U)
#define SECURE_DIGITAL_IO_COMBO_CARD          ((uint32_t)0x00000006U)
#define HIGH_CAPACITY_MMC_CARD                ((uint32_t)0x00000007U)
void print_sdcard_info(HAL_SD_CardInfoTypeDef sd_info)
{
	switch(sd_info.CardType)
	{
		case STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
// 	printf("Card RelCardAdd:%d\r\n",sd_info.RelCardAdd);								//¿¨Ïà¶ÔµØÖ·
	printf("Card BlockNbr:%d \r\n",(uint32_t)(sd_info.BlockNbr));	//ÏÔÊ¾ÈÝÁ¿
 	printf("Card BlockSize:%d\r\n\r\n",sd_info.BlockSize);			//ÏÔÊ¾¿é´óÐ¡
  printf("Card CardSpeed:%04X\r\n\r\n",sd_info.CardSpeed);
//    printf("Card MB:%d MB\r\n\r\n", (uint32_t)(sd_info.BlockNbr>>11));
}

HAL_StatusTypeDef HAL_SD1_DeInit(){
  return HAL_SD_DeInit(&hsd1);
}
HAL_StatusTypeDef MX_SDMMC1_SD_Init(void)
{
    HAL_StatusTypeDef ret = HAL_OK;
  HAL_SD_DeInit(&hsd1);
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE;
  hsd1.Init.ClockDiv = 0;
  hsd1.Init.TranceiverPresent = SDMMC_TRANSCEIVER_NOT_PRESENT;
    ret = HAL_SD_Init(&hsd1);
  if (ret != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
      return ret;
  }
  HAL_SD_GetCardInfo(&hsd1, &hsd1.SdCard);
  print_sdcard_info(hsd1.SdCard);
  ret = HAL_SD_ConfigWideBusOperation(&hsd1, SDMMC_BUS_WIDE_4B);
  if ( ret != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
      return ret;
  }
    return ret;
}

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(sdHandle->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */

  /* USER CODE END SDMMC1_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.PLL2.PLL2M = 5;
    PeriphClkInitStruct.PLL2.PLL2N = 40;
    PeriphClkInitStruct.PLL2.PLL2P = 4;
    PeriphClkInitStruct.PLL2.PLL2Q = 4;
    PeriphClkInitStruct.PLL2.PLL2R = 4;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* SDMMC1 clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* SDMMC1 interrupt Init */
    HAL_NVIC_SetPriority(SDMMC1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
  /* USER CODE BEGIN SDMMC1_MspInit 1 */

  /* USER CODE END SDMMC1_MspInit 1 */
  }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle)
{

  if(sdHandle->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspDeInit 0 */

  /* USER CODE END SDMMC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC1_CLK_DISABLE();

    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* SDMMC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
  /* USER CODE BEGIN SDMMC1_MspDeInit 1 */

  /* USER CODE END SDMMC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
