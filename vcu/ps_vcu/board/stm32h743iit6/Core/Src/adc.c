/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
#define ADC_DMA_BUF_SIZE        (50)

#define NUM_ENTRIES 151  // �?-30℃到120℃，�?151个温度点

float resistance_table[NUM_ENTRIES][2] = {
    {-30, 129.9167}, {-29, 122.7265}, {-28, 115.9880}, {-27, 109.6698}, {-26, 103.7428},
    {-25, 98.1801}, {-24, 92.9568}, {-23, 88.0498}, {-22, 83.4379}, {-21, 79.1013},
    {-20, 75.0217}, {-19, 71.1822}, {-18, 67.5670}, {-17, 64.1615}, {-16, 60.9521},
    {-15, 57.9264}, {-14, 55.0724}, {-13, 52.3794}, {-12, 49.8373}, {-11, 47.4365},
    {-10, 45.1683}, {-9, 43.0245}, {-8, 40.9975}, {-7, 39.0802}, {-6, 37.2659},
    {-5, 35.5484}, {-4, 33.9220}, {-3, 32.3812}, {-2, 30.9210}, {-1, 29.5366},
    {0, 28.2237}, {1, 26.9781}, {2, 25.7960}, {3, 24.6736}, {4, 23.6077},
    {5, 22.5949}, {6, 21.6325}, {7, 20.7174}, {8, 19.8472}, {9, 19.0193},
    {10, 18.2314}, {11, 17.4814}, {12, 16.7671}, {13, 16.0868}, {14, 15.4384},
    {15, 14.8205}, {16, 14.2313}, {17, 13.6694}, {18, 13.1332}, {19, 12.6216},
    {20, 12.1332}, {21, 11.6668}, {22, 11.2213}, {23, 10.7957}, {24, 10.3889},
    {25, 10.0000}, {26, 9.6281}, {27, 9.2724}, {28, 8.9321}, {29, 8.6064},
    {30, 8.2946}, {31, 7.9960}, {32, 7.7101}, {33, 7.4361}, {34, 7.1736},
    {35, 6.9219}, {36, 6.6806}, {37, 6.4492}, {38, 6.2273}, {39, 6.0143},
    {40, 5.8099}, {41, 5.6136}, {42, 5.4252}, {43, 5.2443}, {44, 5.0704},
    {45, 4.9034}, {46, 4.7429}, {47, 4.5885}, {48, 4.4401}, {49, 4.2974},
    {50, 4.1601}, {51, 4.0280}, {52, 3.9009}, {53, 3.7785}, {54, 3.6607},
    {55, 3.5473}, {56, 3.4380}, {57, 3.3327}, {58, 3.2312}, {59, 3.1335},
    {60, 3.0392}, {61, 2.9483}, {62, 2.8606}, {63, 2.7761}, {64, 2.6945},
    {65, 2.6158}, {66, 2.5398}, {67, 2.4665}, {68, 2.3957}, {69, 2.3273},
    {70, 2.2613}, {71, 2.1975}, {72, 2.1358}, {73, 2.0762}, {74, 2.0187},
    {75, 1.9630}, {76, 1.9092}, {77, 1.8571}, {78, 1.8067}, {79, 1.7580},
    {80, 1.7109}, {81, 1.6653}, {82, 1.6211}, {83, 1.5784}, {84, 1.5370},
    {85, 1.4969}, {86, 1.4581}, {87, 1.4205}, {88, 1.3840}, {89, 1.3487},
    {90, 1.3145}, {91, 1.2813}, {92, 1.2492}, {93, 1.2180}, {94, 1.1877},
    {95, 1.1584}, {96, 1.1300}, {97, 1.1023}, {98, 1.0756}, {99, 1.0496},
    {100, 1.0243}, {101, 0.9998}, {102, 0.9760}, {103, 0.9529}, {104, 0.9305},
    {105, 0.9087}, {106, 0.8875}, {107, 0.8670}, {108, 0.8470}, {109, 0.8275},
    {110, 0.8087}, {111, 0.7903}, {112, 0.7724}, {113, 0.7551}, {114, 0.7382},
    {115, 0.7218}, {116, 0.7058}, {117, 0.6903}, {118, 0.6752}, {119, 0.6604},
    {120, 0.6461}
};

typedef enum
{
    ADC1Rank_DC12 = 0x0,
    ADC1Rank_IN1,
    ADC1Rank_IN2,
    ADC1Rank_IN3,
    ADC1Rank_IN4,
    ADC1Rank_IN5,
    ADC1Rank_IN6,
    ADC1Rank_IN7,
    ADC1Rank_IN8,
    ADC1Rank_MAX,
} ADC1Rank;

DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc3;

static uint16_t s_adc1_dma_buf[ADC_DMA_BUF_SIZE * ADC1Rank_MAX];
static uint16_t s_adc3_dma_buf[ADC_DMA_BUF_SIZE];
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 9;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_17;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_18;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_19;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  //dma
  __HAL_RCC_DMA2_CLK_ENABLE();
  hdma_adc1.Instance = DMA2_Stream4;
  hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
  hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_adc1.Init.Mode = DMA_CIRCULAR;
  hdma_adc1.Init.Priority = DMA_PRIORITY_MEDIUM;
  hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_adc1);

  __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);

  HAL_ADCEx_Calibration_Start(&hadc1,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);

