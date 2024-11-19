/*
 * @Author: hanson
 * @Date: 2024-08-28 14:29:43
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-30 17:05:25
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\send\RDCU155.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU155_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU155_HPP_

#include "protocol/BaseProtocol.hpp"

class RDCU155 : public BaseProtocol
{
public:
    enum RdcuFanControlModeType
    {
        RDCU_FAN_CTRL_MODE_GEAR = 0,
        RDCU_FAN_CTRL_MODE_SPEED = 1,
        RDCU_FAN_CTRL_MODE_DISABLE = 2,
    };
    enum RdcuFanGearType
    {
        RDCU_FAN_GEAR_MEDIUM = 0,  // 3000 rpm
        RDCU_FAN_GEAR_LOW = 1,     // 2800 rpm
        RDCU_FAN_GEAR_HIGH = 2,    // 3200 rpm
        RDCU_FAN_GEAR_NEUTRAL = 3, // stop
    };
    enum RdcuBrushMototCtrlModeType
    {
        RDCU_BRUSH_MTR_CTRL_MODE_GEAR = 0,
        RDCU_BRUSH_MTR_CTRL_MODE_SPEED = 1,
        RDCU_BRUSH_MTR_CTRL_MODE_DISABLE = 2,
    };

    enum RdcuBrushMotorGearType
    {
        RDCU_BRUSH_MOTOR_GEAR_MEDIUM = 0,  // 100rpm
        RDCU_BRUSH_MOTOR_GEAR_LOW = 1,     // 80rpm
        RDCU_BRUSH_MOTOR_GEAR_HIGH = 2,    // 120rpm
        RDCU_BRUSH_MOTOR_GEAR_DISABLE = 3, // disable
    };

    enum RdcuDustbinLiftAngleGearCmdType
    {                                           // 垃圾箱举升角度挡位控制指令
        RDCU_DUSTBIN_LIFT_ANGLE_GEAR_CMD_1 = 0, // 45°
        RDCU_DUSTBIN_LIFT_ANGLE_GEAR_CMD_2 = 1, // 25°
    };

    enum RdcuDustbinOverTurnCmdType
    {
        RDCU_DUSTBIN_OVERTURN_CMD_INVALID = 0, // 无效
        RDCU_DUSTBIN_OVERTURN_CMD_DUMP = 1,    // 倾倒
        RDCU_DUSTBIN_OVERTURN_CMD_RETRACT = 2, // 回缩
    };

    enum RdcuDustbinLiftDropCmdType
    {
        RDCU_DUSTBIN_LIFTDROP_CMD_INVALID = 0, // 无效
        RDCU_DUSTBIN_LIFTDROP_CMD_LIFT = 1,    // 举升
        RDCU_DUSTBIN_LIFTDROP_CMD_DROP = 2,    // 下降
    };

    enum RdcuDustbinDoorCmdType
    {
        RDCU_DUSTBIN_DOOR_CMD_INVALID = 0, // 无效
        RDCU_DUSTBIN_DOOR_CMD_OPEN = 1,    // 打开
        RDCU_DUSTBIN_DOOR_CMD_CLOSE = 2,   // 关闭
    };

    enum RdcuDustbinLockCmdType
    {
        RDCU_DUSTBIN_LOCK_CMD_INVALID = 0, // 无效
        RDCU_DUSTBIN_LOCK_CMD_UNLOCK = 1,  // 解锁
        RDCU_DUSTBIN_LOCK_CMD_LOCK = 2,    // 锁住
    };

private:
    /* data */
    uint8_t _dustbin_lock_cmd;            // 垃圾箱锁紧控制
    uint8_t _dustbin_door_cmd;            // 垃圾箱舱门控制
    uint8_t _dustbin_liftdrop_cmd;        // 垃圾箱举升控制
    uint8_t _dustbin_overturn_cmd;        // 垃圾箱翻转
    uint8_t _dustbin_lift_angle_gear_cmd; // 垃圾箱举升角度控制

    uint8_t _fan_cmd;                     // 风机开启
    uint8_t _left_front_brush_motor_cmd;  // 左前边刷电机控制
    uint8_t _right_front_brush_motor_cmd; // 右前边刷电机控制
    uint8_t _left_rear_brush_motor_cmd;   // 左后边刷电机控制
    uint8_t _right_rear_brush_motor_cmd;  // 右后边刷电机控制
    uint8_t _main_brush_motor_cmd;        // 滚刷电机控制

    uint8_t _fan_mode_cmd; // 风机控制模式
    uint8_t _fan_gear_cmd; // 风机转速挡位设置
    double _fan_speed_rpm; // 风机目标转速

    uint8_t _left_front_brush_motor_mode_cmd; // 左前边刷电机控制模式
    uint8_t _left_front_brush_motor_gear_cmd; // 左前边刷控制挡位
    double _left_front_brush_motor_spd_rpm;   // 左前边刷目标转速

    uint8_t _right_front_brush_motor_mode_cmd; // 右前边刷电机控制模式
    uint8_t _right_front_brush_motor_gear_cmd; // 右前边刷控制挡位
    double _right_front_brush_motor_spd_rpm;   // 右前边刷目标转速
