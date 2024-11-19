/*
 * @Author: hanson
 * @Date: 2024-08-29 15:09:54
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:10:15
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CBCU537.cpp
 */
#include "vehicle/ecar3/protocol/recv/CBCU537.hpp"

void CBCU537::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_remain_water(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.remain_water);
    parse_dustbin_pose_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_pose_status);
    parse_dustbin_lock_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_lock_status);
    parse_dustbin_door_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_door_status);
    parse_dustbin_lift_pose_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_lift_pose_status);
    parse_dustbin_overturn_pose_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_overturn_pose_status);
    parse_dustbin_lift_angle_gear_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_lift_angle_gear_status);
    parse_dustbin_full_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_full_status);
    parse_sweep_lamp_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.sweep_lamp_status);
    parse_dustbin_sater_lvl_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dustbin_sater_lvl_status);
    parse_dump_status(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.dump_status);
    parse_brush_motor1_speed_rpm(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.brush_motor1_speed_rpm);
    parse_brush_motor2_speed_rpm(data, &chassis_detail->GetEcar3Chassis()->cbcu537_a_.brush_motor2_speed_rpm);
}

void CBCU537::parse_remain_water(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(0, 0) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_pose_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_lock_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_door_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_lift_pose_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_overturn_pose_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_lift_angle_gear_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_full_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 21)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_sweep_lamp_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dustbin_sater_lvl_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_dump_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU537::parse_brush_motor1_speed_rpm(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(4, 32) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 5, 0, &m);
    *singal = m;
}
void CBCU537::parse_brush_motor2_speed_rpm(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> (Motorola(5, 40) - 0)) & 0xff;
    uint8_t a = ((uint8_t)(x)) >> 0;
    double m = 0;
    HexToDecimal(a, 5, 0, &m);
    *singal = m;
}
