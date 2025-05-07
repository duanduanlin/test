/*
 * @Author: dding3
 * @Date: 2025-04-01 14:56:47
 * @LastEditors: dding3
 * @LastEditTime: 2025-05-06 18:22:12
 * @Description:
 * @FilePath: \ps_vcu\modules\diag.c
 */
#include "stdio.h"
#include "string.h"
#include "modules/diag.h"
#include "rtc.h"
#include "common/vcu_status.h"

#define VCU_FAULT_CODE_ID (0b100000)
#define MCU_FAULT_CODE_ID (0b101100)
#define CCU_FAULT_CODE_ID (0b100100)

#define NODE_LOST_COUNT_MAX (3)
#define NODE_LOST_TIMEOUT (500)

typedef struct
{
    uint8_t id : 6;          // id
    uint8_t sd_abnormal : 1; // sd卡异常
    uint8_t adcu_lost : 1;   // adcu离线

    uint8_t obd_lost : 1;      // obd离线
    uint8_t ccu_lost : 1;      // ccu离线
    uint8_t pmu_lost : 1;      // pmu离线
    uint8_t mcu_l_lost : 1;    // mcu l离线
    uint8_t mcu_r_lost : 1;    // mcu r 离线
    uint8_t eps_lost : 1;      // eps离线
    uint8_t dc12_abnormal : 1; // dc12电压异常
    uint8_t time_not_sync : 1; // 时间未同步

    uint8_t comm_abnormal : 1; // 通信异常
    uint8_t dcharge_not_disconnect : 1; // 充电枪未移除
    uint8_t reserved2 : 6;

    uint8_t reserved3 : 8;
    uint8_t reserved4 : 8;
    uint8_t reserved5 : 8;
    uint8_t reserved6 : 8;
    uint8_t reserved7 : 8;
} VcuErrorCode; // 故障码

typedef struct
{
    uint8_t id : 6;                  // id
    uint8_t soft_over_current_l : 1; // 软件过流
    uint8_t over_peed_l : 1;         // 电机过速

    uint8_t over_voltage_l : 1;               // 过压
    uint8_t power_supply_abnormal_key_l : 1;  // 钥匙电源供电异常
    uint8_t power_supply_abnormal12v_l : 1;   // 12v电源供电异常
    uint8_t power_supply_abnormal5v_l : 1;    // 5v电源供电异常
    uint8_t angle_sensor_powered_off_l : 1;   // 角度传感器断电
    uint8_t hard_over_current_l : 1;          // 硬件过流
    uint8_t current_closed_loop_failed_l : 1; // 电流闭环失败
    uint8_t low_bat_voltage_l : 1;            // 电池欠压

    uint8_t control_over_heated_l : 1;      // 控制器过温
    uint8_t motor_overheated_l : 1;         // 电机过温
    uint8_t curren_sensor_abnormal_l : 1;   // 电流传感器异常
    uint8_t angle_sensor_disturbance_l : 1; // 角度传感器扰动
    uint8_t turnaround_overrun_l : 1;       // 转把超限
    uint8_t turnaround_not_reset_l : 1;     // 转把未复位
    uint8_t motor_stalled_l : 1;            // 电机堵转
    uint8_t bms_fault_l : 1;                // bms故障

    uint8_t comm_abnormal_l : 1;             // 通信异常
    uint8_t soft_over_current_r : 1;         // 软件过流
    uint8_t over_peed_r : 1;                 // 电机过速
    uint8_t over_voltage_r : 1;              // 过压
    uint8_t power_supply_abnormal_key_r : 1; // 钥匙电源供电异常
    uint8_t power_supply_abnormal12v_r : 1;  // 12v电源供电异常
    uint8_t power_supply_abnormal5v_r : 1;   // 5v电源供电异常
    uint8_t angle_sensor_powered_off_r : 1;  // 角度传感器断电

    uint8_t hard_over_current_r : 1;          // 硬件过流
    uint8_t current_closed_loop_failed_r : 1; // 电流闭环失败
    uint8_t low_bat_voltage_r : 1;            // 电池欠压
    uint8_t control_over_heated_r : 1;        // 控制器过温
    uint8_t motor_overheated_r : 1;           // 电机过温
    uint8_t curren_sensor_abnormal_r : 1;     // 电流传感器异常
    uint8_t angle_sensor_disturbance_r : 1;   // 角度传感器扰动
    uint8_t turnaround_overrun_r : 1;         // 转把超限

    uint8_t turnaround_not_reset_r : 1; // 转把未复位
    uint8_t motor_stalled_r : 1;        // 电机堵转
    uint8_t bms_fault_r : 1;            // bms故障
    uint8_t comm_abnormal_r : 1;        // 通信异常
    uint8_t reserved5 : 4;

    uint8_t reserved6 : 8;
    uint8_t reserved7 : 8;
} McuErrorCode; // mcu故障码

