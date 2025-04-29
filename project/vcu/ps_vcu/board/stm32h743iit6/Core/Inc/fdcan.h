/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.h
  * @brief   This file contains all the function prototypes for
  *          the fdcan.c file
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
#ifndef __FDCAN_H__
#define __FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_HandleTypeDef hfdcan2;

/* USER CODE BEGIN Private defines */
typedef enum can_net
{
    CanNetA = 0x0, // A CAN网络
    CanNetC = 0x1, // C CAN网络
} CanNet;          // can网络
typedef enum frame_type
{
    FRAME_TYPE_DATA   = 0,
    FRAME_TYPE_REMOTE = 1,
}FrameType;

typedef struct canmsg
{
	uint32_t     id;
    FrameType       rtr;
    uint8_t      len;
    uint8_t      buffer[8];
}CanMsg;

typedef int (*msg_cb)(CanMsg *msg);
/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);
void MX_FDCAN2_Init(void);

/* USER CODE BEGIN Prototypes */
void FDCAN1_Start(void);
void FDCAN2_Start(void);
void FDCAN1_RX_Filter(uint32_t *ids, int num);
void FDCAN2_RX_Filter(uint32_t *ids, int num);
uint8_t FDCAN1_Send_Msg(const CanMsg *msg);
uint8_t FDCAN1_Recv_Msg(CanMsg *msg);
uint8_t FDCAN2_Send_Msg(const CanMsg *msg);
uint8_t FDCAN2_Recv_Msg(CanMsg *msg);
void FDCAN1_Set_RecvMsgCB(msg_cb cb);
void FDCAN2_Set_RecvMsgCB(msg_cb cb);

int FDCAN_Msg2CSV(CanMsg *msg, char*dir,char *buff, int len);
int FDCAN_Msg2CAN(CanMsg *msg, int dir,char *buff, int len);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */

