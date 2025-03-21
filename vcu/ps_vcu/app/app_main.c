/*
 * @Author: hanson
 * @Date: 2025-02-12 16:32:38
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-21 15:58:57
 * @Descrche
 * @FilePath: \ps_vcu\app\app_main.c
 */

#include "modules/log.h"
#include "common/error_code.h"
#include "common/vcu_info.h"
#include "modules/data_writer.h"
#include "modules/chassis_control.h"
#include "modules/log.h"
#include "modules/data_handle.h"
#include "rtc.h"
#include "adc.h"
#include "gpio.h"
#include "tim.h"
#include "sd_driver.h"

static DataReader s_data_reader;

void SetUp()
{
    ChassisStatus *status = &s_data_reader.chassis_status;
    ChassisCmd *cmd = &s_data_reader.chassis_cmd;
    // 状态初始化
    status->veh_info.software_ver_num = VCU_SOFT_VERSION_NUM;
    status->veh_info.hardware_ver_num = VCU_HARD_VERSION_NUM;
    // 命令初始化
    cmd->power.veh_pwrup = PwrMode_Up;
    cmd->power.adcu_pwr_on_req = PwrMode_Up;
    cmd->power.mcu_pwr_on_req = PwrMode_Up;
    cmd->power.led_pwrup = PwrMode_Up;
    cmd->power.eps_pwrup = PwrMode_Up;
    cmd->power.ccu_pwrup = PwrMode_Up;
    cmd->power.obd_pwrup = PwrMode_Up;
    cmd->power.park_enable = PwrMode_Up;
    // 外设
    GPIO_Set_LedRun(Switch_On);
    GPIO_Set_LedError(Switch_Off);
    GPIO_Set_SDPower(Switch_On);
    PWM_SetLedRed(50);
    // PWM_SetHSOut1(50);
    // PWM_SetHSOut2(50);
    // PWM_SetHSOut3(50);
    // PWM_SetHSOut4(50);
    // PWM_SetLSOut1(50);
    // PWM_SetLSOut2(50);
    // PWM_SetLSOut3(50);
    // PWM_SetLSOut4(50);
    // GPIO_SetHSOut5(Switch_Off);
    // GPIO_SetHSOut6(Switch_Off);
    // GPIO_SetHSOut7(Switch_Off);
    // GPIO_SetHSOut8(Switch_Off);
    // GPIO_SetLSOut5(Switch_On);
    // GPIO_SetLSOut6(Switch_On);
    // GPIO_SetLSOut7(Switch_On);
    // GPIO_SetLSOut8(Switch_On);
    // GPIO_SetLSOut9(Switch_On);
    // GPIO_SetLSOut10(Switch_On);
    // PWM_SetLSOut11(50);
    // PWM_SetLSOut12(50);
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int App_Main(void)
{
    char timestamp[32] = {0};
    RTC_GetTimestamps(timestamp, 32);
    // 日志
    Log_Init();
    Log_Set_Lvl(LOG_LEVEL_INFO);
    LOG_INFO("VCU startup build time:%s %s\r\n", __DATE__, __TIME__);
    LOG_INFO("Curr Time:%s\r\n", timestamp);
    LOG_INFO("board id:0x%x\r\n", GPIO_GetIDs());
    // 数据处理模块
    Data_Handle_Init();
    // 初始化
    SetUp();

    return VCU_OK;
}

/**
 * @brief 处理can数据
 *
 * @return int
 */
int Can_Recv_Handle(void)
{
    // 读取并处理can数据
    Data_Handle_Parse(&s_data_reader);
    // 底盘控制
    Chassis_Control(&s_data_reader.chassis_status, &s_data_reader.chassis_cmd);
    // 更新底盘状态
    Sync_Chassis_Status(&s_data_reader.chassis_status);
    return VCU_OK;
}

/**
 * @brief 空闲状态处理
 *
 */
void Idel_Handler(void)
{
    // char timestamp[32] = {0};
    // RTC_GetTimestamps(timestamp, 32);
    // printf("timestamp:%s\r\n",timestamp);
    float dc12_v = ADC_ReadDC12();
    float mcu_tmp = ADC_ReadMcuTemperature();
    float in1_v = ADC_ReadIN1();
    // LOG_INFO("tmpr:%.2f C\r\n", mcu_tmp);
    // LOG_INFO("DC12:%.2f V\r\n", dc12_v);
    // LOG_INFO("IN1:%.2f C\r\n", in1_v);

    // 存储日志
    // Log_Save();
}

void SD_SetUp(void)
{
    if (Disk_Mount() == 0)
    {
        LOG_INFO("disk mount success\r\n");
        // Disk_Test_Write();
        Disk_Test_Read();
    }
    else
    {
        LOG_ERROR("disk mount failed\r\n");
    }
}
