/*
 * @Author: hanson
 * @Date: 2024-08-28 11:45:42
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 13:42:33
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\send\RDCU119.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU119_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU119_HPP_

#include "protocol/BaseProtocol.hpp"

class RDCU119 : public BaseProtocol
{
private:
    /* data */
    uint8_t _width_lamp_cmd;        // 示廓灯
    uint8_t _brake_lamp_cmd;        // 制动灯
    uint8_t _fog_lamp_cmd;          // 雾灯
    uint8_t _head_lamp_cmd;         // 前大灯
    uint8_t _double_flash_lamp_cmd; // 双闪
    uint8_t _left_turn_lamp_cmd;    // 左转向灯
    uint8_t _right_turn_lamp_cmd;   // 右转向灯
    uint8_t _back_lamp_cmd;         // 倒车灯
    uint8_t _buzzer_cmd;            // 蜂鸣器
    uint8_t _horn_cmd;              // 喇叭
    uint8_t _run_lamp_cmd;          // 日行灯

public:
    RDCU119(/* args */) : BaseProtocol(0x119)
    {
        ResetCmd();
    }
    ~RDCU119() = default;

    void UpdateCmd(uint64_t *data) override;
    void ResetCmd() override;

    void SetWidthLampCmd(const uint8_t val)
    {
        _width_lamp_cmd = val;
    }

    void SetBrakeLampCmd(const uint8_t val)
    {
        _brake_lamp_cmd = val;
    }

    void SetFogLampCmd(const uint8_t val)
    {
        _fog_lamp_cmd = val;
    }

    void SetHeadLampCmd(const uint8_t val)
    {
        _head_lamp_cmd = val;
    }

    void SetDoubleFlashLampCmd(const uint8_t val)
    {
        _double_flash_lamp_cmd = val;
    }

    void SetLeftTurnLampCmd(const uint8_t val)
    {
        _left_turn_lamp_cmd = val;
    }

    void SetRightTurnLampCmd(const uint8_t val)
    {
        _right_turn_lamp_cmd = val;
    }

    void SetBackLampCmd(const uint8_t val)
    {
        _back_lamp_cmd = val;
    }

    void SetBuzzerCmd(const uint8_t val)
    {
        _buzzer_cmd = val;
    }

    void SetHornCmd(const uint8_t val)
    {
        _horn_cmd = val;
    }

    void SetRunLampCmd(const uint8_t val)
    {
        _run_lamp_cmd = val;
    }

private:
    void _update_width_lamp_cmd();
    void _update_brake_lamp_cmd();
    void _update_fog_lamp_cmd();
    void _update_head_lamp_cmd();
    void _update_double_flash_lamp_cmd();
    void _update_left_turn_lamp_cmd();
    void _update_right_turn_lamp_cmd();
    void _update_back_lamp_cmd();
    void _update_buzzer_cmd();
    void _update_horn_cmd();
    void _update_run_lamp_cmd();
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU119_HPP_
