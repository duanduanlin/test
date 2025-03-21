/*
 * @Author: hanson
 * @Date: 2025-02-20 14:53:39
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-18 14:30:07
 * @Description:
 * @FilePath: \ps_vcu\modules\chassis_control.c
 */
#include "modules/chassis_control.h"
#include "common/error_code.h"
#include "main.h"
#include "modules/log.h"
#include "modules/data_writer.h"
#include "string.h"

typedef struct chassis_state
{
    DrivingMode crr_mode; // 当前模式
    DrivingMode tgt_mode; // 目标模式
    BodyState body;
} ChassisState; // 底盘状态

static ChassisState s_curr_chassis_state = {.crr_mode = Driving_Mode_INVALID}; // 当前底盘状态

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
void update_cmd(const ChassisCmd *cmd)
{
    handle_body_cmd(&cmd->body);
    Sync_Sweep_Cmd(&cmd->sweep);
    Sync_Power_Cmd(&cmd->power);
    Sync_Drv_Cmd(&cmd->drv, &cmd->steer);
}

/**
 * @brief 更新底盘状态
 *
 * @param status
 */
void update_chassis_status(ChassisStatus *status, const ChassisCmd *cmd)
{
    memcpy(&status->body_state, &s_curr_chassis_state.body, sizeof(BodyState));
    status->veh_state.driving_mode = s_curr_chassis_state.crr_mode;

    if (status->pwr_state.estop_sts) // 硬急停
    {
        status->veh_state.veh_emgcy_swh_st = 1;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_Key;
    }
    else if (cmd->power.emg_brk_req || cmd->power.soft_emg_brk_req) // 软急停
    {
        status->veh_state.ad_emgcy_stop_st = 1;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_Cloud;
    }
    else
    {
        status->veh_state.veh_emgcy_swh_st = 0;
        status->veh_state.ad_emgcy_stop_st = 0;
        status->veh_state.veh_emgcy_stop_reason = EStopReason_None;
    }
}

/**
 * @brief 更新rcu cmd
 *
 * @param cmd
 */
void update_rcu_cmd(const RcuCmd *rcu)
{
    ChassisCmd cmd = {0};
    LOG_EVERY_SECOND("rcu cmd:Gr:%d,Acc:%d,Agl:%f,Prk:%d,Cln:%d,Dmp:%d\r\n", rcu->tgt_gear, rcu->tgt_pedpos, rcu->target_angle, rcu->park_enable, rcu->one_clk_clean_ctrl, rcu->one_clk_dump_ctrl);
    cmd.drv.ctrl_mode = 0;
    cmd.drv.tgt_gear = rcu->tgt_gear;
    cmd.drv.tgt_pedpos = rcu->tgt_pedpos;
    cmd.steer.target_angle = rcu->target_angle;
    cmd.brake.park_enable = rcu->park_enable;
    cmd.sweep.one_clk_clean_ctrl = rcu->one_clk_clean_ctrl;
    cmd.sweep.one_clk_dump_ctrl = rcu->one_clk_dump_ctrl;
    update_cmd(&cmd);
}

/**
 * @brief 检查底盘状态变化
 *
 * @param status
 */
void check_mode(const ChassisStatus *status, const ChassisCmd *cmd)
{
    // 模式
    if (status->pwr_state.estop_sts ||
        cmd->power.emg_brk_req) // 硬急停
    {
        s_curr_chassis_state.tgt_mode = Driving_Mode_HardEStop;
    }
    else if (cmd->power.soft_emg_brk_req) // 软急停
    {
        s_curr_chassis_state.tgt_mode = Driving_Mode_SoftEStop;
    }
    else if (cmd->rcu.ctrl_mod) // 遥控
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

void Chassis_Control(ChassisStatus *status, const ChassisCmd *cmd)
{
    ChassisCmd default_cmd = {0};

    // 检查模式
    check_mode(status, cmd);

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