typedef struct
{
    uint8_t id : 6;                   // id
    uint8_t SideBrushOvercurrent : 1; // 边刷过流
    uint8_t MainBrushOvercurrent : 1; // 滚刷过流

    uint8_t VBROvercurrent : 1;              // 震尘过流
    uint8_t DustBinLiftOvercurrent : 1;      // 垃圾仓抬升过流
    uint8_t BrushLiftOvercurrent : 1;        // 扫刷抬升过流
    uint8_t HighPressurePumpOvercurrent : 1; // 高压水泵过流
    uint8_t LowPressurePumpOvercurrent : 1;  // 低压水泵过流
    uint8_t DumpPushrodOvercurrent : 1;      // 倾倒推杆过流
    uint8_t VacuumCleanerOvercurrent : 1;    // 吸尘器过流
    uint8_t ThirdBrushLiftOvercurrent : 1;   // 第三边刷抬升过流

    uint8_t SkinStopSensorAbnormal : 1;  // 挡皮传感器异常
    uint8_t AngleSensorAbnormal : 1;     // 角度传感器异常
    uint8_t FullSensorAbnormal : 1;      // 溢满传感器异常
    uint8_t MainWireOverVoltage : 1;     // 母线过压
    uint8_t SideBrushLiftrodOffLine : 1; // 边刷抬升推杆掉线
    uint8_t MainBrushLiftrodOffLine : 1; // 滚刷抬升推杆掉线
    uint8_t DustBinLiftrodOffLine : 1;   // 垃圾仓抬升推杆掉线
    uint8_t DustBinDumprodOffLine : 1;   // 垃圾仓倾倒推杆掉线

    uint8_t SpinkAngleRodOffLine : 1;          // 喷头角度推杆掉线
    uint8_t SideBrushLiftErr : 1;              // 边刷抬升推杆报错
    uint8_t MainBrushLiftErr : 1;              // 滚刷抬升推杆报错
    uint8_t DustBinLiftErr : 1;                // 垃圾斗抬升推杆报错
    uint8_t DustBinDumpErr : 1;                // 垃圾斗倾倒推杆报错
    uint8_t SpinkAngleRodErr : 1;              // 喷头角度推杆报错
    uint8_t SideBrushAngleSensorOffline : 1;   // 边刷角度传感器掉线
    uint8_t DustBinLiftAngleSensorOffline : 1; // 垃圾斗抬升角度传感器掉线

    uint8_t SideBrushAngleSensorOutrange : 1;   // 边刷角度超限
    uint8_t DustBinLiftAngleSensorOutrange : 1; // 垃圾斗抬升角度超限
    uint8_t FullSensorOffline : 1;              // 满溢传感器掉线
    uint8_t reserved4 : 5;

    uint8_t reserved5 : 5;
    uint8_t reserved6 : 8;
    uint8_t reserved7 : 8;
} CcuErrorCode;

typedef struct
{
    long last_ticks;
    uint8_t err_count;
} NodeLostState;

static struct
{
    NodeLostState adcu_lost;
    NodeLostState ccu_lost;
    NodeLostState mcu_l_lost;
    NodeLostState mcu_r_lost;
    NodeLostState eps_lost;
    NodeLostState pmu_lost;
    NodeLostState obd_lost;
} s_vcu_fault_status;

