/*
 * @Author: hanson
 * @Date: 2024-08-29 16:00:03
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:00:13
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU219.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU219.hpp"

void CCU219::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_acostoptic_work_mode(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.acostoptic_work_mode);
    parse_head_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.head_lamp);
    parse_double_flash(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.double_flash);
    parse_left_turn_light(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.left_turn_light);
    parse_right_turn_light(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.right_turn_light);
    parse_back_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.back_lamp);
    parse_buzzer(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.buzzer);
    parse_horn(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.horn);
    parse_run_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.run_lamp);
    parse_brake_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.brake_lamp);
    parse_fog_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.fog_lamp);
    parse_width_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.width_lamp);
    parse_wiper(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.wiper);
    parse_warn_lamp(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.warn_lamp);
    parse_flood_light(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.flood_light);
    parse_siren(data, &chassis_detail->GetEcar3Chassis()->ccu219_a_.siren);
}

void CCU219::parse_acostoptic_work_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_head_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_double_flash(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_left_turn_light(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_right_turn_light(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_back_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_buzzer(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_horn(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_run_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_brake_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_fog_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_width_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_wiper(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_warn_lamp(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_flood_light(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU219::parse_siren(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 27)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
