/*
 * @Author: hanson
 * @Date: 2024-08-29 16:03:37
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:03:48
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU252.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU252.hpp"

void CCU252::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_left_rear_whl_speed_kmph(data, &chassis_detail->GetEcar3Chassis()->ccu252_a_.left_rear_whl_speed_kmph);
    parse_right_rear_whl_speed_kmph(data, &chassis_detail->GetEcar3Chassis()->ccu252_a_.right_rear_whl_speed_kmph);
    parse_left_rear_whl_validity(data, &chassis_detail->GetEcar3Chassis()->ccu252_a_.left_rear_whl_validity);
    parse_right_rear_whl_validity(data, &chassis_detail->GetEcar3Chassis()->ccu252_a_.right_rear_whl_validity);
}
void CCU252::parse_left_rear_whl_speed_kmph(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(1, 8) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.01, 0, &m);
    *singal = m;
}
void CCU252::parse_right_rear_whl_speed_kmph(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(3, 24) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.01, 0, &m);
    *singal = m;
}
void CCU252::parse_left_rear_whl_validity(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 55)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU252::parse_right_rear_whl_validity(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
