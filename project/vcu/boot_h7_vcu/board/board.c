#include "board.h"
#include "elog.h"
#include "ring_buffer.h"
#include "crc16.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "fdcan.h"
// #include <math.h>
// #include <errno.h>

// 模块ID
#define MODULE_SELF MODULE_VCU 

// BOOT VERSION
#define BOOT_VERSION "1.0.0"

// LED
// #define LED1_Pin GPIO_PIN_5
// #define LED1_GPIO_Port GPIOG
// #define LED2_Pin GPIO_PIN_6
// #define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOA

#define LED1_TOGGLE HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
#define LED2_TOGGLE HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
#define LED3_TOGGLE HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
#define LED4_TOGGLE HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);

#include "usart.h"
#define UART             huart1
uint8_t uart_rec_buf[512];

// FLASH
#define FLASH_BASE_ADDR ((uint32_t)0x08000000)
#define FLASH_PARAM_OFFSET_ADDR ((uint32_t)0x00020000)
#define FLASH_APP_OFFSET_ADDR ((uint32_t)0x00040000)
#define FLASH_PARAM_MAX_SIZE 16 // 单位为KB
#define FLASH_APP_MAX_SIZE 512 // 单位为KB

// RAM
#define RAM_VAILD_ADDR_RANGE ((uint32_t)0x2bf00000)

#if USE_INTERFACE_CAN
#define APP_CFG_UAVCAN_LOCALHOST_NODE_ID MODULE_LIGHT_START // 30
#endif

static sys_ops_t sys_ops;
static boot_ops_t boot_ops;
static flash_ops_t flash_ops;
static fifo_ops_t fifo_ops;
static mrb_t recv_fifo;
static mrb_t send_fifo;
static uint8_t recv_fifo_buf[1024];
static uint8_t send_fifo_buf[1024];

static void init_elog(void);
static void SystemClock_Config(void);
static void boot_api_init(void);
static void sys_reboot(void);
static void sys_reset(void);
static void port_init(void);
static void task_led_callback(void);
static void port_send_data(uint8_t *msg_buf, uint16_t len);
static void set_msp(uint32_t addr);
#if USE_INTERFACE_CAN
static void can_send_data(uint8_t *msg_buf, uint16_t len);
uint8_t uavcan_msg_pack_publish(CanardMicrosecond timestampUsec, CanardPortID portID, size_t payloadSize, const void *payload);
#endif
#if USE_INTERFACE_UART
static void uart_send_data(uint8_t *msg_buf, uint16_t len);
#endif

/**
 * @brief 板级初始化
 * @param None
 * @retval None
 */
void board_init(void)
{
    init_elog();
    HAL_Init();
    SystemClock_Config();
    HAL_Delay(1000);
    gpio_init();
    port_init();
    boot_api_init();
    
    log_i("enter bootloader...");
    printf("enter bootloader...\r\n");
}

/**
 * @brief boot抽象层接口配置
 * @param None
 * @retval None
 */
