/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    fdcan.c
 * @brief   This file provides code for the configuration
 *          of the FDCAN instances.
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
#include "stdio.h"
#include "rtc.h"
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */
static FDCAN_FilterTypeDef s_hfdcan1_rx_filter0;
static FDCAN_TxHeaderTypeDef s_hfdcan1_tx;
static FDCAN_RxHeaderTypeDef s_hfdcan1_rx;
static FDCAN_FilterTypeDef s_hfdcan2_rx_filter0;
static FDCAN_TxHeaderTypeDef s_hfdcan2_tx;
static FDCAN_RxHeaderTypeDef s_hfdcan2_rx;
static msg_cb s_msg_recv_cb_1 = NULL;
static msg_cb s_msg_recv_cb_2 = NULL;
/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = ENABLE;
  hfdcan1.Init.NominalPrescaler = 6;
  hfdcan1.Init.NominalSyncJumpWidth = 8;
  hfdcan1.Init.NominalTimeSeg1 = 31;
  hfdcan1.Init.NominalTimeSeg2 = 8;
  hfdcan1.Init.DataPrescaler = 6;
  hfdcan1.Init.DataSyncJumpWidth = 8;
  hfdcan1.Init.DataTimeSeg1 = 31;
  hfdcan1.Init.DataTimeSeg2 = 8;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 128;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.RxFifo0ElmtsNbr = 32;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 32;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */
    // HAL_FDCAN_ConfigFifoWatermark(&hfdcan1, FDCAN_CFG_RX_FIFO0, 2);

  /* USER CODE END FDCAN1_Init 2 */

}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = DISABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = ENABLE;
  hfdcan2.Init.NominalPrescaler = 6;
  hfdcan2.Init.NominalSyncJumpWidth = 8;
  hfdcan2.Init.NominalTimeSeg1 = 31;
  hfdcan2.Init.NominalTimeSeg2 = 8;
  hfdcan2.Init.DataPrescaler = 6;
  hfdcan2.Init.DataSyncJumpWidth = 8;
  hfdcan2.Init.DataTimeSeg1 = 31;
  hfdcan2.Init.DataTimeSeg2 = 8;
  hfdcan2.Init.MessageRAMOffset = 0x406;
  hfdcan2.Init.StdFiltersNbr = 1;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 0;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxFifo1ElmtsNbr = 32;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 0;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 0;
  hfdcan2.Init.TxBuffersNbr = 0;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 32;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED=0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN1 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOH_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PH13     ------> FDCAN1_TX
    PH14     ------> FDCAN1_RX
    */
    GPIO_InitStruct.Pin = ACAN_TX_Pin|ACAN_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspInit 0 */

  /* USER CODE END FDCAN2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN2 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    GPIO_InitStruct.Pin = CCAN_RX_Pin|CCAN_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* FDCAN2 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
  /* USER CODE BEGIN FDCAN2_MspInit 1 */

  /* USER CODE END FDCAN2_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN1 GPIO Configuration
    PH13     ------> FDCAN1_TX
    PH14     ------> FDCAN1_RX
    */
    HAL_GPIO_DeInit(GPIOH, ACAN_TX_Pin|ACAN_RX_Pin);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

  /* USER CODE END FDCAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, CCAN_RX_Pin|CCAN_TX_Pin);

    /* FDCAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
  /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

  /* USER CODE END FDCAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void FDCAN1_RX_Filter(uint32_t *ids, int num)
{
    for (int i = 0; i < num; i += 2)
    {
        s_hfdcan1_rx_filter0.IdType = FDCAN_STANDARD_ID;
        s_hfdcan1_rx_filter0.FilterIndex = i / 2;
        s_hfdcan1_rx_filter0.FilterType = FDCAN_FILTER_DUAL;
        s_hfdcan1_rx_filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
        s_hfdcan1_rx_filter0.FilterID1 = ids[i];
        printf("add filter id:%x\r\n", ids[i]);
        if (i + 1 < num)
        {
            s_hfdcan1_rx_filter0.FilterID2 = ids[i + 1];
            printf("add filter id:%x\r\n", ids[i + 1]);
        }

        if (HAL_FDCAN_ConfigFilter(&hfdcan1, &s_hfdcan1_rx_filter0) != HAL_OK)
        {
            Error_Handler();
        }
    }

    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE) != HAL_OK)
    {
        Error_Handler();
    }
}

void FDCAN2_RX_Filter(uint32_t *ids, int num)
{
    for (int i = 0; i < num; i += 2)
    {
        s_hfdcan2_rx_filter0.IdType = FDCAN_STANDARD_ID;
        s_hfdcan2_rx_filter0.FilterIndex = i / 2;
        s_hfdcan2_rx_filter0.FilterType = FDCAN_FILTER_DUAL;
        s_hfdcan2_rx_filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
        s_hfdcan2_rx_filter0.FilterID1 = ids[i];
        printf("add filter id:%x\r\n", ids[i]);
        if (i + 1 < num)
        {
            s_hfdcan2_rx_filter0.FilterID2 = ids[i + 1];
            printf("add filter id:%x\r\n", ids[i + 1]);
        }

        if (HAL_FDCAN_ConfigFilter(&hfdcan2, &s_hfdcan2_rx_filter0) != HAL_OK)
        {
            Error_Handler();
        }
    }

    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE) != HAL_OK)
    {
        Error_Handler();
    }
}

void FDCAN1_Start(void)
{
    HAL_FDCAN_Start(&hfdcan1);
    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_FULL, 0) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_WATERMARK, 0) != HAL_OK)
    {
        Error_Handler();
    }
}

void FDCAN2_Start(void)
{
    HAL_FDCAN_Start(&hfdcan2);
    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_FULL, 0) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_WATERMARK, 0) != HAL_OK)
    {
        Error_Handler();
    }
}

uint8_t FDCAN_Send_Msg(FDCAN_HandleTypeDef *hfcan, FDCAN_TxHeaderTypeDef *hfcan_tx, const CanMsg *msg)
{
    switch (msg->len)
    {
    case 0:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_0;
        break;
    case 1:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_1;
        break;
    case 2:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_2;
        break;
    case 3:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_3;
        break;
    case 4:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_4;
        break;
    case 5:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_5;
        break;
    case 6:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_6;
        break;
    case 7:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_7;
        break;
    case 8:
        hfcan_tx->DataLength = FDCAN_DLC_BYTES_8;
        break;
    default:
        return 1;
    }

    hfcan_tx->Identifier = msg->id;
    hfcan_tx->IdType = FDCAN_STANDARD_ID;
    hfcan_tx->TxFrameType = FDCAN_DATA_FRAME;
    hfcan_tx->ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    hfcan_tx->BitRateSwitch = FDCAN_BRS_OFF;
    hfcan_tx->FDFormat = FDCAN_CLASSIC_CAN;
    hfcan_tx->TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    hfcan_tx->MessageMarker = 0;

    if (FRAME_TYPE_REMOTE == msg->rtr)
        hfcan_tx->TxFrameType = FDCAN_REMOTE_FRAME;
    else
        hfcan_tx->TxFrameType = FDCAN_DATA_FRAME;

    if (HAL_FDCAN_AddMessageToTxFifoQ(hfcan, hfcan_tx, (uint8_t *)msg->buffer) == HAL_OK)
    {
        // printf("FDCAN1 sent data successfully! \n");
        return 0;
    }

    return 1;
}

uint8_t FDCAN1_Send_Msg(const CanMsg *msg)
{
    return FDCAN_Send_Msg(&hfdcan1, &s_hfdcan1_tx, msg);
}

uint8_t FDCAN2_Send_Msg(const CanMsg *msg)
{
    return FDCAN_Send_Msg(&hfdcan2, &s_hfdcan2_tx, msg);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    // uint8_t rxdata[8] = {0};

    if (FDCAN_IT_RX_FIFO0_WATERMARK == RxFifo0ITs ||
        FDCAN_IT_RX_FIFO0_NEW_MESSAGE == RxFifo0ITs ||
        FDCAN_IT_RX_FIFO0_FULL == RxFifo0ITs)
    {
        do
        {
            CanMsg msg = {0};
            HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &s_hfdcan1_rx, (uint8_t *)msg.buffer);
            // memcpy((uint8_t *)msg.buffer, rxdata, 8);
            msg.id = s_hfdcan1_rx.Identifier;
            msg.len = s_hfdcan1_rx.DataLength >> 16;

            if (s_hfdcan1_rx.RxFrameType == FDCAN_REMOTE_FRAME)
                msg.rtr = FRAME_TYPE_REMOTE;
            else
                msg.rtr = FRAME_TYPE_DATA;

            if (s_msg_recv_cb_1 != NULL)
            {
                s_msg_recv_cb_1(&msg);
            }

        } while ((hfdcan->Instance->RXF0S & 0x3F) > 0);
    }
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    // uint8_t rxdata[8] = {0};

    if (FDCAN_IT_RX_FIFO1_WATERMARK == RxFifo1ITs ||
        FDCAN_IT_RX_FIFO1_NEW_MESSAGE == RxFifo1ITs ||
        FDCAN_IT_RX_FIFO1_FULL == RxFifo1ITs)
    {
        do
        {
            CanMsg msg = {0};
            HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &s_hfdcan2_rx, (uint8_t *)msg.buffer);
            // memcpy((uint8_t *)msg.buffer, rxdata, 8);
            msg.id = s_hfdcan2_rx.Identifier;
            msg.len = s_hfdcan2_rx.DataLength >> 16;

            if (s_hfdcan2_rx.RxFrameType == FDCAN_REMOTE_FRAME)
                msg.rtr = FRAME_TYPE_REMOTE;
            else
                msg.rtr = FRAME_TYPE_DATA;

            if (s_msg_recv_cb_2 != NULL)
            {
                s_msg_recv_cb_2(&msg);
            }

        } while ((hfdcan->Instance->RXF1S & 0x3F) > 0);
    }
}

void FDCAN1_Set_RecvMsgCB(msg_cb cb)
{
    s_msg_recv_cb_1 = cb;
}

void FDCAN2_Set_RecvMsgCB(msg_cb cb)
{
    s_msg_recv_cb_2 = cb;
}

uint8_t FDCAN1_Recv_Msg(CanMsg *msg)
{
    if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &s_hfdcan1_rx, msg->buffer) != HAL_OK) /* 接收数杮 */
    {
        return 0;
    }

    msg->id = s_hfdcan1_rx.Identifier;
    msg->len = s_hfdcan1_rx.DataLength >> 16;

    if (s_hfdcan1_rx.RxFrameType == FDCAN_REMOTE_FRAME)
        msg->rtr = FRAME_TYPE_REMOTE;
    else
        msg->rtr = FRAME_TYPE_DATA;

    return msg->len;
}

