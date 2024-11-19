#include "vehicle/ecar3/protocol/recv/CCU222.hpp"

void CCU222::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_lvbat_volt(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_lvbat_volt);
    parse_ccu_bms_vehbatsoc(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_vehbatsoc);
    parse_ccu_bms_batsoh(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_batsoh);
    parse_ccu_bms_batvolt(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_batvolt);
    parse_ccu_bms_batcurt(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_batcurt);
    parse_ccu_bms_battemp(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_battemp);
    parse_ccu_bms_chgst(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_chgst);
    parse_ccu_bms_dischgst(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_dischgst);
    parse_ccu_bms_feedbackst(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_feedbackst);
    parse_ccu_bms_chgconnectst(data, &chassis_detail->GetEcar3Chassis()->ccu222_a_.ccu_bms_chgconnectst);
}

void CCU222::parse_ccu_lvbat_volt(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(0, 0) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.1, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_vehbatsoc(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(1, 8) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.4, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_batsoh(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(2, 16) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.4, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_batvolt(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(3, 24) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.4, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_batcurt(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(4, 32) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_battemp(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> Motorola(5, 40)) & 0xff;
    double m = 0;
    HexToDecimal(x, 1, -50, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_chgst(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 55)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_dischgst(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_feedbackst(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 53)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU222::parse_ccu_bms_chgconnectst(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
