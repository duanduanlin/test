/*
 * @Author: hanson
 * @Date: 2024-08-29 14:42:53
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:44:35
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU217.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU217.hpp"

void CCU217::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_mcu_work_mode(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.mcu_work_mode);
    parse_gear(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.gear);
    parse_run_direction(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.run_direction);
    parse_throttle(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.throttle);
    parse_mcu_current(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.mcu_current);
    parse_motor_speed_rpm(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.motor_speed_rpm);
    parse_err_level(data, &chassis_detail->GetEcar3Chassis()->ccu217_a_.err_level);
}

void CCU217::parse_mcu_work_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU217::parse_gear(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU217::parse_run_direction(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU217::parse_throttle(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(1, 8) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.4, 0, &m);
    *singal = m;
}
void CCU217::parse_mcu_current(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(3, 24) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 0.1, 0, &m);
    *singal = m;
}
void CCU217::parse_motor_speed_rpm(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(5, 40) - 0)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
void CCU217::parse_err_level(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
