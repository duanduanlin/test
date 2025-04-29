/*
 * @Author: hanson
 * @Date: 2025-02-20 14:53:39
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-28 17:05:24
 * @Description:
 * @FilePath: \ps_vcu\modules\chassis_control.c
 */
#include "modules/chassis_control.h"
#include "common/error_code.h"
#include "main.h"
#include "modules/log.h"
#include "modules/data_writer.h"
#include "string.h"
#include <math.h>
#include "adc.h"
#include "modules/diag.h"

#define M_PI 3.1415926

#define WHEEL_RADIUS (0.15f)   // 轮半径
#define WHEEL_SPACING (0.6f)   // 轮间距
#define TRANSMISSION_RATIO (1) // 传动比

#define SPEED_LIMIT (4)

typedef struct chassis_state
{
    DrivingMode crr_mode; // 当前模式
    DrivingMode tgt_mode; // 目标模式
    BodyState body;
    uint8_t veh_err_level; // 整车故障等级
} ChassisState;            // 底盘状态

static ChassisState s_curr_chassis_state = {.crr_mode = Driving_Mode_INVALID}; // 当前底盘状态

/**
 * @brief 计算轮速
 *
 * @param veh_speed
 * @param angle_speed
 * @param left_wheel_speed
 * @param right_wheel_speed
 */
static void compute_wheel_velocities(double veh_speed, double angle_speed, double *left_wheel_speed, double *right_wheel_speed)
{
    double vel_left = veh_speed - (angle_speed * WHEEL_SPACING / 2.0);  // 计算左轮速度
    double vel_right = veh_speed + (angle_speed * WHEEL_SPACING / 2.0); // 计算右轮速度

    double wheel_perimeter = 2.0 * M_PI * WHEEL_RADIUS; // 计算左轮周长

    *left_wheel_speed = (vel_left / wheel_perimeter) * 60.0 / TRANSMISSION_RATIO;   // 将m/s转换为rpm
    *right_wheel_speed = (vel_right / wheel_perimeter) * 60.0 / TRANSMISSION_RATIO; // 将m/s转换为rpm
}

/**
 * @brief
 *
 * @param left_wheel_speed
 * @param right_wheel_speed
 * @param veh_speed
 * @param angle_speed
 */
static void compute_vehicle_velocities(double *veh_speed, double *angle_speed, double left_wheel_speed, double right_wheel_speed)
{
    double wheel_perimeter = 2.0 * M_PI * WHEEL_RADIUS; // 计算左轮周长
    double vel_left = left_wheel_speed * wheel_perimeter * TRANSMISSION_RATIO / 60.0;
    double vel_right = right_wheel_speed * wheel_perimeter * TRANSMISSION_RATIO / 60.0;

    *veh_speed = (vel_left + vel_right) / 2.0;
    *angle_speed = atan2(vel_right - vel_left, WHEEL_SPACING);
}

static void compute_odometer(double veh_speed, double *odometer)
{
    double delt = veh_speed * 0.01 / 1000;
    *odometer += delt;
}

/**
 * @brief 处理车身控制指令
 *
 * @param cmd
 */
static void handle_body_cmd(const BodyCmd *cmd)
{
    BodyState *state = &s_curr_chassis_state.body;
    if (cmd != NULL)
    {
        // 闪光灯
        if (cmd->dbl_flash_lamp)
        {
            // todo
            state->dbl_flash_lamp = 1;
        }
        else if (cmd->turn_l_lamp)
        {
            // todo
            state->turn_l_lamp = 1;
        }
        else if (cmd->turn_r_lamp)
        {
            // todo
            state->turn_r_lamp = 1;
        }
        else
        {
            state->dbl_flash_lamp = 1;
            state->turn_l_lamp = 0;
            state->turn_r_lamp = 0;
        }

        // 警示灯
        if (cmd->warning_lamp)
        {
            // todo
            state->warning_lamp = 1;
        }
        else
        {
            state->warning_lamp = 0;
        }

        // 大灯
        if (cmd->head_lamp)
        {
            // todo
            state->head_lamp = 1;
        }
        else
        {
            state->head_lamp = 0;
        }

        // 倒车灯
        if (cmd->back_lamp)
        {
            // todo
            state->back_lamp = 1;
        }
        else
        {
            state->back_lamp = 0;
        }

        // 蜂鸣器
        if (cmd->buzzer)
        {
            // todo
            state->buzzer = 1;
        }
        else
        {
            state->buzzer = 0;
        }

        // 喇叭
        if (cmd->horn)
        {
            // todo
            state->horn = 1;
        }
        else
        {
            state->horn = 0;
        }

        // 刹车灯
        if (cmd->brk_lamp)
        {
            // todo
            state->brk_lamp = 1;
        }
        else
        {
            state->brk_lamp = 0;
        }

        // 雾灯
        if (cmd->fog_lamp)
        {
            // todo
            state->fog_lamp = 1;
        }
        else
        {
            state->fog_lamp = 0;
        }

        // 示廓灯
        if (cmd->width_lamp)
        {
            // todo
            state->width_lamp = 1;
        }
        else
        {
            state->width_lamp = 0;
        }

        // 扫刷
        if (cmd->wiper)
        {
            // todo
            state->wiper = 1;
        }
        else
        {
            state->wiper = 0;
        }
    }
}

