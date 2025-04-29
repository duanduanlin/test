/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for idle_task */
osThreadId_t idle_taskHandle;
const osThreadAttr_t idle_task_attributes = {
  .name = "idle_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for can_recv_task */
osThreadId_t can_recv_taskHandle;
const osThreadAttr_t can_recv_task_attributes = {
  .name = "can_recv_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for can_send_task */
osThreadId_t can_send_taskHandle;
const osThreadAttr_t can_send_task_attributes = {
  .name = "can_send_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern int App_Main(void);
extern int Can_Recv_Handle(void);
extern int Can_Send_Handle(void);
extern void Idel_Handler(void);
extern void SD_SetUp(void);
/* USER CODE END FunctionPrototypes */

void IdleTask(void *argument);
void CanRecvTask(void *argument);
void CanSendTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    App_Main();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of idle_task */
  idle_taskHandle = osThreadNew(IdleTask, NULL, &idle_task_attributes);

  /* creation of can_recv_task */
  can_recv_taskHandle = osThreadNew(CanRecvTask, NULL, &can_recv_task_attributes);

  /* creation of can_send_task */
  can_send_taskHandle = osThreadNew(CanSendTask, NULL, &can_send_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_IdleTask */
/**
  * @brief  Function implementing the idle_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_IdleTask */
void IdleTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN IdleTask */
  SD_SetUp();
  /* Infinite loop */
  for(;;)
  {
    if(HAL_GPIO_ReadPin(SLEEP_KEY_GPIO_Port,SLEEP_KEY_Pin) == 0)
    {
        PWR_EnterStopMode();
    }
    Idel_Handler();
    osDelay(1000);
  }
  /* USER CODE END IdleTask */
}

/* USER CODE BEGIN Header_CanRecvTask */
/**
* @brief Function implementing the can_recv_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CanRecvTask */
void CanRecvTask(void *argument)
{
  /* USER CODE BEGIN CanRecvTask */
  /* Infinite loop */
  for(;;)
  {
    Can_Recv_Handle();
    osDelay(10);
  }
  /* USER CODE END CanRecvTask */
}

/* USER CODE BEGIN Header_CanSendTask */
/**
* @brief Function implementing the can_send_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CanSendTask */
void CanSendTask(void *argument)
{
  /* USER CODE BEGIN CanSendTask */
  /* Infinite loop */
  for(;;)
  {
      Can_Send_Handle();
      osDelay(10);
  }
  /* USER CODE END CanSendTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

