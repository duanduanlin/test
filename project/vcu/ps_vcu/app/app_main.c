/*
 * @Author: hanson
 * @Date: 2025-02-12 16:32:38
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-28 16:47:01
 * @Descrche
 * @FilePath: \ps_vcu\app\app_main.c
 */

#include "modules/log.h"
#include "common/error_code.h"
#include "common/vcu_info.h"
#include "modules/chassis_control.h"
#include "modules/log.h"
#include "modules/data_handle.h"
#include "rtc.h"
#include "adc.h"
#include "gpio.h"
#include "tim.h"
#include "sd_driver.h"
#include "modules/diag.h"
#include "modules/ota_app.h"

#define TIME_UPDATE_INTERVAL (24 * 60 * 60 * 1000)

static DataReader s_data_reader;

void SetUp()
{
    ChassisStatus *status = &s_data_reader.chassis_status;
    ChassisCmd *cmd = &s_data_reader.chassis_cmd;

    status->odometer.total_odometer = Vcu_Info_GetOdometer();
    status->odometer.curr_odometer = 0;
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
    // 故障码初始化
    Diag_Get_VcuFaultCode((uint8_t *)&status->vcu_fault_code, 8);
    Diag_Get_CcuFaultCode((uint8_t *)&status->ccu_fault_code, 8);
    Diag_Get_McuFaultCode((uint8_t *)&status->mcu_fault_code, 8);

    power_up_ota_handle();
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int App_Main(void)
{
    char timestamp[32] = {0};
    RTC_GetTimestampsStr(timestamp, 32);
    // 日志
    Log_Init();
    Log_Set_Lvl(LOG_LEVEL_INFO);
    LOG_INFO("VCU startup build time:%s %s\r\n", __DATE__, __TIME__);
    LOG_INFO("Curr Time:%s\r\n", timestamp);
    LOG_INFO("board id:0x%x\r\n", GPIO_GetIDs());
    // 读取vcu信息
    Vcu_Info_Read();
    // Vcu_Info_AddOdometer(1.1);

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
 * @brief 发送can数据
 *
 * @return int
 */
int Can_Send_Handle(void)
{
    Data_Handle_Sync();
    return VCU_OK;
}
/**
 * @brief 空闲状态处理
 *
 */
void Idel_Handler(void)
{
    static long time_update_tick = 0;
    static double last_save_odometer = 0;
    static int tick_count = 0;
    ChassisStatus *status = &s_data_reader.chassis_status;
    ChassisCmd *cmd = &s_data_reader.chassis_cmd;

    char timestamp[32] = {0};
    RTC_GetTimestampsStr(timestamp, 32);
    // printf("timestamp:%s\r\n",timestamp);
    float dc12_v = ADC_ReadDC12();
    float mcu_tmp = ADC_ReadMcuTemperature();
    float in1_v = ADC_ReadIN1();
    // LOG_INFO("tmpr:%.2f C\r\n", mcu_tmp);
    // LOG_INFO("DC12:%.2f V\r\n", dc12_v);
    // LOG_INFO("IN1:%.2f C\r\n", in1_v);
    double delt_odo = status->odometer.curr_odometer - last_save_odometer;

    if (delt_odo > 0)
    {
        Vcu_Info_AddOdometer(delt_odo);
        last_save_odometer = status->odometer.curr_odometer;
    }

    if (tick_count % 5 == 0)
    {
        LOG_INFO("odometer:%f km\r\n", Vcu_Info_GetOdometer());
        // 5秒存储下info
        Vcu_Info_Write();
    }

    // 存储日志
    // Log_File_Sync();
    // Log_Data_Save(timestamp,strlen(timestamp));
    Log_Data_Sync();

    // 诊断
    Diag_Check_Node();
    // mcu故障
    Diag_Set_McuFault(status->drv_state.mcu_state_l.error_code, status->drv_state.mcu_state_r.error_code);
    // ccu故障
    Diag_Set_CcuFault(status->sweep.error_code);
    // 检测时间同步
    if ((cmd->time.is_time_sync == 1) && ((HAL_GetTick() - cmd->time.last_sync_ticks) < 5 * 1000))
    {
        // 时间已更新可以同步
        if ((time_update_tick == 0) || ((HAL_GetTick() - time_update_tick) > TIME_UPDATE_INTERVAL))
        {
            time_update_tick = HAL_GetTick();
            RTC_TimeTypeDef time = {0};
            RTC_DateTypeDef date = {0};
            int week = RTC_GetWeekDay(cmd->time.year, cmd->time.month, cmd->time.day);

            time.Hours = cmd->time.hour;
            time.Minutes = cmd->time.minute;
            time.Seconds = cmd->time.second;

            date.Month = cmd->time.month + 1;
            date.Date = cmd->time.day;
            date.Year = cmd->time.year - 1970;
            date.WeekDay = week;

            MX_RTC_SetTime(time, date);
        }
    }
    if (RTC_IsTimeSet() == 0)
    {
        LOG_INFO("time not sync\r\n");
        Diag_Set_VcuFault_TimeNotSync();
    }
    else
    {
        Diag_Clear_VcuFault_TimeNotSync();
        if (Disk_Status_Get(eDisk_SD) == eStatus_Valid)
        {
            LogFile_Init();
        }
    }
    // 更新故障码
    Diag_Get_VcuFaultCode((uint8_t *)&status->vcu_fault_code, 8);
    Diag_Get_CcuFaultCode((uint8_t *)&status->ccu_fault_code, 8);
    Diag_Get_McuFaultCode((uint8_t *)&status->mcu_fault_code, 8);

    tick_count++;
}

void SD_SetUp(void)
{
    if (Disk_Mount() == 0)
    {
        LOG_INFO("disk mount success\r\n");
    }
    else
    {
        Diag_Set_VcuFault_SD();
        LOG_ERROR("disk mount failed\r\n");
    }
}
