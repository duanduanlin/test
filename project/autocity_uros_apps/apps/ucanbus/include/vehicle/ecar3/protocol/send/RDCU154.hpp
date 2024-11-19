/*
 * @Author: hanson
 * @Date: 2024-08-28 11:45:42
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-30 17:20:03
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\send\RDCU154.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU154_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU154_HPP_

#include "protocol/BaseProtocol.hpp"

class RDCU154 : public BaseProtocol
{
public:
    enum RdcuTargetSweepMode
    {
        RDCU_TGT_SWEEP_MODE_DRIVE = 0,
        RDCU_TGT_SWEEP_MODE_SWEEP = 1,
    };

    enum RdcuSweepCommand
    {
        RDCU_SWEEP_CMD_OFF = 0,
        RDCU_SWEEP_CMD_ON = 1,
    };

    enum RdcuGarbageDumpCmdType
    {
        RDCU_GARBAGE_DUMP_CMD_OFF = 0,
        RDCU_GARBAGE_DUMP_CMD_ON = 1,
    };

    enum RdcuSweepEStopCommand
    {
        RDCU_SWEEP_ESTOP_CMD_NORAML = 0,
        RDCU_SWEEP_ESTOP_CMD_EMERGENCY = 1,
    };

    enum RdcuFrontBoardControlType
    {
        RDCU_FRONT_BOARD_CTRL_OFF = 0,
        RDCU_FRONT_BOARD_CTRL_ON = 1,
    };

    enum RdcuWaterValveControlType
    {
        RDCU_WATER_VALVE_CTRL_CLOSE = 0,
        RDCU_WATER_VALVE_CTRL_OPEN = 1,
    };

    enum RdcuBrushAbdCmdType
    {
        RDCU_BRUSH_ABD_CMD_INVALID = 0, // 无效
        RDCU_BRUSH_ABD_CMD_STRETCH = 1, // 延伸
        RDCU_BRUSH_ABD_CMD_RETRACT = 2, // 回缩
    };

    enum RdcuLiftRodCmdType
    {
        RDCU_LIFT_ROD_CMD_INVALID = 0, // 无效
        RDCU_LIFT_ROD_CMD_RISE = 1,    // 上升
        RDCU_LIFT_ROD_CMD_FALL = 2,    // 下降
    };

    enum RdcuSwitchCmd
    {
        RDCU_SwitchCmdOFF = 0,
        RDCU_SwitchCmdON = 1,
    };

    enum FanCtrlModeSel
    {
        GearCtrlMode = 0,
        SpeedCtroMode = 1,
        DisableMode = 2,
    };

    enum FanSpdGearSel
    {
        Medium_Speed_Gear = 0,
        Low_Speed_Gear = 1,
        High_Speed_Gear = 2,
        Disable = 3,
    };

private:
    /* data */
    uint8_t _tgt_sweep_mode;                      // 清扫模式
    uint8_t _sweep_cmd;                           // 清扫指令
    uint8_t _dump_cmd;                            // 垃圾倾倒
    uint8_t _sweep_estop_cmd;                     // 清扫系统急停
    uint8_t _brush_water_valve_cmd;               // 边刷喷水阀
    uint8_t _fan_dust_fall_valve_cmd;             // 风机降尘阀
    uint8_t _suction_dust_fall_valve_cmd;         // 吸口降尘阀
    uint8_t _dustbin_dust_fall_valve_cmd;         // 垃圾箱降尘阀
    uint8_t _roll_swp_water_valve_cmd;            // 滚扫降尘水阀
    uint8_t _dustbin_clean_water_valve_cmd;       // 垃圾箱自洁水阀
    uint8_t _water_boxlid_cmd;                    // 加水盖控制
    uint8_t _water_drain_valve_cmd;               // 放水阀
    double _left_front_brush_abd_dist;            // 左前置边刷目标外展距离
    double _right_front_brush_abd_dist;           // 右前置边刷外展距离
    uint8_t _left_front_brush_extension_rod_cmd;  // 左前边刷伸缩杆控制
    uint8_t _right_front_brush_extension_rod_cmd; // 右前边刷伸缩杆控制
    uint8_t _left_front_brush_lift_rod_cmd;       // 左前边刷升降杆控制
    uint8_t _right_front_brush_lift_rod_cmd;      // 右前边刷升降杆控制
    uint8_t _rear_brush_lift_rod_cmd;             // 后置边刷升降杆控制
    uint8_t _suction_lift_rod_cmd;                // 吸口升降杆控制
    uint8_t _main_brush_lift_rod_cmd;             // 滚刷升降杆控制
    uint8_t _front_fender_cmd;                    // 前挡板控制
    uint8_t _shake_dust_cmd;                      // 震尘控制