public:
    RDCU155(/* args */) : BaseProtocol(0x155)
    {
        ResetCmd();
    }
    ~RDCU155() = default;

    void UpdateCmd(uint64_t *data) override;
    void ResetCmd() override;

    void SetDustbinLockCmd(const uint8_t val)
    {
        _dustbin_lock_cmd = val;
    }

    void SetDustbinDoorCmd(const uint8_t val)
    {
        _dustbin_door_cmd = val;
    }

    void SetDustbinLiftdropCmd(const uint8_t val)
    {
        _dustbin_liftdrop_cmd = val;
    }

    void SetDustbinOverturnCmd(const uint8_t val)
    {
        _dustbin_overturn_cmd = val;
    }

    void SetDustbinLiftAngleGearCmd(const uint8_t val)
    {
        _dustbin_lift_angle_gear_cmd = val;
    }

    void SetFanCmd(const uint8_t val)
    {
        _fan_cmd = val;
    }

    void SetLeftFrontBrushMotorCmd(const uint8_t val)
    {
        _left_front_brush_motor_cmd = val;
    }

    void SetRightFrontBrushMotorCmd(const uint8_t val)
    {
        _right_front_brush_motor_cmd = val;
    }

    void SetLeftRearBrushMotorCmd(const uint8_t val)
    {
        _left_rear_brush_motor_cmd = val;
    }

    void SetRightRearBrushMotorCmd(const uint8_t val)
    {
        _right_rear_brush_motor_cmd = val;
    }

    void SetMainBrushMotorCmd(const uint8_t val)
    {
        _main_brush_motor_cmd = val;
    }

    void SetFanModeCmd(const uint8_t val)
    {
        _fan_mode_cmd = val;
    }

    void SetFanGearCmd(const uint8_t val)
    {
        _fan_gear_cmd = val;
    }

    void SetFanSpeedRpm(const double val)
    {
        _fan_speed_rpm = val;
    }

    void SetLeftFrontBrushMotorModeCmd(const uint8_t val)
    {
        _left_front_brush_motor_mode_cmd = val;
    }

    void SetLeftFrontBrushMotorGearCmd(const uint8_t val)
    {
        _left_front_brush_motor_gear_cmd = val;
    }

    void SetLeftFrontBrushMotorSpdRpm(const double val)
    {
        _left_front_brush_motor_spd_rpm = val;
    }

    void SetRightFrontBrushMotorModeCmd(const uint8_t val)
    {
        _right_front_brush_motor_mode_cmd = val;
    }

    void SetRightFrontBrushMotorGearCmd(const uint8_t val)
    {
        _right_front_brush_motor_gear_cmd = val;
    }

    void SetRightFrontBrushMotorSpdRpm(const double val)
    {
        _right_front_brush_motor_spd_rpm = val;
    }

private:
    void _update_dustbin_lock_cmd();
    void _update_dustbin_door_cmd();
    void _update_dustbin_liftdrop_cmd();
    void _update_dustbin_overturn_cmd();
    void _update_dustbin_lift_angle_gear_cmd();

    void _update_fan_cmd();
    void _update_left_front_brush_motor_cmd();
    void _update_right_front_brush_motor_cmd();
    void _update_left_rear_brush_motor_cmd();
    void _update_right_rear_brush_motor_cmd();
    void _update_main_brush_motor_cmd();

    void _update_fan_mode_cmd();
    void _update_fan_gear_cmd();
    void _update_fan_speed_rpm();

    void _update_left_front_brush_motor_mode_cmd();
    void _update_left_front_brush_motor_gear_cmd();
    void _update_left_front_brush_motor_spd_rpm();

    void _update_right_front_brush_motor_mode_cmd();
    void _update_right_front_brush_motor_gear_cmd();
    void _update_right_front_brush_motor_spd_rpm();
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU155_HPP_
