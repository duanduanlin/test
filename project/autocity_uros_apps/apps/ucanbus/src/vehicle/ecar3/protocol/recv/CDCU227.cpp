/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 18:31:49
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CDCU227.cpp
 */
#include "vehicle/ecar3/protocol/recv/CDCU227.hpp"

void CDCU227::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_wireless_chg_coupling_status(data, &chassis_detail->GetEcar3Chassis()->cdcu227_a_.wireless_chg_coupling_status);
    parse_wireless_charging_status(data, &chassis_detail->GetEcar3Chassis()->cdcu227_a_.wireless_charging_status);
}

void CDCU227::parse_wireless_chg_coupling_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CDCU227::parse_wireless_charging_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