/**
 * @brief 更新命令
 *
 * @param status
 * @param cmd
 */
static void update_cmd(ChassisCmd *cmd)
{
    if (s_curr_chassis_state.veh_err_level == ErrLvl3)
    {
        // 停车
        cmd->drv.tgt_pedpos = 0;
        cmd->drv.tgt_gear = Gear_N;
        cmd->drv.tgt_veh_spd = 0;
        cmd->drv.tgt_veh_acc_spd = 0;
        cmd->drv.tgt_veh_acc_spd = 0;
        cmd->power.park_enable = 1;
    }

    if (s_curr_chassis_state.veh_err_level >= ErrLvl1)
    {
        // 停止清扫作业
        cmd->sweep.fender_ctrl = 2;
        cmd->sweep.one_clk_clean_ctrl = 2;
        cmd->sweep.one_clk_dump_ctrl = 2;
        cmd->sweep.water_pump_ctrl = 2;
        cmd->sweep.vbr_ctrl = 2;
        cmd->sweep.water_add_ctrl = 2;
        cmd->sweep.sweeping_ctrl = 2;
    }

    handle_body_cmd(&cmd->body);
    Sync_Sweep_Cmd(&cmd->sweep);
    Sync_Power_Cmd(&cmd->power);

    if (cmd->drv.ctrl_mode == 0)
    {
        // 踏板模式
        cmd->drv.tgt_veh_spd = cmd->drv.tgt_pedpos * SPEED_LIMIT / 100.0;
    }

    cmd->drv.tgt_veh_spd *= (1.0 - cmd->brake.target_brake_val / 100.0f);

    // 根据车速和角速度，计算左右轮速度
    compute_wheel_velocities(cmd->drv.tgt_veh_spd, cmd->steer.angle_speed, &cmd->drv.tgt_whl_spd_l, &cmd->drv.tgt_whl_spd_r);
    Sync_Drv_Cmd(&cmd->drv);
    Sync_Str_Cmd(&cmd->steer);
}

/**
 * @brief 处理故障
 *
 * @param status
 */
