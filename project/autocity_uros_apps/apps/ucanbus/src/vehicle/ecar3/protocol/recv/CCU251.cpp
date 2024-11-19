/*
 * @Author: hanson
 * @Date: 2024-08-29 16:06:22
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:06:32
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU251.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU251.hpp"

void CCU251::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_left_front_whl_speed_kmph(data, &chassis_detail->GetEcar3Chassis()->ccu251_a_.left_front_whl_speed_kmph);
    parse_right_front_whl_speed_kmph(data, &chassis_detail->GetEcar3Chassis()->ccu251_a_.right_front_whl_speed_kmph);
    parse_left_front_whl_validity(data, &chassis_detail->GetEcar3Chassis()->ccu251_a_.left_front_whl_validity);
    parse_right_front_whl_validity(data, &chassis_detail->GetEcar3Chassis()->ccu251_a_.right_front_whl_validity);
}

void CCU251::parse_left_front_whl_speed_kmph(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(1, 8) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.01, 0, &m);
    *singal = m;
}
void CCU251::parse_right_front_whl_speed_kmph(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(3, 24) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.01, 0, &m);
    *singal = m;
}
void CCU251::parse_left_front_whl_validity(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 55)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU251::parse_right_front_whl_validity(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
