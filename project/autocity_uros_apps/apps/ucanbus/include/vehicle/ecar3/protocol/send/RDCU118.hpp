/*
 * @Author: hanson
 * @Date: 2024-08-28 11:11:25
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-30 14:24:22
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\send\RDCU118.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU118_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU118_HPP_
#include "protocol/BaseProtocol.hpp"

class RDCU118 : public BaseProtocol
{
public:
    enum Active
    {
        ACTIVE_DISABLE = 0,
        ACTIVE_ENABLE = 1,
    };

    enum RdcuDriveControlMode
    {
        RDCU_DRIVE_CONTROL_MODE_THROTTLE = 0,
        RDCU_DRIVE_CONTROL_MODE_SPEED = 1,
    };
    enum RdcuTargetGear
    {
        RDCU_TARGET_GEAR_N = 0,
        RDCU_TARGET_GEAR_D = 1,
        RDCU_TARGET_GEAR_R = 2,
    };

private:
    /* data */
    uint8_t _active;
    uint8_t _park_enable;     // 驻车使能
    uint8_t _drive_ctrl_mode; // 驱动模式
    uint8_t _tgt_gear;        // 目标挡位
    double _tgt_throttle;     // 驱动量
    double _tgt_brk;          // 制动量
    double _tgt_str_angle;    // 前轮转角

public:
    RDCU118(/* args */) : BaseProtocol(0x118)
    {
        ResetCmd();
    }
    ~RDCU118() = default;

    void UpdateCmd(uint64_t *data) override;
    void ResetCmd() override;

    void SetActive(const uint8_t val)
    {
        _active = val;
    }

    void SetParkEnable(const uint8_t val)
    {
        _park_enable = val;
    }

    void SetDriveCtrlMode(const uint8_t val)
    {
        _drive_ctrl_mode = val;
    }

    void SetTgtGear(const uint8_t val)
    {
        _tgt_gear = val;
    }

    void SetTgtThrottle(const double val)
    {
        _tgt_throttle = val;
    }

    void SetTgtBrk(const double val)
    {
        _tgt_brk = val;
    }

    void SetTgtStrAngle(const double val)
    {
        _tgt_str_angle = val;
    }

private:
    void _update_active();
    void _update_park_enable();
    void _update_drive_ctrl_mode();
    void _update_tgt_gear();
    void _update_tgt_throttle();
    void _update_tgt_brk();
    void _update_tgt_str_angle();
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU118_HPP_
