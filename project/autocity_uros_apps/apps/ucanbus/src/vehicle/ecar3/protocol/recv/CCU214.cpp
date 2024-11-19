/*
 * @Author: hanson
 * @Date: 2024-08-29 15:37:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:38:52
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU214.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU214.hpp"

void CCU214::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_prkcmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_prkcmdperd_err);
    parse_ccu_prkcmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_prkcmddrop_err);
    parse_ccu_prkcmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_prkcmdchksum_err);
    parse_ccu_prkcmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_prkcmdoffline_err);
    parse_ccu_prkcmdoverrge_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_prkcmdoverrge_err);
    parse_ccu_epbmsgperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbmsgperd_err);
    parse_ccu_epbmsgdrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbmsgdrop_err);
    parse_ccu_epbmsgchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbmsgchksum_err);
    parse_ccu_epbmsgoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbmsgoffline_err);
    parse_ccu_epbparkinvalid_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbparkinvalid_err);
    parse_ccu_epbenablefeedback_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbenablefeedback_err);
    parse_ccu_epbovervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbovervolt_err);
    parse_ccu_epbundervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbundervolt_err);
    parse_ccu_epbrelay_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbrelay_err);
    parse_ccu_epbcancom_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbcancom_err);
    parse_ccu_epbleftlockingact_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbleftlockingact_err);
    parse_ccu_epbrightlockingact_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbrightlockingact_err);
    parse_ccu_epbleftunlockingact_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbleftunlockingact_err);
    parse_ccu_epbrightunlockingact_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbrightunlockingact_err);
    parse_ccu_epbfallback_warning(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbfallback_warning);
    parse_ccu_epbprotectoff_active(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbprotectoff_active);
    parse_ccu_epbmtroffcurt_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbmtroffcurt_err);
    parse_ccu_epbtempsenor_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbtempsenor_err);
    parse_ccu_epbovertemplevel1_warning(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbovertemplevel1_warning);
    parse_ccu_epbovertemplevel2_warning(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbovertemplevel2_warning);
    parse_ccu_epbwakeuphw_err(data, &chassis_detail->GetEcar3Chassis()->ccu214_a_.ccu_epbwakeuphw_err);
}

void CCU214::parse_ccu_prkcmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_prkcmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_prkcmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_prkcmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_prkcmdoverrge_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbmsgperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbmsgdrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbmsgchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbmsgoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbparkinvalid_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbenablefeedback_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbovervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 21)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbundervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbrelay_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbcancom_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbleftlockingact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbrightlockingact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbleftunlockingact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbrightunlockingact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbfallback_warning(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbprotectoff_active(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbmtroffcurt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 27)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbtempsenor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbovertemplevel1_warning(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 25)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbovertemplevel2_warning(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU214::parse_ccu_epbwakeuphw_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
