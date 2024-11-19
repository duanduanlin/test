/*
 * @Author: hanson
 * @Date: 2024-08-29 15:41:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:41:20
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU216.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU216.hpp"

void CCU216::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_strcmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_strcmdperd_err);
    parse_ccu_strcmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_strcmddrop_err);
    parse_ccu_strcmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_strcmdchksum_err);
    parse_ccu_strcmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_strcmdoffline_err);
    parse_ccu_strcmdoverrge_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_strcmdoverrge_err);
    parse_ccu_epsmsgperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsmsgperd_err);
    parse_ccu_epsmsgdrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsmsgdrop_err);
    parse_ccu_epsmsgchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsmsgchksum_err);
    parse_ccu_epsmsgoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsmsgoffline_err);
    parse_ccu_epsworkmode_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsworkmode_err);
    parse_ccu_epsstrangle_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.ccu_epsstrangle_err);
    parse_eps_ecuovervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_ecuovervolt_err);
    parse_eps_ecuundervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_ecuundervolt_err);
    parse_eps_mtrovercurt_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_mtrovercurt_err);
    parse_eps_ecuovertemp_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_ecuovertemp_err);
    parse_eps_mtrovertemp_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_mtrovertemp_err);
    parse_eps_anglesensor_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_anglesensor_err);
    parse_eps_anglealignm_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_anglealignm_err);
    parse_eps_strmtr_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_strmtr_err);
    parse_eps_cancom_err(data, &chassis_detail->GetEcar3Chassis()->ccu216_a_.eps_cancom_err);
}

void CCU216::parse_ccu_strcmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_strcmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_strcmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_strcmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_strcmdoverrge_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsmsgperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsmsgdrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsmsgchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsmsgoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsworkmode_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_ccu_epsstrangle_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_ecuovervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_ecuundervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_mtrovercurt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_ecuovertemp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_mtrovertemp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 21)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_anglesensor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_anglealignm_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_strmtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU216::parse_eps_cancom_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