static void handle_fault(ChassisStatus *status, const ChassisCmd *cmd)
{
    // 故障处理
    float dc12_v = ADC_ReadDC12();
    status->veh_state.veh_err_level = ErrLvlNone;
    status->veh_state.lv_bat_low_volt = (dc12_v < 10.0) ? 1 : 0; // adc12采集

    if (dc12_v > 13.0 || dc12_v < 10.0)
    {
        Diag_Set_VcuFault_DC12();
    }
    else
    {
        Diag_Clear_VcuFault_DC12();
    }

    // 清扫故障
    if (status->sweep.error_code == 0)
    {
        status->veh_state.ccu_err_level = ErrLvlNone;
    }
    else
    {
        status->veh_state.ccu_err_level = ErrLvl1;
    }

    // 驱动故障
    if (status->drv_state.mcu_state_l.error_code == McuErrCode_None && status->drv_state.mcu_state_r.error_code == McuErrCode_None)
    {
        status->veh_state.mcu_err_level = ErrLvlNone;
    }
    else if (status->drv_state.mcu_state_l.error_code == McuErrCode_LowBatVoltage ||
             status->drv_state.mcu_state_l.error_code == McuErrCode_ControlOverheated ||
             status->drv_state.mcu_state_l.error_code == McuErrCode_MotorOverheated ||
             status->drv_state.mcu_state_l.error_code == McuErrCode_MotorStalled ||
             status->drv_state.mcu_state_r.error_code == McuErrCode_LowBatVoltage ||
             status->drv_state.mcu_state_r.error_code == McuErrCode_ControlOverheated ||
             status->drv_state.mcu_state_r.error_code == McuErrCode_MotorOverheated ||
             status->drv_state.mcu_state_r.error_code == McuErrCode_MotorStalled)
    {
        status->veh_state.mcu_err_level = ErrLvl2;
    }
    else
    {
        status->veh_state.mcu_err_level = ErrLvl3;
    }

    // 转向故障
    if (status->drv_state.str_error_code & 0x1)
    {
        status->veh_state.eps_err_level = ErrLvl1;
    }
    else if (status->drv_state.str_error_code & (0x1 << 1))
    {
        status->veh_state.eps_err_level = ErrLvl2;
    }
    else if (status->drv_state.str_error_code & (0x1 << 2))
    {
        status->veh_state.eps_err_level = ErrLvl3;
    }
    else
    {
        status->veh_state.eps_err_level = ErrLvlNone;
    }

    // 电源故障
    status->veh_state.pmu_err_level = ErrLvlNone;

    // rcu故障
    status->veh_state.rcu_err_level = ErrLvlNone;

    // 整车故障等级
    if (status->veh_state.mcu_err_level == ErrLvl3 ||
        status->veh_state.eps_err_level == ErrLvl3)
    {
        status->veh_state.veh_err_level = ErrLvl3;
    }
    else if (status->veh_state.mcu_err_level == ErrLvl2 ||
             status->veh_state.eps_err_level == ErrLvl2)
    {
        status->veh_state.veh_err_level = ErrLvl2;
    }
    else if (status->veh_state.ccu_err_level == ErrLvl1)
    {
        status->veh_state.veh_err_level = ErrLvl1;
    }
    else
    {
        status->veh_state.veh_err_level = ErrLvlNone;
    }

    // 模式判断
    if (status->pwr_state.estop_sts) // 硬急停
    {
        status->veh_state.veh_emgcy_swh_st = 1;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_Key;
        s_curr_chassis_state.tgt_mode = Driving_Mode_HardEStop;
    }
    else if (status->veh_state.veh_err_level == ErrLvl3)
    {
        status->veh_state.veh_emgcy_swh_st = 0;
        status->veh_state.ad_emgcy_stop_st = 0;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_VehFault;
        s_curr_chassis_state.tgt_mode = Driving_Mode_SoftEStop;
    }
    else if (cmd->power.soft_emg_brk_req) // 软急停
    {
        status->veh_state.ad_emgcy_stop_st = 1;
        status->veh_state.veh_emgcy_swh_st = 0;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_Cloud;
        s_curr_chassis_state.tgt_mode = Driving_Mode_SoftEStop;
    }
    else
    {
        status->veh_state.veh_emgcy_swh_st = 0;
        status->veh_state.ad_emgcy_stop_st = 0;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_None;
        if (cmd->rcu.ctrl_mod) // 遥控
        {
            s_curr_chassis_state.tgt_mode = Driving_Mode_Remote;
        }
        else if (cmd->drv.driving_mode == Driving_Mode_Remote_Cloud) // 远程
        {
            s_curr_chassis_state.tgt_mode = Driving_Mode_Remote_Cloud;
        }
        else if (cmd->drv.driving_mode == Driving_Mode_Auto) // 自动
        {
            s_curr_chassis_state.tgt_mode = Driving_Mode_Auto;
        }
        else // 待机
        {
            s_curr_chassis_state.tgt_mode = Driving_Mode_Standby;
        }
    }

    s_curr_chassis_state.veh_err_level = status->veh_state.veh_err_level;
}

/**
 * @brief 更新底盘状态
 *
 * @param status
 */
static void update_chassis_status(ChassisStatus *status, ChassisCmd *cmd)
{
    memcpy(&status->body_state, &s_curr_chassis_state.body, sizeof(BodyState));
    status->veh_state.driving_mode = s_curr_chassis_state.crr_mode;

    // 计算车速
    compute_vehicle_velocities(&status->drv_state.drv_veh_spd, &status->drv_state.str_angle_speed, status->drv_state.mcu_state_l.motor_speed, status->drv_state.mcu_state_r.motor_speed);
    // 计算里程
    compute_odometer(status->drv_state.drv_veh_spd, &status->odometer.curr_odometer);
}

/**
 * @brief 更新rcu cmd
 *
 * @param cmd
 */
