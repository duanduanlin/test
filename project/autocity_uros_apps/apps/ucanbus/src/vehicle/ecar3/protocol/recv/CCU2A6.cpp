/*
 * @Author: hanson
 * @Date: 2024-08-29 16:15:32
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:15:43
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU2A6.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU2A6.hpp"

void CCU2A6::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_vehvin_c8(data, &chassis_detail->GetEcar3Chassis()->ccu2a6_a_.ccu_vehvin_c8);
    parse_ccu_vehvin_c9(data, &chassis_detail->GetEcar3Chassis()->ccu2a6_a_.ccu_vehvin_c9);
    parse_ccu_vehvin_c10(data, &chassis_detail->GetEcar3Chassis()->ccu2a6_a_.ccu_vehvin_c10);
    parse_ccu_vehvin_c11(data, &chassis_detail->GetEcar3Chassis()->ccu2a6_a_.ccu_vehvin_c11);
    parse_ccu_vehvin_d12_17(data, &chassis_detail->GetEcar3Chassis()->ccu2a6_a_.ccu_vehvin_d12_17);
}

void CCU2A6::parse_ccu_vehvin_c8(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A6::parse_ccu_vehvin_c9(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A6::parse_ccu_vehvin_c10(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A6::parse_ccu_vehvin_c11(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A6::parse_ccu_vehvin_d12_17(const uint64_t data, double *singal) const
{
    uint64_t x = (data >> (Motorola(6, 48) - 0)) & 0xffffff;
    uint64_t a = ((uint64_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
