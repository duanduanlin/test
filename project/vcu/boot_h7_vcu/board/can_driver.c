#include "can_driver.h"
#include "fdcan.h"



void can_start(FDCAN_HandleTypeDef *handle,uint32_t ActiveITs){
  HAL_FDCAN_Start(handle);
//   HAL_FDCAN_ConfigFifoWatermark(handle, FDCAN_CFG_RX_FIFO0, 4);
  HAL_FDCAN_ActivateNotification(handle,ActiveITs,0);
  
}

void can_filter_init(FDCAN_HandleTypeDef *can_handle,
                    uint32_t IdType,
                    uint32_t FilterIndex,
                    uint32_t FilterType,
                    uint32_t FilterID1,
                    uint32_t FilterID2){
    FDCAN_FilterTypeDef FDCAN_RXFilter;
	/* Configure Rx filter */
	FDCAN_RXFilter.IdType = IdType;
	FDCAN_RXFilter.FilterIndex = FilterIndex;
	FDCAN_RXFilter.FilterType = FilterType;
	FDCAN_RXFilter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	FDCAN_RXFilter.FilterID1 = FilterID1;
	FDCAN_RXFilter.FilterID2 = FilterID2; /* For acceptance, MessageID and FilterID1 must match exactly */
	HAL_FDCAN_ConfigFilter(can_handle, &FDCAN_RXFilter);
    // HAL_FDCAN_ConfigGlobalFilter(&hfdcan, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);
    HAL_FDCAN_ConfigGlobalFilter(can_handle,FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE);
    if (HAL_FDCAN_ConfigGlobalFilter(can_handle, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, ENABLE, ENABLE) != HAL_OK)
    {
        return 2;
    }
    
}
uint16_t bsp_can_send_data(FDCAN_HandleTypeDef *can_handle,
                    uint32_t id,
                    uint32_t id_type,
                    uint32_t data_type,
                    uint32_t dlc,
                    uint8_t *data){
    FDCAN_TxHeaderTypeDef FDCAN_TxHeader;
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t  FreeTxNum=0;
    if(!can_handle || ! data)  return 0xFFFF;
	FDCAN_TxHeader.Identifier = id;
	FDCAN_TxHeader.IdType = id_type;
	FDCAN_TxHeader.TxFrameType = data_type;
	FDCAN_TxHeader.DataLength = (dlc)<<16;
	FDCAN_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	FDCAN_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	FDCAN_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	FDCAN_TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
	FDCAN_TxHeader.MessageMarker = 0;
    // logError("CAN[%08X] send\r\n",can_handle);
	FreeTxNum = HAL_FDCAN_GetTxFifoFreeLevel(can_handle);
    if (FreeTxNum == 0){
        // logError("CAN[%08X] mail box full\r\n",can_handle);
        HAL_FDCAN_Stop(can_handle);
        can_start(can_handle,FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
        return HAL_ERROR;
    }
    // portENTER_CRITICAL();
    status = HAL_FDCAN_AddMessageToTxFifoQ(can_handle,&FDCAN_TxHeader,data); 
    // portEXIT_CRITICAL();
	return status;     
}


// int can1_write(dev_size_t pos, const void *buf, dev_size_t size){
//     can_frame_t *can_frame=NULL;
//     can_frame = (can_frame_t *)buf;
//     uint32_t id_type = 0;
//     uint32_t data_type = 0;
//     if (can_frame->id_type  == CAN_ID_TYPE_STD ){
//         id_type = FDCAN_STANDARD_ID;
//     } else {
//         id_type = FDCAN_EXTENDED_ID;
//     }
//     if (can_frame->data_type  == CAN_FRAME_TYPE_DATA ){
//         data_type = FDCAN_DATA_FRAME;
//     } else {
//         data_type = FDCAN_REMOTE_FRAME;
//     }    
//     bsp_can_send_data(&hfdcan1, can_frame->id, id_type,data_type, can_frame->len, can_frame->data);
// }

int can1_open(uint16_t oflag){
    can_filter_init(&hfdcan1,
                    FDCAN_STANDARD_ID,
                    0,
                    FDCAN_FILTER_MASK,
                    0,
                    0);                    
    can_start(&hfdcan1,FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);

    return 0;
}
int can2_open(uint16_t oflag){
    can_filter_init(&hfdcan2,
                    FDCAN_EXTENDED_ID,
                    0,
                    FDCAN_FILTER_MASK,
                    0,
                    0); 
    can_filter_init(&hfdcan2,
                    FDCAN_STANDARD_ID,
                    1,
                    FDCAN_FILTER_MASK,
                    0,
                    0);                                       
    can_start(&hfdcan2,FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);

    return 0;
}

void can_init(void)
{
    MX_FDCAN1_Init();
    can1_open(0);
}








int can_send_msg(uint32_t id, const uint8_t *data, uint8_t len)
{
    uint32_t id_type = 0;
    uint32_t data_type = 0;

    data_type = FDCAN_DATA_FRAME;
    id_type = FDCAN_STANDARD_ID;
    printf("send:%x %d:%x %x %x %x %x %x %x %x\r\n",id,len,data[0],data[1],data[2],data[3],
        data[4],data[5],data[6],data[7]);
    bsp_can_send_data(&hfdcan1, id, id_type,data_type, len, data);
    return 0;
}

// void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
// {
// 	if ( hfdcan->Instance == FDCAN1 ){
//         if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) //FIFO1?????
//         {
//             // can1_irq_callback();
//             HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
//         }
//     }
// 	if ( hfdcan->Instance == FDCAN2 ){
//         if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) //FIFO1?????
//         {

//             // can2_irq_callback();
//             HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
            
//         }
//     }    
   
// }

/**
  * @brief This function handles FDCAN1 interrupt 0.
  */
void FDCAN1_IT0_IRQHandler(void)
{
  /* USER CODE BEGIN FDCAN1_IT0_IRQn 0 */

  /* USER CODE END FDCAN1_IT0_IRQn 0 */
  HAL_FDCAN_IRQHandler(&hfdcan1);
  /* USER CODE BEGIN FDCAN1_IT0_IRQn 1 */

  /* USER CODE END FDCAN1_IT0_IRQn 1 */
}

/**
  * @brief This function handles FDCAN2 interrupt 0.
  */
void FDCAN2_IT0_IRQHandler(void)
{
  /* USER CODE BEGIN FDCAN2_IT0_IRQn 0 */

  /* USER CODE END FDCAN2_IT0_IRQn 0 */
  HAL_FDCAN_IRQHandler(&hfdcan2);
  /* USER CODE BEGIN FDCAN2_IT0_IRQn 1 */

  /* USER CODE END FDCAN2_IT0_IRQn 1 */
}

/**
  * @brief This function handles FDCAN1 interrupt 1.
  */
void FDCAN1_IT1_IRQHandler(void)
{
  /* USER CODE BEGIN FDCAN1_IT1_IRQn 0 */

  /* USER CODE END FDCAN1_IT1_IRQn 0 */
  HAL_FDCAN_IRQHandler(&hfdcan1);
  /* USER CODE BEGIN FDCAN1_IT1_IRQn 1 */

  /* USER CODE END FDCAN1_IT1_IRQn 1 */
}

/**
  * @brief This function handles FDCAN2 interrupt 1.
  */
void FDCAN2_IT1_IRQHandler(void)
{
  /* USER CODE BEGIN FDCAN2_IT1_IRQn 0 */

  /* USER CODE END FDCAN2_IT1_IRQn 0 */
  HAL_FDCAN_IRQHandler(&hfdcan2);
  /* USER CODE BEGIN FDCAN2_IT1_IRQn 1 */

  /* USER CODE END FDCAN2_IT1_IRQn 1 */
}


void HAL_FDCAN_HighPriorityMessageCallback(FDCAN_HandleTypeDef *hfdcan){
    if ( hfdcan->Instance == FDCAN1 ) {
        printf("can 1 high\r\n"); 
    }
    if ( hfdcan->Instance == FDCAN2 ) {
        printf("can 2 high\r\n");    
    }    
}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
  /* Prevent unused argument(s) compilation warning */
    if ( hfdcan->Instance == FDCAN1 ) {
        printf("can 1 error\r\n"); 
    }
    if ( hfdcan->Instance == FDCAN2 ) {
        printf("can 2 error\r\n");    
    }
}





void HAL_FDCAN_ClockCalibrationCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ClkCalibrationITs){
    ERROR("callbak");
}
void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs)
{
    ERROR("callbak");  
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    ERROR("callbak");  
}
void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan)
{
    ERROR("callbak");  
}
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
    ERROR("callbak");  
}
void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
    ERROR("callbak");  
}
void HAL_FDCAN_RxBufferNewMessageCallback(FDCAN_HandleTypeDef *hfdcan){
    ERROR("callbak");  
}

void HAL_FDCAN_TimestampWraparoundCallback(FDCAN_HandleTypeDef *hfdcan){
    ERROR("callbak");  
}
void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *hfdcan){
    ERROR("callbak");  
}

void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs){
    ERROR("callbak");  
}
void HAL_FDCAN_TT_ScheduleSyncCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TTSchedSyncITs){
    ERROR("callbak");  
}
void HAL_FDCAN_TT_TimeMarkCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TTTimeMarkITs){
    ERROR("callbak");  
}
void HAL_FDCAN_TT_StopWatchCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t SWTime, uint32_t SWCycleCount){
    ERROR("callbak");  
}
void HAL_FDCAN_TT_GlobalTimeCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TTGlobTimeITs){
    ERROR("callbak");  
}
