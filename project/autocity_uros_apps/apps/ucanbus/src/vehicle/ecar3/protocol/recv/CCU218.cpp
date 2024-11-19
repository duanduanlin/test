/*
 * @Author: hanson
 * @Date: 2024-08-29 15:49:00
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:50:14
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU218.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU218.hpp"

void CCU218::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_ccu_drvcmdperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_drvcmdperd_err);
    parse_ccu_drvcmddrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_drvcmddrop_err);
    parse_ccu_drvcmdchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_drvcmdchksum_err);
    parse_ccu_drvcmdoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_drvcmdoffline_err);
    parse_ccu_drvcmdoverrge_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_drvcmdoverrge_err);
    parse_ccu_mcumsgperd_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumsgperd_err);
    parse_ccu_mcumsgdrop_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumsgdrop_err);
    parse_ccu_mcumsgchksum_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumsgchksum_err);
    parse_ccu_mcumsgoffline_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumsgoffline_err);
    parse_ccu_mcumainpwrcur_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumainpwrcur_err);
    parse_ccu_mcucurtsensor_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcucurtsensor_err);
    parse_ccu_mcuprechg_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcuprechg_err);
    parse_ccu_mcupwrovervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcupwrovervolt_err);
    parse_ccu_mcupwrundervolt_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcupwrundervolt_err);
    parse_ccu_mcupwrovercurt_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcupwrovercurt_err);
    parse_ccu_mcuovertemp_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcuovertemp_err);
    parse_ccu_mcucancom_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcucancom_err);
    parse_ccu_mcumtrovertemp_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumtrovertemp_err);
    parse_ccu_mcumtrphase_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumtrphase_err);
    parse_ccu_mcuencoder_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcuencoder_err);
    parse_ccu_mcumtrblock_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumtrblock_err);
    parse_ccu_mcuenable_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcuenable_err);
    parse_ccu_mcuthortact_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcuthortact_err);
    parse_ccu_mcumtrspdact_err(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcumtrspdact_err);
    parse_ccu_mcu_errcode(data, &chassis_detail->GetEcar3Chassis()->ccu218_a_.ccu_mcu_errcode);
}

void CCU218::parse_ccu_drvcmdperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_drvcmddrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_drvcmdchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_drvcmdoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_drvcmdoverrge_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumsgperd_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumsgdrop_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumsgchksum_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumsgoffline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumainpwrcur_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 23)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcucurtsensor_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcuprechg_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 21)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcupwrovervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcupwrundervolt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcupwrovercurt_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcuovertemp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcucancom_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumtrovertemp_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumtrphase_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcuencoder_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumtrblock_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcuenable_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 25)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcuthortact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcumtrspdact_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU218::parse_ccu_mcu_errcode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 40)) & 0xff;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
