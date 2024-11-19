/*
 * @Author: hanson
 * @Date: 2024-08-29 13:48:33
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:00:32
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU240.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU240.hpp"

void CCU240::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_vehicle_run_mode(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.vehicle_run_mode);
    parse_ccu_veh_runlockrsn(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_veh_runlockrsn);
    parse_err_level(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.err_level);
    parse_ccu_ftcrash_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_ftcrash_st);
    parse_ccu_rrcrash_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_rrcrash_st);
    parse_ccu_vehemgcyswh_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_vehemgcyswh_st);
    parse_ccu_lvbat_lowvolt(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_lvbat_lowvolt);
    parse_ccu_bat_lowsoc(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_bat_lowsoc);
    parse_ccu_bms_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_bms_errlevel);
    parse_ccu_mcu_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_mcu_errlevel);
    parse_ccu_ehb_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_ehb_errlevel);
    parse_ccu_eps_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_eps_errlevel);
    parse_ccu_epb_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_epb_errlevel);
    parse_ccu_siu_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_siu_errlevel);
    parse_ccu_lpdu_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_lpdu_errlevel);
    parse_ccu_tirepresralarm_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_tirepresralarm_st);
    parse_ccu_canbusoff_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_canbusoff_st);
    parse_ccu_segcodedispoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_segcodedispoffline_err);
    parse_ccu_leddispofflie_err(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_leddispofflie_err);
    parse_ccu_chginhibit_flt(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_chginhibit_flt);
    parse_ccu_pwrupinhibit_flt(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_pwrupinhibit_flt);
    parse_ccu_ademgcystop_st(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_ademgcystop_st);
    parse_ccu_vehemgcystop_reason(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_vehemgcystop_reason);
    parse_ccu_hpdu_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_hpdu_errlevel);
    parse_ccu_cbcu_errlevel(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_cbcu_errlevel);
    parse_ccu_veh_errcode(data, &chassis_detail->GetEcar3Chassis()->ccu240_a_.ccu_veh_errcode);
}

void CCU240::parse_vehicle_run_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_veh_runlockrsn(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_err_level(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_ftcrash_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_rrcrash_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_vehemgcyswh_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_lvbat_lowvolt(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_bat_lowsoc(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_bms_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_mcu_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_ehb_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_eps_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_epb_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_siu_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_lpdu_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_tirepresralarm_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_canbusoff_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_segcodedispoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_leddispofflie_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 38)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_chginhibit_flt(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 37)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_pwrupinhibit_flt(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 36)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_ademgcystop_st(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 35)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_vehemgcystop_reason(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 32)) & 0x7;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_hpdu_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_cbcu_errlevel(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU240::parse_ccu_veh_errcode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 40)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