#include "flash.h"
static void boot_api_init(void)
{
    flash_ops.unlock = flash_program_prepare;
    flash_ops.lock = flash_program_finish;
    flash_ops.erase = flash_erase;
    flash_ops.read = flash_read_bytes;
    flash_ops.write = flash_program;

    rb_init(&recv_fifo, recv_fifo_buf, 1024);
    rb_init(&send_fifo, send_fifo_buf, 1024);

    fifo_ops.recv_fifo_ptr = &recv_fifo;
    fifo_ops.send_fifo_ptr = &send_fifo;
    fifo_ops.ringbuf_is_empty = rb_is_empty;
    fifo_ops.ringbuf_get_payload_size = rb_get_payload_size;
    fifo_ops.ringbuf_pop_bytes = rb_pop_bytes;
    fifo_ops.ringbuf_push_bytes = rb_push_bytes;

    sys_ops.port_type = CAN_PORT;
    sys_ops.module_self = MODULE_SELF;
    sys_ops.flash_param_max_size = FLASH_PARAM_MAX_SIZE;
    sys_ops.flash_app_max_size = FLASH_APP_MAX_SIZE;
    strncpy((void *)&sys_ops.boot_version, BOOT_VERSION, sizeof(sys_ops.boot_version));
    sys_ops.flash_start_addr = FLASH_BASE_ADDR;
    sys_ops.param_offset_addr = FLASH_PARAM_OFFSET_ADDR;
    sys_ops.app_offset_addr = FLASH_APP_OFFSET_ADDR;
    sys_ops.ram_valid_addr_range = RAM_VAILD_ADDR_RANGE;
    sys_ops.get_sys_tick = HAL_GetTick;
    sys_ops.delay_ms = HAL_Delay;
    sys_ops.reboot = sys_reboot;
    sys_ops.reset = sys_reset;
    sys_ops.set_msp = set_msp;
    sys_ops.task_led_callback = task_led_callback;
    sys_ops.port_send_data = port_send_data;
#if USE_INTERFACE_CAN
    sys_ops.accept_canard_frame = accept_canard_frame;
    sys_ops.uavcan_msg_pack_publish = uavcan_msg_pack_publish;
#endif

    boot_ops.fifo_ops = &fifo_ops;
    boot_ops.flash_ops = &flash_ops;
    boot_ops.sys_ops = &sys_ops;

    // boot_ops_init(&boot_ops);
    boot_init(&boot_ops);
}

/**
 * @brief 系统重启
 * @param None
 * @retval None
 */
static void sys_reboot(void)
{
    NVIC_SystemReset();
}

static void set_msp(uint32_t addr)
{
    __set_MSP(*(volatile uint32_t *)addr);
}

/**
 * @brief 板级外设复位
 * @param None
 * @retval None
 */
static void sys_reset(void)
{
    log_d("system reset...");
    // peripherals disable
    // can_deinit();

    // nvic disable
    SysTick->CTRL &= (~SysTick_CTRL_TICKINT_Msk);
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
    HAL_NVIC_DisableIRQ(SysTick_IRQn);

    __disable_irq();
}

/**
 * @brief 通信接口初始化
 * @param None
 * @retval None
 */
static void port_init(void)
{
#if USE_INTERFACE_CAN
    can_init();                                            // can init
    // port_canard_init(8, APP_CFG_UAVCAN_LOCALHOST_NODE_ID); // uavcan init
    
#endif
#if USE_INTERFACE_UART
    MX_DMA_Init();
    MX_USART1_UART_Init();
    // dma_config();
#endif
}

#if USE_INTERFACE_CAN
uint8_t uavcan_msg_pack_publish(CanardMicrosecond timestampUsec, CanardPortID portID, size_t payloadSize, const void *payload)
{
    static uint8_t my_message_transfer_id; // Must be static or heap-allocated to retain state between calls.
    // int sta;
    CanardInstance *ins = port_canard_get_instance();
    const CanardTransfer transfer = {
        .timestamp_usec = timestampUsec, // Zero if transmission deadline is not limited.
        .priority = CanardPriorityExceptional,
        .transfer_kind = CanardTransferKindMessage,
        .port_id = portID,              // This is the subject-ID.
        .remote_node_id = CANARD_NODE_ID_UNSET, // Messages cannot be unicast, so use UNSET.
        .transfer_id = my_message_transfer_id,
        .payload_size = payloadSize,
        .payload = payload,
    };
    ++my_message_transfer_id; // The transfer-ID shall be incremented after every transmission on this subject.
    int32_t result = canardTxPush(ins, &transfer);
    if (result < 0)
    {
        // An error has occurred: either an argument is invalid or we've ran out of memory.
        // It is possible to statically prove that an out-of-memory will never occur for a given application if the
        // heap is sized correctly; for background, refer to the Robson's Proof and the documentation for O1Heap.
        log_info("Fatal error (w)\r\n");

        return 1;
    }
    for (const CanardFrame *txf = NULL; (txf = canardTxPeek(ins)) != NULL;) // Look at the top of the TX queue.
    {
        // if (uavcan_queue_can_send(txf) != 0)
        if (boot_uavcan_queue_can_send(txf) != 0)
        {
            continue;
        }
        // sys_ops_api->delay_ms(1);
        HAL_Delay(1);

        canardTxPop(ins);                          // Remove the frame from the queue after it's transmitted.
        ins->memory_free(ins, (CanardFrame *)txf); // Deallocate the dynamic memory afterwards.
    }

    return 0;
}
#endif

