/*
 * @Author: hanson
 * @Date: 2024-08-29 15:13:46
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:15:03
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU211.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU211.hpp"

void CCU211::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_brake_work_mode(data, &chassis_detail->GetEcar3Chassis()->ccu211_a_.brake_work_mode);
    parse_brake_mode(data, &chassis_detail->GetEcar3Chassis()->ccu211_a_.brake_mode);
    parse_brake_pressure_bar(data, &chassis_detail->GetEcar3Chassis()->ccu211_a_.brake_pressure_bar);
    parse_brake_pedal_pos(data, &chassis_detail->GetEcar3Chassis()->ccu211_a_.brake_pedal_pos);
    parse_err_level(data, &chassis_detail->GetEcar3Chassis()->ccu211_a_.err_level);
}

void CCU211::parse_brake_work_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU211::parse_brake_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU211::parse_brake_pressure_bar(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(1, 8) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
void CCU211::parse_brake_pedal_pos(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(2, 16) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.4, 0, &m);
    *singal = m;
}
void CCU211::parse_err_level(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
