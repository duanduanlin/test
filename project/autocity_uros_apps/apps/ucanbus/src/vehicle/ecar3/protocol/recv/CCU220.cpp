/*
 * @Author: hanson
 * @Date: 2024-08-29 15:52:08
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:52:19
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU220.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU220.hpp"

void CCU220::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_bodycmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_bodycmdperd_err);
    parse_ccu_bodycmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_bodycmddrop_err);
    parse_ccu_bodycmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_bodycmdchksum_err);
    parse_ccu_bodycmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_bodycmdoffline_err);
    parse_ccu_headlamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_headlamp_err);
    parse_ccu_turnllamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_turnllamp_err);
    parse_ccu_turnrlamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_turnrlamp_err);
    parse_ccu_backlamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_backlamp_err);
    parse_ccu_buzzer_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_buzzer_err);
    parse_ccu_runlamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_runlamp_err);
    parse_ccu_brklamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_brklamp_err);
    parse_ccu_foglamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_foglamp_err);
    parse_ccu_horn_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_horn_err);
    parse_ccu_widthlamp_err(data, &chassis_detail->GetEcar3Chassis()->ccu220_a_.ccu_widthlamp_err);
}

void CCU220::parse_ccu_bodycmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_bodycmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_bodycmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_bodycmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_headlamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_turnllamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_turnrlamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_backlamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_buzzer_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_runlamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_brklamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_foglamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_horn_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU220::parse_ccu_widthlamp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
