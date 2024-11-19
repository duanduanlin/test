/*
 * @Author: hanson
 * @Date: 2024-08-29 16:10:55
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:11:07
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU2A5.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU2A5.hpp"

void CCU2A5::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_vehvin_c1(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c1);
    parse_ccu_vehvin_c2(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c2);
    parse_ccu_vehvin_c3(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c3);
    parse_ccu_vehvin_c4(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c4);
    parse_ccu_vehvin_c5(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c5);
    parse_ccu_vehvin_c6(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c6);
    parse_ccu_vehvin_c7(data, &chassis_detail->GetEcar3Chassis()->ccu2a5_a_.ccu_vehvin_c7);
}

void CCU2A5::parse_ccu_vehvin_c1(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c2(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c3(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c4(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c5(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 32)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c6(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 40)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU2A5::parse_ccu_vehvin_c7(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 48)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
