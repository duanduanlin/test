/*
 * @Author: hanson
 * @Date: 2024-08-29 14:54:49
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:56:16
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU254.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU254.hpp"

void CCU254::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_totaltrip_meter(data, &chassis_detail->GetEcar3Chassis()->ccu254_a_.ccu_totaltrip_meter);
    parse_ccu_remain_mileage(data, &chassis_detail->GetEcar3Chassis()->ccu254_a_.ccu_remain_mileage);
    parse_ccu_totalodo_meter(data, &chassis_detail->GetEcar3Chassis()->ccu254_a_.ccu_totalodo_meter);
}

void CCU254::parse_ccu_totaltrip_meter(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(1, 8) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.1, 0, &m);
    *singal = m;
}
void CCU254::parse_ccu_remain_mileage(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(2, 16) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
void CCU254::parse_ccu_totalodo_meter(const uint64_t data, double *singal) const
{
    uint64_t x = (data >> (Motorola(5, 40) - 0)) & 0xffffff;
    uint64_t a = ((uint64_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.1, 0, &m);
    *singal = m;
}