static VcuErrorCode s_vcu_error_code = {.id = VCU_FAULT_CODE_ID};
static McuErrorCode s_mcu_error_code = {.id = MCU_FAULT_CODE_ID};
static CcuErrorCode s_ccu_error_code = {.id = CCU_FAULT_CODE_ID};

void Diag_Get_CcuFaultCode(uint8_t *data, int len)
{
    if (len == 8)
    {
        memcpy(data, &s_ccu_error_code, len);
    }
}

void Diag_Get_McuFaultCode(uint8_t *data, int len)
{
    if (len == 8)
    {
        memcpy(data, &s_mcu_error_code, len);
    }
}

void Diag_Get_VcuFaultCode(uint8_t *data, int len)
{
    if (len == 8)
    {
        memcpy(data, &s_vcu_error_code, len);
    }
}

void Diag_Set_VcuFault_SD(void)
{
    s_vcu_error_code.sd_abnormal = 1;
}

void Diag_Clear_VcuFault_SD(void)
{
    s_vcu_error_code.sd_abnormal = 0;
}

void Diag_Set_VcuFault_DC12(void)
{
    s_vcu_error_code.dc12_abnormal = 1;
}

void Diag_Clear_VcuFault_DC12(void)
{
    s_vcu_error_code.dc12_abnormal = 0;
}

void Diag_Set_VcuFault_TimeNotSync(void)
{
    s_vcu_error_code.time_not_sync = 1;
}

void Diag_Clear_VcuFault_TimeNotSync(void)
{
    s_vcu_error_code.time_not_sync = 0;
}

void Diag_Set_VcuFault_DchargeNotDisconnect(void)
{
    s_vcu_error_code.dcharge_not_disconnect = 1;
}

void Diag_Clear_VcuFault_DchargeNotDisconnect(void)
{
    s_vcu_error_code.dcharge_not_disconnect = 0;
}

void Diag_Update_Node(Node node)
{
    NodeLostState *lost = NULL;
    switch (node)
    {
    case Node_ADCU:
    {
        lost = &s_vcu_fault_status.adcu_lost;
    }
    case Node_CCU:
    {
        lost = &s_vcu_fault_status.ccu_lost;
    }
    case Node_MCU_L:
    {
        lost = &s_vcu_fault_status.mcu_l_lost;
    }
    case Node_MCU_R:
    {
        lost = &s_vcu_fault_status.mcu_r_lost;
    }
    case Node_EPS:
    {
        lost = &s_vcu_fault_status.eps_lost;
    }
    case Node_PMU:
    {
        lost = &s_vcu_fault_status.pmu_lost;
    }
    case Node_OBD:
    {
        lost = &s_vcu_fault_status.obd_lost;
    }
    }

    if (lost != NULL)
    {
        lost->last_ticks = HAL_GetTick();
    }
}

