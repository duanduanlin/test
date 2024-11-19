/*
 * @Author: hanson
 * @Date: 2024-08-29 14:48:51
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:50:17
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU250.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU250.hpp"

void CCU250::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_speed_kmph(data, &chassis_detail->GetEcar3Chassis()->ccu250_a_.speed_kmph);
    parse_a_mpps(data, &chassis_detail->GetEcar3Chassis()->ccu250_a_.a_mpps);
    parse_motion_curvature(data, &chassis_detail->GetEcar3Chassis()->ccu250_a_.motion_curvature);
    parse_run_direction(data, &chassis_detail->GetEcar3Chassis()->ccu250_a_.run_direction);
}

void CCU250::parse_speed_kmph(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(3, 24) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.00390625, 0, &m);
    *singal = m;
}
void CCU250::parse_a_mpps(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> Motorola(1, 8)) & 0xffff;
    double m = 0;
    HexToDecimal(x, 0.01, -40, &m);
    *singal = m;
}
void CCU250::parse_motion_curvature(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> Motorola(5, 40)) & 0xffff;
    double m = 0;
    HexToDecimal(x, 0.0001, -3, &m);
    *singal = m;
}
void CCU250::parse_run_direction(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