/**
 * @brief led任务回调函数
 * @param None
 * @retval None
 */
static void task_led_callback(void)
{
    LED1_TOGGLE;
    LED2_TOGGLE;
}

/**
 * @brief 通信接口发送
 * @param None
 * @retval None
 */
static void port_send_data(uint8_t *msg_buf, uint16_t len)
{
#if USE_INTERFACE_CAN
can_send_data(msg_buf, len);
#endif
#if USE_INTERFACE_UART
uart_send_data(msg_buf, len);
#endif
}

int canard_subscription_init(CanardInstance *ins)
{
    /*Be careful, must to keep CanardRxSubscription variables to be existed forever if you don't want to lose subscriptions*/
    static CanardRxSubscription subscriptions[5];
    int cnt = 0;
    int status = 0;

    status += canardRxSubscribe(ins, CanardTransferKindRequest,
                                OTA_CMD_200, sizeof(upgrade_notify_content_type),
                                CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC, &subscriptions[cnt++]);
#if (APP_CFG_OTA_ROLE == OTA_ROLE_BOOTLOADER)
    status += canardRxSubscribe(ins, CanardTransferKindRequest,
                                OTA_CMD_203_DATA, sizeof(upgrade_fw_block_type),
                                CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC, &subscriptions[cnt++]);
    status += canardRxSubscribe(ins, CanardTransferKindRequest,
                                OTA_CMD_205_REBOOT, sizeof(reboot_type),
                                CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC, &subscriptions[cnt++]);
#endif
    status += canardRxSubscribe(ins, CanardTransferKindRequest,
                                OTA_CMD_209, sizeof(version_check_type),
                                CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC, &subscriptions[cnt++]);
    status += canardRxSubscribe(ins, CanardTransferKindRequest,
                                OTA_CMD_211, sizeof(upgrade_status_type),
                                CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC, &subscriptions[cnt++]);

    if (status != cnt)
    {
        log_e("canardRxSubscribe failed");
        return 1;
    }

    return 0;
}

#if USE_INTERFACE_CAN
// can port send
//can_send_data接口已经弃用,改为直接调用can_send_msg
static void can_send_data(uint8_t *msg_buf, uint16_t len)
{
    iFrame_t *can_frame = (iFrame_t *)msg_buf;

    can_send_msg(can_frame->id, can_frame->data, can_frame->size);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    FDCAN_RxHeaderTypeDef header;
    iFrame_t can_frame;

	if ( hfdcan->Instance == FDCAN1 ){
        if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) //FIFO1?????
        {
            // can1_irq_callback();
            if ( HAL_OK ==  HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &header, can_frame.data) ){
                can_frame.timestamp_usec = 0;
                can_frame.id = header.Identifier;
                can_frame.size = header.DataLength;

                // dev_recv_fifo(&can1_dev,&can_frame,sizeof(can_frame_t));
                rb_push_bytes(&recv_fifo, &can_frame, sizeof(can_frame));
            }
        }
    }

    HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
   
}
#endif

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void HardFault_Handler(void)
{
    printf("enter hardfault irq and erase flash 0x08020000\n");
    flash_program_prepare();
    flash_erase(0x08020000);
    HAL_Delay(1000);
    while (1)
    {
        NVIC_SystemReset();
    }
}

#if USE_INTERFACE_UART
// uart port send
static void uart_send_data(uint8_t *msg_buf, uint16_t len)
{    
    // HAL_UART_Transmit(&UART,msg_buf,len,1000);
}



#endif

static void init_elog(void)
{
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
    /* start EasyLogger */
    elog_start();
}

#define OSCILLATOR
#define OSC_VALUE (25000000U)
#include "stm32h7xx_hal_pwr_ex.h"
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    // Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    // Error_Handler();
  }
}

