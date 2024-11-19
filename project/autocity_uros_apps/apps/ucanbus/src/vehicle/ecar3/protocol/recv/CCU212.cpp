/*
 * @Author: hanson
 * @Date: 2024-08-29 15:24:28
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:25:47
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU212.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU212.hpp"

void CCU212::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_brkcmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkcmdperd_err);
    parse_ccu_brkcmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkcmddrop_err);
    parse_ccu_brkcmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkcmdchksum_err);
    parse_ccu_brkcmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkcmdoffline_err);
    parse_ccu_brkcmdoverrge_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkcmdoverrge_err);
    parse_ccu_ehbmsgperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbmsgperd_err);
    parse_ccu_ehbmsgdrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbmsgdrop_err);
    parse_ccu_ehbmsgchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbmsgchksum_err);
    parse_ccu_ehbmsgoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbmsgoffline_err);
    parse_ccu_brkfldlack_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkfldlack_err);
    parse_ccu_ehbcurtsenor_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbcurtsenor_err);
    parse_ccu_ehbtempsenor_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbtempsenor_err);
    parse_ccu_ehbovertemp_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbovertemp_err);
    parse_ccu_brkpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkpwrsupply_err);
    parse_ccu_brkpresrsenor_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_brkpresrsenor_err);
    parse_ccu_ehbpwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpwrsupply_err);
    parse_ccu_ecupwrsupply_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ecupwrsupply_err);
    parse_ccu_drvbridge_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_drvbridge_err);
    parse_ccu_drvmtr_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_drvmtr_err);
    parse_ccu_ehbcan_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbcan_err);
    parse_ccu_ehbpwrswh_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpwrswh_err);
    parse_ccu_ehbweeping_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbweeping_err);
    parse_ccu_ehbpresfolw_alarm(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpresfolw_alarm);
    parse_ccu_ehbpresctrlvib_alarm(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpresctrlvib_alarm);
    parse_ccu_ehbtempsenor_alarm(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbtempsenor_alarm);
    parse_ccu_ehbworkmode_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbworkmode_err);
    parse_ccu_ehbbrkpres_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbbrkpres_err);
    parse_ccu_ehbpresfolw_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpresfolw_err);
    parse_ccu_ehbpresctrlvib_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbpresctrlvib_err);
    parse_ccu_ehbloadmismatch_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbloadmismatch_err);
    parse_ccu_ehbovercurt_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbovercurt_err);
    parse_ccu_ehbbrkcmdabnormal_err(data, &chassis_detail->GetEcar3Chassis()->ccu212_a_.ccu_ehbbrkcmdabnormal_err);
}

void CCU212::parse_ccu_brkcmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkcmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkcmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkcmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkcmdoverrge_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbmsgperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbmsgdrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbmsgchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbmsgoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkfldlack_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbcurtsenor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbtempsenor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 21)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbovertemp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_brkpresrsenor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ecupwrsupply_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_drvbridge_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_drvmtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbcan_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpwrswh_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbweeping_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 27)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpresfolw_alarm(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpresctrlvib_alarm(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 25)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbtempsenor_alarm(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbworkmode_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbbrkpres_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 38)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpresfolw_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 37)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbpresctrlvib_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 36)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbloadmismatch_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 35)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbovercurt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 34)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU212::parse_ccu_ehbbrkcmdabnormal_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 33)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