static void update_rcu_cmd(const RcuCmd *rcu)
{
    ChassisCmd cmd = {0};
    LOG_EVERY_SECOND("rcu cmd:Gr:%d,Acc:%d,Agl:%f,Prk:%d,Cln:%d,Dmp:%d\r\n", rcu->tgt_gear, rcu->tgt_pedpos, rcu->target_angle, rcu->park_enable, rcu->one_clk_clean_ctrl, rcu->one_clk_dump_ctrl);
    cmd.drv.ctrl_mode = 0;
    cmd.drv.tgt_gear = rcu->tgt_gear;
    cmd.drv.tgt_pedpos = rcu->tgt_pedpos;
    cmd.steer.target_angle = rcu->target_angle;
    cmd.steer.angle_speed = M_PI / 6;
    cmd.brake.park_enable = rcu->park_enable;
    cmd.sweep.one_clk_clean_ctrl = rcu->one_clk_clean_ctrl;
    cmd.sweep.one_clk_dump_ctrl = rcu->one_clk_dump_ctrl;
    cmd.sweep.vbr_ctrl = rcu->vbr_ctrl;
    cmd.sweep.fender_ctrl = rcu->fender_ctrl;
    cmd.sweep.water_pump_ctrl = rcu->water_pump_ctrl;
    update_cmd(&cmd);
}

/**
 * @brief 灯光闪烁逻辑
 *
 */
void Lamp_Flash_Run(void)
{
    BodyState *state = &s_curr_chassis_state.body;
    if (state->turn_r_lamp)
    {
        // HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    }
    else if (state->turn_l_lamp)
    {
        // HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    }
    else if (state->dbl_flash_lamp)
    {
        // HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        // HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    }
}

void Chassis_Control(ChassisStatus *status, ChassisCmd *cmd)
{
    ChassisCmd default_cmd = {0};

    // 处理故障
    handle_fault(status, cmd);

    // 处理模式变化
    if (s_curr_chassis_state.tgt_mode != s_curr_chassis_state.crr_mode)
    {
        LOG_INFO("mode change from %d to %d\r\n", s_curr_chassis_state.crr_mode, s_curr_chassis_state.tgt_mode);
        if (s_curr_chassis_state.tgt_mode == Driving_Mode_Standby)
        {
            LOG_INFO("enter standby\r\n");
            update_cmd(&default_cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_Auto)
        {
            LOG_INFO("enter auto\r\n");
            update_cmd(cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_Remote_Cloud)
        {
            LOG_INFO("enter rmt cloud\r\n");
            update_cmd(cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_Remote)
        {
            LOG_INFO("enter rmt\r\n");
            update_rcu_cmd(&cmd->rcu);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_SoftEStop)
        {
            LOG_INFO("enter SEStop\r\n");
            update_cmd(&default_cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_HardEStop)
        {
            LOG_INFO("enter HEStop\r\n");
            update_cmd(&default_cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_Charging)
        {
            LOG_INFO("enter Charging\r\n");
            update_cmd(&default_cmd);
        }
        else if (s_curr_chassis_state.tgt_mode == Driving_Mode_OTA)
        {
            LOG_INFO("enter Ota\r\n");
            update_cmd(&default_cmd);
        }
    }

    // LOG_EVERY_SECOND("crr mode:%d\r\n", s_curr_chassis_state.crr_mode);
    switch (s_curr_chassis_state.crr_mode)
    {
    case Driving_Mode_Standby:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_Standby)
        {
            LOG_INFO("leave standby\r\n");
        }
        break;
    }
    case Driving_Mode_Auto:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_Auto)
        {
            LOG_INFO("leave auto\r\n");
        }
        else
        {
            update_cmd(cmd);
        }

        break;
    }
    case Driving_Mode_Remote_Cloud:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_Remote_Cloud)
        {
            LOG_INFO("leave rmt cloud\r\n");
        }
        else
        {
            update_cmd(cmd);
        }
        break;
    }
    case Driving_Mode_Remote:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_Remote)
        {
            LOG_INFO("leave rmt\r\n");
        }
        else
        {
            update_rcu_cmd(&cmd->rcu);
        }

        break;
    }
    case Driving_Mode_SoftEStop:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_SoftEStop)
        {
            LOG_INFO("leave SEStop\r\n");
        }
        break;
    }
    case Driving_Mode_HardEStop:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_HardEStop)
        {
            LOG_INFO("leave HEStop\r\n");
        }
        break;
    }
    case Driving_Mode_Charging:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_Charging)
        {
            LOG_INFO("leave Charging\r\n");
        }
        break;
    }
    case Driving_Mode_OTA:
    {
        if (s_curr_chassis_state.tgt_mode != Driving_Mode_OTA)
        {
            LOG_INFO("leave Ota\r\n");
        }
        break;
    }
    default:
        break;
    }
    s_curr_chassis_state.crr_mode = s_curr_chassis_state.tgt_mode;
    update_chassis_status(status, cmd);
}