//   HAL_DMA_Start_IT(&hdma_adc1, (uint32_t)&ADC1->DR, (uint32_t)&s_adc1_dma_buf, 2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&s_adc1_dma_buf, ADC_DMA_BUF_SIZE*ADC1Rank_MAX);
  /* USER CODE END ADC1_Init 2 */

}
/* ADC3 init function */
void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.Resolution = ADC_RESOLUTION_16B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc3.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */
  __HAL_RCC_DMA2_CLK_ENABLE();
  hdma_adc3.Instance = DMA2_Stream1;
  hdma_adc3.Init.Request = DMA_REQUEST_ADC3;
  hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_adc3.Init.Mode = DMA_CIRCULAR;
  hdma_adc3.Init.Priority = DMA_PRIORITY_MEDIUM;
  hdma_adc3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_adc3);

  __HAL_LINKDMA(&hadc3, DMA_Handle, hdma_adc3);

  HAL_ADCEx_Calibration_Start(&hadc3,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);

//   HAL_DMA_Start_IT(&hdma_adc1, (uint32_t)&ADC1->DR, (uint32_t)&s_adc1_dma_buf, 2);
  HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&s_adc3_dma_buf, ADC_DMA_BUF_SIZE);
  /* USER CODE END ADC3_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_INP16
    PA1     ------> ADC1_INP17
    PA2     ------> ADC1_INP14
    PA3     ------> ADC1_INP15
    PA4     ------> ADC1_INP18
    PA5     ------> ADC1_INP19
    PA6     ------> ADC1_INP3
    PA7     ------> ADC1_INP7
    PB0     ------> ADC1_INP9
    */
    GPIO_InitStruct.Pin = ADC_DC12_Pin|ADC_IN_1_Pin|ADC_IN_2_Pin|ADC_IN_3_Pin
                          |ADC_IN_4_Pin|ADC_IN_5_Pin|ADC_IN_6_Pin|ADC_IN_7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_IN_8_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_IN_8_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* ADC3 clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();
  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_INP16
    PA1     ------> ADC1_INP17
    PA2     ------> ADC1_INP14
    PA3     ------> ADC1_INP15
    PA4     ------> ADC1_INP18
    PA5     ------> ADC1_INP19
    PA6     ------> ADC1_INP3
    PA7     ------> ADC1_INP7
    PB0     ------> ADC1_INP9
    */
    HAL_GPIO_DeInit(GPIOA, ADC_DC12_Pin|ADC_IN_1_Pin|ADC_IN_2_Pin|ADC_IN_3_Pin
                          |ADC_IN_4_Pin|ADC_IN_5_Pin|ADC_IN_6_Pin|ADC_IN_7_Pin);

    HAL_GPIO_DeInit(ADC_IN_8_GPIO_Port, ADC_IN_8_Pin);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();
  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 * @brief calculate avage value
 *
 * @param rank
 * @return uint32_t
 */
uint32_t adc1_avage_value(ADC1Rank rank)
{
    uint32_t value = 0;
    if(rank < ADC1Rank_MAX)
    {
        for (int i = 0; i < ADC_DMA_BUF_SIZE; i ++)
        {
            // printf("%x ",s_adc1_dma_buf[i * ADC1Rank_MAX + rank]);
            // if(i== ADC_DMA_BUF_SIZE-1)
            // {
            //     printf("\r\n");
            // }
            value += s_adc1_dma_buf[i * ADC1Rank_MAX + rank];
        }
    }
    value /= ADC_DMA_BUF_SIZE;
    return value;
}

float ADC_ReadDC12(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_DC12);
    // HAL_ADC_Start(&hadc1);	//
    // HAL_ADC_PollForConversion(&hadc1,10);
    // value = HAL_ADC_GetValue(&hadc1);
    return (value / (float)65536) *(10+1) / 1 * 3.3f;
}

float ADC_ReadIN1(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN1);
    float v_r = (value / (float)65536) * 3.3f;
    float r_r = (5.0f - v_r) / v_r * 2;
    float tmpr = 0;

//    printf("adc:%x,V:%.2f,R:%.2f,\r\n", value, v_r, r_r);

    if(r_r > resistance_table[0][1] || r_r < resistance_table[NUM_ENTRIES-1][1])
    {
//        printf("R value out of range\r\n");
        return tmpr;
    }

    for (int i = 0; i < NUM_ENTRIES; i ++)
    {
        if(resistance_table[i][1] <= r_r)
        {
            tmpr = resistance_table[i][0];
            break;
        }
    }
    return tmpr;
}

float ADC_ReadIN2(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN2);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN3(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN3);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN4(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN4);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN5(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN5);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN6(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN6);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN7(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN7);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadIN8(void)
{
    uint32_t value = adc1_avage_value(ADC1Rank_IN8);
    return (value / (float)65536) * 3.3f;
}

float ADC_ReadMcuTemperature(void)
{
    uint32_t value = 0;
    uint16_t TS_CAL1;
	uint16_t TS_CAL2;
    for (int i = 0; i < ADC_DMA_BUF_SIZE; i++)
    {
        value += s_adc3_dma_buf[i];
    }
    value /= ADC_DMA_BUF_SIZE;

    TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
    TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);

    return ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (value - TS_CAL1) + 30.0f;
}
/* USER CODE END 1 */