public:
    RDCU154(/* args */) : BaseProtocol(0x154)
    {
        ResetCmd();
    }
    ~RDCU154() = default;

    void UpdateCmd(uint64_t *data) override;
    void ResetCmd() override;

    void SetTgtSweepMode(const uint8_t val)
    {
        _tgt_sweep_mode = val;
    }

    void SetSweepCmd(const uint8_t val)
    {
        _sweep_cmd = val;
    }

    void SetDumpCmd(const uint8_t val)
    {
        _dump_cmd = val;
    }

    void SetSweepEstopCmd(const uint8_t val)
    {
        _sweep_estop_cmd = val;
    }

    void SetBrushWaterValveCmd(const uint8_t val)
    {
        _brush_water_valve_cmd = val;
    }

    void SetFanDustFallValveCmd(const uint8_t val)
    {
        _fan_dust_fall_valve_cmd = val;
    }

    void SetSuctionDustFallValveCmd(const uint8_t val)
    {
        _suction_dust_fall_valve_cmd = val;
    }

    void SetDustbinDustFallValveCmd(const uint8_t val)
    {
        _dustbin_dust_fall_valve_cmd = val;
    }

    void SetRollSwpWaterValveCmd(const uint8_t val)
    {
        _roll_swp_water_valve_cmd = val;
    }

    void SetDustbinCleanWaterValveCmd(const uint8_t val)
    {
        _dustbin_clean_water_valve_cmd = val;
    }

    void SetWaterBoxlidCmd(const uint8_t val)
    {
        _water_boxlid_cmd = val;
    }

    void SetWaterDrainValveCmd(const uint8_t val)
    {
        _water_drain_valve_cmd = val;
    }

    void SetLeftFrontBrushAbdDist(const double val)
    {
        _left_front_brush_abd_dist = val;
    }

    void SetRightFrontBrushAbdDist(const double val)
    {
        _right_front_brush_abd_dist = val;
    }

    void SetLeftFrontBrushExtensionRodCmd(const uint8_t val)
    {
        _left_front_brush_extension_rod_cmd = val;
    }

    void SetRightFrontBrushExtensionRodCmd(const uint8_t val)
    {
        _right_front_brush_extension_rod_cmd = val;
    }

    void SetLeftFrontBrushLiftRodCmd(const uint8_t val)
    {
        _left_front_brush_lift_rod_cmd = val;
    }

    void SetRightFrontBrushLiftRodCmd(const uint8_t val)
    {
        _right_front_brush_lift_rod_cmd = val;
    }

    void SetRearBrushLiftRodCmd(const uint8_t val)
    {
        _rear_brush_lift_rod_cmd = val;
    }

    void SetSuctionLiftRodCmd(const uint8_t val)
    {
        _suction_lift_rod_cmd = val;
    }

    void SetMainBrushLifRodCmd(const uint8_t val)
    {
        _main_brush_lift_rod_cmd = val;
    }

    void SetFrontFenderCmd(const uint8_t val)
    {
        _front_fender_cmd = val;
    }

    void SetShakeDustCmd(const uint8_t val)
    {
        _shake_dust_cmd = val;
    }

private:
    void _update_tgt_sweep_mode();
    void _update_sweep_cmd();
    void _update_dump_cmd();
    void _update_sweep_estop_cmd();
    void _update_brush_water_valve_cmd();
    void _update_fan_dust_fall_valve_cmd();
    void _update_suction_dust_fall_valve_cmd();
    void _update_dustbin_dust_fall_valve_cmd();
    void _update_roll_swp_water_valve_cmd();
    void _update_dustbin_clean_water_valve_cmd();
    void _update_water_boxlid_cmd();
    void _update_water_drain_valve_cmd();
    void _update_left_front_brush_abd_dist();
    void _update_right_front_brush_abd_dist();
    void _update_left_front_brush_extension_rod_cmd();
    void _update_right_front_brush_extension_rod_cmd();
    void _update_left_front_brush_lift_rod_cmd();
    void _update_right_front_brush_lift_rod_cmd();
    void _update_rear_brush_lift_rod_cmd();
    void _update_suction_lift_rod_cmd();
    void _update_main_brush_lift_rod_cmd();
    void _update_front_fender_cmd();
    void _update_shake_dust_Cmd();
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU154_HPP_