uint8_t FDCAN2_Recv_Msg(CanMsg *msg)
{
    if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO1, &s_hfdcan2_rx, msg->buffer) != HAL_OK) /* 接收数杮 */
    {
        return 0;
    }

    msg->id = s_hfdcan2_rx.Identifier;
    msg->len = s_hfdcan2_rx.DataLength >> 16;

    if (s_hfdcan2_rx.RxFrameType == FDCAN_REMOTE_FRAME)
        msg->rtr = FRAME_TYPE_REMOTE;
    else
        msg->rtr = FRAME_TYPE_DATA;

    return msg->len;
}

int FDCAN_Msg2CSV(CanMsg *msg,char*dir, char *buff, int len)
{
    return snprintf(buff, len, "%u,%s,%x,%x %x %x %x %x %x %x %x\r\n", RTC_GetTimestamps(), dir, msg->id, msg->buffer[0], msg->buffer[1], msg->buffer[2], msg->buffer[3], msg->buffer[4], msg->buffer[5], msg->buffer[6], msg->buffer[7]);
}

int FDCAN_Msg2CAN(CanMsg *msg, int dir,char *buff, int len)
{
    long timestamps = RTC_GetTimestamps();
    int index = 0;
    buff[index++] = msg->id&0xff;
    buff[index++] = msg->id<<8 & 0xff;
    buff[index++] = msg->id<<16 & 0xff;
    buff[index++] = msg->id<<24 & 0xff;

    buff[index++] = timestamps&0xff;
    buff[index++] = timestamps <<8&0xff;
    buff[index++] = timestamps <<16&0xff;
    buff[index++] = timestamps <<24&0xff;

    buff[index++] = 0;
    buff[index++] = dir;
    buff[index++] = msg->rtr;
    buff[index++] = msg->len;
    memcpy(buff + index, msg->buffer, 8);
    index += 8;
    buff[index++] = 0;
    buff[index++] = 0;
    buff[index++] = 0;

    return index;
}

/* USER CODE END 1 */