void Diag_Check_Node(void)
{
    uint32_t curr_tick = HAL_GetTick();

    // adcu
    if (curr_tick - s_vcu_fault_status.adcu_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.adcu_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("adcu lost\r\n");
            s_vcu_error_code.adcu_lost = 1;
        }
        else
        {
            printf("adcu lost,count %d\r\n", s_vcu_fault_status.adcu_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.adcu_lost.err_count = 0;
        s_vcu_error_code.adcu_lost = 0;
    }

    // ccu
    if (curr_tick - s_vcu_fault_status.ccu_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.ccu_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("ccu lost\r\n");
            s_vcu_error_code.ccu_lost = 1;
        }
        else
        {
            printf("ccu lost,count %d\r\n", s_vcu_fault_status.ccu_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.ccu_lost.err_count = 0;
        s_vcu_error_code.ccu_lost = 0;
    }

    // mcu l
    if (curr_tick - s_vcu_fault_status.mcu_l_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.mcu_l_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("mcu l lost\r\n");
            s_vcu_error_code.mcu_l_lost = 1;
        }
        else
        {
            printf("mcu l lost,count %d\r\n", s_vcu_fault_status.mcu_l_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.mcu_l_lost.err_count = 0;
        s_vcu_error_code.mcu_l_lost = 0;
    }

    // mcu r
    if (curr_tick - s_vcu_fault_status.mcu_r_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.mcu_r_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("mcu r lost\r\n");
            s_vcu_error_code.mcu_r_lost = 1;
        }
        else
        {
            printf("mcu r lost,count %d\r\n", s_vcu_fault_status.mcu_r_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.mcu_r_lost.err_count = 0;
        s_vcu_error_code.mcu_r_lost = 0;
    }

    // eps
    if (curr_tick - s_vcu_fault_status.eps_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.eps_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("eps lost\r\n");
            s_vcu_error_code.eps_lost = 1;
        }
        else
        {
            printf("eps lost,count %d\r\n", s_vcu_fault_status.eps_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.eps_lost.err_count = 0;
        s_vcu_error_code.eps_lost = 0;
    }

    // pmu
    if (curr_tick - s_vcu_fault_status.pmu_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.pmu_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("pmu lost\r\n");
            s_vcu_error_code.pmu_lost = 1;
        }
        else
        {
            printf("pmu lost,count %d\r\n", s_vcu_fault_status.pmu_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.pmu_lost.err_count = 0;
        s_vcu_error_code.pmu_lost = 0;
    }

    // obd
    if (curr_tick - s_vcu_fault_status.obd_lost.last_ticks > NODE_LOST_TIMEOUT)
    {
        if (s_vcu_fault_status.obd_lost.err_count > NODE_LOST_COUNT_MAX)
        {
            printf("obd lost\r\n");
            s_vcu_error_code.obd_lost = 1;
        }
        else
        {
            printf("obd lost,count %d\r\n", s_vcu_fault_status.obd_lost.err_count++);
        }
    }
    else
    {
        s_vcu_fault_status.obd_lost.err_count = 0;
        s_vcu_error_code.obd_lost = 0;
    }
}

void Diag_Set_McuFault(uint8_t code_l, uint8_t code_r)
{
    if (code_l == McuErrCode_SoftOverCurrent)
    {
        s_mcu_error_code.soft_over_current_l = 1;
    }
    else if (code_l == McuErrCode_OverSpeed)
    {
        s_mcu_error_code.over_peed_l = 1;
    }
    else if (code_l == McuErrCode_OverVoltage)
    {
        s_mcu_error_code.over_voltage_l = 1;
    }
    else if (code_l == McuErrCode_PowerSupplyAbnormalKey)
    {
        s_mcu_error_code.power_supply_abnormal_key_l = 1;
    }
    else if (code_l == McuErrCode_PowerSupplyAbnormal12v)
    {
        s_mcu_error_code.power_supply_abnormal12v_l = 1;
    }
    else if (code_l == McuErrCode_PowerSupplyAbnormal5v)
    {
        s_mcu_error_code.power_supply_abnormal5v_l = 1;
    }
    else if (code_l == McuErrCode_AngleSensorPoweredOff)
    {
        s_mcu_error_code.angle_sensor_powered_off_l = 1;
    }
    else if (code_l == McuErrCode_HardOverCurrent)
    {
        s_mcu_error_code.hard_over_current_l = 1;
    }
    else if (code_l == McuErrCode_CurrentClosedLoopFailed)
    {
        s_mcu_error_code.current_closed_loop_failed_l = 1;
    }
    else if (code_l == McuErrCode_LowBatVoltage)
    {
        s_mcu_error_code.low_bat_voltage_l = 1;
    }
    else if (code_l == McuErrCode_ControlOverheated)
    {
        s_mcu_error_code.control_over_heated_l = 1;
    }
    else if (code_l == McuErrCode_MotorOverheated)
    {
        s_mcu_error_code.motor_overheated_l = 1;
    }
    else if (code_l == McuErrCode_CurrenSensorAbnormal)
    {
        s_mcu_error_code.curren_sensor_abnormal_l = 1;
    }
    else if (code_l == McuErrCode_AngleSensorDisturbance)
    {
        s_mcu_error_code.angle_sensor_disturbance_l = 1;
    }
    else if (code_l == McuErrCode_TurnaroundOverrun)
    {
        s_mcu_error_code.turnaround_overrun_l = 1;
    }
    else if (code_l == McuErrCode_TurnaroundNotReset)
    {
        s_mcu_error_code.turnaround_not_reset_l = 1;
    }
    else if (code_l == McuErrCode_MotorStalled)
    {
        s_mcu_error_code.motor_stalled_l = 1;
    }
    else if (code_l == McuErrCode_BMSFault)
    {
        s_mcu_error_code.bms_fault_l = 1;
    }
    else if (code_l == McuErrCode_CommAbnormal)
    {
        s_mcu_error_code.comm_abnormal_l = 1;
    }
    else
    {
        s_mcu_error_code.soft_over_current_l = 0;
        s_mcu_error_code.over_peed_l = 0;
        s_mcu_error_code.over_voltage_l = 0;
        s_mcu_error_code.power_supply_abnormal_key_l = 0;
        s_mcu_error_code.power_supply_abnormal12v_l = 0;
        s_mcu_error_code.power_supply_abnormal5v_l = 0;
        s_mcu_error_code.angle_sensor_powered_off_l = 0;
        s_mcu_error_code.hard_over_current_l = 0;
        s_mcu_error_code.current_closed_loop_failed_l = 0;
        s_mcu_error_code.low_bat_voltage_l = 0;
        s_mcu_error_code.control_over_heated_l = 0;
        s_mcu_error_code.motor_overheated_l = 0;
        s_mcu_error_code.curren_sensor_abnormal_l = 0;
        s_mcu_error_code.angle_sensor_disturbance_l = 0;
        s_mcu_error_code.turnaround_overrun_l = 0;
        s_mcu_error_code.turnaround_not_reset_l = 0;
        s_mcu_error_code.motor_stalled_l = 0;
        s_mcu_error_code.bms_fault_l = 0;
        s_mcu_error_code.comm_abnormal_l = 0;
    }

    if (code_r == McuErrCode_SoftOverCurrent)
    {
        s_mcu_error_code.soft_over_current_r = 1;
    }
    else if (code_r == McuErrCode_OverSpeed)
    {
        s_mcu_error_code.over_peed_r = 1;
    }
    else if (code_r == McuErrCode_OverVoltage)
    {
        s_mcu_error_code.over_voltage_r = 1;
    }
    else if (code_r == McuErrCode_PowerSupplyAbnormalKey)
    {
        s_mcu_error_code.power_supply_abnormal_key_r = 1;
    }
    else if (code_r == McuErrCode_PowerSupplyAbnormal12v)
    {
        s_mcu_error_code.power_supply_abnormal12v_r = 1;
    }
    else if (code_r == McuErrCode_PowerSupplyAbnormal5v)
    {
        s_mcu_error_code.power_supply_abnormal5v_r = 1;
    }
    else if (code_r == McuErrCode_AngleSensorPoweredOff)
    {
        s_mcu_error_code.angle_sensor_powered_off_r = 1;
    }
    else if (code_r == McuErrCode_HardOverCurrent)
    {
        s_mcu_error_code.hard_over_current_r = 1;
    }
    else if (code_r == McuErrCode_CurrentClosedLoopFailed)
    {
        s_mcu_error_code.current_closed_loop_failed_r = 1;
    }
    else if (code_r == McuErrCode_LowBatVoltage)
    {
        s_mcu_error_code.low_bat_voltage_r = 1;
    }
    else if (code_r == McuErrCode_ControlOverheated)
    {
        s_mcu_error_code.control_over_heated_r = 1;
    }
    else if (code_r == McuErrCode_MotorOverheated)
    {
        s_mcu_error_code.motor_overheated_r = 1;
    }
    else if (code_r == McuErrCode_CurrenSensorAbnormal)
    {
        s_mcu_error_code.curren_sensor_abnormal_r = 1;
    }
    else if (code_r == McuErrCode_AngleSensorDisturbance)
    {
        s_mcu_error_code.angle_sensor_disturbance_r = 1;
    }
    else if (code_r == McuErrCode_TurnaroundOverrun)
    {
        s_mcu_error_code.turnaround_overrun_r = 1;
    }
    else if (code_r == McuErrCode_TurnaroundNotReset)
    {
        s_mcu_error_code.turnaround_not_reset_r = 1;
    }
    else if (code_r == McuErrCode_MotorStalled)
    {
        s_mcu_error_code.motor_stalled_r = 1;
    }
    else if (code_r == McuErrCode_BMSFault)
    {
        s_mcu_error_code.bms_fault_r = 1;
    }
    else if (code_r == McuErrCode_CommAbnormal)
    {
        s_mcu_error_code.comm_abnormal_r = 1;
    }
    else
    {
        s_mcu_error_code.soft_over_current_r = 0;
        s_mcu_error_code.over_peed_r = 0;
        s_mcu_error_code.over_voltage_r = 0;
        s_mcu_error_code.power_supply_abnormal_key_r = 0;
        s_mcu_error_code.power_supply_abnormal12v_r = 0;
        s_mcu_error_code.power_supply_abnormal5v_r = 0;
        s_mcu_error_code.angle_sensor_powered_off_r = 0;
        s_mcu_error_code.hard_over_current_r = 0;
        s_mcu_error_code.current_closed_loop_failed_r = 0;
        s_mcu_error_code.low_bat_voltage_r = 0;
        s_mcu_error_code.control_over_heated_r = 0;
        s_mcu_error_code.motor_overheated_r = 0;
        s_mcu_error_code.curren_sensor_abnormal_r = 0;
        s_mcu_error_code.angle_sensor_disturbance_r = 0;
        s_mcu_error_code.turnaround_overrun_r = 0;
        s_mcu_error_code.turnaround_not_reset_r = 0;
        s_mcu_error_code.motor_stalled_r = 0;
        s_mcu_error_code.bms_fault_r = 0;
        s_mcu_error_code.comm_abnormal_r = 0;
    }
}

void Diag_Set_CcuFault(uint32_t code)
{
    if (code & CcuErrCode_SideBrushOvercurrent)
    {
        s_ccu_error_code.SideBrushOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.SideBrushOvercurrent = 0;
    }
    if (code & CcuErrCode_MainBrushOvercurrent)
    {
        s_ccu_error_code.MainBrushOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.MainBrushOvercurrent = 0;
    }
    if (code & CcuErrCode_VBROvercurrent)
    {
        s_ccu_error_code.VBROvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.VBROvercurrent = 0;
    }
    if (code & CcuErrCode_DustBinLiftOvercurrent)
    {
        s_ccu_error_code.DustBinLiftOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.DustBinLiftOvercurrent = 0;
    }
    if (code & CcuErrCode_BrushLiftOvercurrent)
    {
        s_ccu_error_code.BrushLiftOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.BrushLiftOvercurrent = 0;
    }
    if (code & CcuErrCode_HighPressurePumpOvercurrent)
    {
        s_ccu_error_code.HighPressurePumpOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.HighPressurePumpOvercurrent = 0;
    }
    if (code & CcuErrCode_LowPressurePumpOvercurrent)
    {
        s_ccu_error_code.LowPressurePumpOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.LowPressurePumpOvercurrent = 0;
    }
    if (code & CcuErrCode_DumpPushrodOvercurrent)
    {
        s_ccu_error_code.DumpPushrodOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.DumpPushrodOvercurrent = 0;
    }
    if (code & CcuErrCode_VacuumCleanerOvercurrent)
    {
        s_ccu_error_code.VacuumCleanerOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.VacuumCleanerOvercurrent = 0;
    }
    if (code & CcuErrCode_ThirdBrushLiftOvercurrent)
    {
        s_ccu_error_code.ThirdBrushLiftOvercurrent = 1;
    }
    else
    {
        s_ccu_error_code.ThirdBrushLiftOvercurrent = 0;
    }
    if (code & CcuErrCode_SkinStopSensorAbnormal)
    {
        s_ccu_error_code.SkinStopSensorAbnormal = 1;
    }
    else
    {
        s_ccu_error_code.SkinStopSensorAbnormal = 0;
    }
    if (code & CcuErrCode_AngleSensorAbnormal)
    {
        s_ccu_error_code.AngleSensorAbnormal = 1;
    }
    else
    {
        s_ccu_error_code.AngleSensorAbnormal = 0;
    }
    if (code & CcuErrCode_FullSensorAbnormal)
    {
        s_ccu_error_code.FullSensorAbnormal = 1;
    }
    else
    {
        s_ccu_error_code.FullSensorAbnormal = 0;
    }
    if (code & CcuErrCode_MainWireOverVoltage)
    {
        s_ccu_error_code.MainWireOverVoltage = 1;
    }
    else
    {
        s_ccu_error_code.MainWireOverVoltage = 0;
    }
    if (code & CcuErrCode_SideBrushLiftrodOffLine)
    {
        s_ccu_error_code.SideBrushLiftrodOffLine = 1;
    }
    else
    {
        s_ccu_error_code.SideBrushLiftrodOffLine = 0;
    }
    if (code & CcuErrCode_MainBrushLiftrodOffLine)
    {
        s_ccu_error_code.MainBrushLiftrodOffLine = 1;
    }
    else
    {
        s_ccu_error_code.MainBrushLiftrodOffLine = 0;
    }
    if (code & CcuErrCode_DustBinLiftrodOffLine)
    {
        s_ccu_error_code.DustBinLiftrodOffLine = 1;
    }
    else
    {
        s_ccu_error_code.DustBinLiftrodOffLine = 0;
    }
    if (code & CcuErrCode_DustBinDumprodOffLine)
    {
        s_ccu_error_code.DustBinDumprodOffLine = 1;
    }
    else
    {
        s_ccu_error_code.DustBinDumprodOffLine = 0;
    }
    if (code & CcuErrCode_SpinkAngleRodOffLine)
    {
        s_ccu_error_code.SpinkAngleRodOffLine = 1;
    }
    else
    {
        s_ccu_error_code.SpinkAngleRodOffLine = 0;
    }
    if (code & CcuErrCode_SideBrushLiftErr)
    {
        s_ccu_error_code.SideBrushLiftErr = 1;
    }
    else
    {
        s_ccu_error_code.SideBrushLiftErr = 0;
    }
    if (code & CcuErrCode_MainBrushLiftErr)
    {
        s_ccu_error_code.MainBrushLiftErr = 1;
    }
    else
    {
        s_ccu_error_code.MainBrushLiftErr = 0;
    }
    if (code & CcuErrCode_DustBinLiftErr)
    {
        s_ccu_error_code.DustBinLiftErr = 1;
    }
    else
    {
        s_ccu_error_code.DustBinLiftErr = 0;
    }
    if (code & CcuErrCode_DustBinDumpErr)
    {
        s_ccu_error_code.DustBinDumpErr = 1;
    }
    else
    {
        s_ccu_error_code.DustBinDumpErr = 0;
    }
    if (code & CcuErrCode_SpinkAngleRodErr)
    {
        s_ccu_error_code.SpinkAngleRodErr = 1;
    }
    else
    {
        s_ccu_error_code.SpinkAngleRodErr = 0;
    }
    if (code & CcuErrCode_SideBrushAngleSensorOffline)
    {
        s_ccu_error_code.SideBrushAngleSensorOffline = 1;
    }
    else
    {
        s_ccu_error_code.SideBrushAngleSensorOffline = 0;
    }
    if (code & CcuErrCode_DustBinLiftAngleSensorOffline)
    {
        s_ccu_error_code.DustBinLiftAngleSensorOffline = 1;
    }
    else
    {
        s_ccu_error_code.DustBinLiftAngleSensorOffline = 0;
    }
    if (code & CcuErrCode_SideBrushAngleSensorOutrange)
    {
        s_ccu_error_code.SideBrushAngleSensorOutrange = 1;
    }
    else
    {
        s_ccu_error_code.SideBrushAngleSensorOutrange = 0;
    }
    if (code & CcuErrCode_DustBinLiftAngleSensorOutrange)
    {
        s_ccu_error_code.DustBinLiftAngleSensorOutrange = 1;
    }
    else
    {
        s_ccu_error_code.DustBinLiftAngleSensorOutrange = 0;
    }
    if (code & CcuErrCode_FullSensorOffline)
    {
        s_ccu_error_code.FullSensorOffline = 1;
    }
    else
    {
        s_ccu_error_code.FullSensorOffline = 0;
    }
}
