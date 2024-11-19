/*
 * @Author: hanson
 * @Date: 2024-08-29 15:55:17
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:56:34
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU261.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU261.hpp"

void CCU261::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_powercmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_powercmdperd_err);
    parse_ccu_powercmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_powercmddrop_err);
    parse_ccu_powercmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_powercmdchksum_err);
    parse_ccu_powercmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_powercmdoffline_err);
    parse_ccu_pdumsgperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_pdumsgperd_err);
    parse_ccu_pdumsgdrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_pdumsgdrop_err);
    parse_ccu_pdumsgchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_pdumsgchksum_err);
    parse_ccu_pdumsgoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_pdumsgoffline_err);
    parse_ccu_chas12v_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_chas12v_err);
    parse_ccu_ad12v1_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ad12v1_err);
    parse_ccu_ad12v2_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ad12v2_err);
    parse_ccu_ad24v_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ad24v_err);
    parse_ccu_ccupwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ccupwrsupply_err);
    parse_ccu_bmspwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_bmspwrsupply_err);
    parse_ccu_ehbpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ehbpwrsupply_err);
    parse_ccu_epspwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_epspwrsupply_err);
    parse_ccu_siupwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_siupwrsupply_err);
    parse_ccu_epbpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_epbpwrsupply_err);
    parse_ccu_tpmspwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_tpmspwrsupply_err);
    parse_ccu_datarecpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_datarecpwrsupply_err);
    parse_ccu_emgcyrmtpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_emgcyrmtpwrsupply_err);
    parse_ccu_mcuwakeup_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_mcuwakeup_err);
    parse_ccu_bmswakeup_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_bmswakeup_err);
    parse_ccu_ehbwakeup_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_ehbwakeup_err);
    parse_ccu_epswakeup_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_epswakeup_err);
    parse_ccu_epbwakeup_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_epbwakeup_err);
    parse_ccu_rsrvdwakeup1_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_rsrvdwakeup1_err);
    parse_ccu_rsrvdwakeup2_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_rsrvdwakeup2_err);
    parse_ccu_rsrvdwakeup3_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_rsrvdwakeup3_err);
    parse_ccu_rsrvdwakeup4_err(data, &chassis_detail->GetEcar3Chassis()->ccu261_a_.ccu_rsrvdwakeup4_err);
}

void CCU261::parse_ccu_powercmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_powercmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_powercmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_powercmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_pdumsgperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_pdumsgdrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_pdumsgchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 1)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_pdumsgoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_chas12v_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ad12v1_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ad12v2_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ad24v_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ccupwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_bmspwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ehbpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_epspwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_siupwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 27)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_epbpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_tpmspwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 25)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_datarecpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_emgcyrmtpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_mcuwakeup_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 35)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_bmswakeup_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 34)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_ehbwakeup_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 33)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_epswakeup_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 32)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_epbwakeup_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 47)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_rsrvdwakeup1_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 46)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_rsrvdwakeup2_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 45)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_rsrvdwakeup3_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 44)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU261::parse_ccu_rsrvdwakeup4_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 43)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
