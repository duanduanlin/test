/*
 * @Author: hanson
 * @Date: 2024-08-29 15:20:45
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:21:01
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU213.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU213.hpp"

void CCU213::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_park_work_mode(data, &chassis_detail->GetEcar3Chassis()->ccu213_a_.park_work_mode);
    parse_park_status(data, &chassis_detail->GetEcar3Chassis()->ccu213_a_.park_status);
    parse_park_release_swh_status(data, &chassis_detail->GetEcar3Chassis()->ccu213_a_.park_release_swh_status);
    parse_err_level(data, &chassis_detail->GetEcar3Chassis()->ccu213_a_.err_level);
}

void CCU213::parse_park_work_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU213::parse_park_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU213::parse_park_release_swh_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 1)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU213::parse_err_level(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
