/*
 * @Author: hanson
 * @Date: 2024-08-29 15:17:17
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:17:27
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CCU215.cpp
 */
#include "vehicle/ecar3/protocol/recv/CCU215.hpp"

void CCU215::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_eps_work_mode(data, &chassis_detail->GetEcar3Chassis()->ccu215_a_.eps_work_mode);
    parse_steering_wheel_torque_nm(data, &chassis_detail->GetEcar3Chassis()->ccu215_a_.steering_wheel_torque_nm);
    parse_front_whl_angle_deg(data, &chassis_detail->GetEcar3Chassis()->ccu215_a_.front_whl_angle_deg);
    parse_angular_velocity_degps(data, &chassis_detail->GetEcar3Chassis()->ccu215_a_.angular_velocity_degps);
    parse_err_level(data, &chassis_detail->GetEcar3Chassis()->ccu215_a_.err_level);
}

void CCU215::parse_eps_work_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CCU215::parse_steering_wheel_torque_nm(const uint64_t data, double *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0xff;
    double m = 0;
    HexToDecimal(x, 0.1, -12.8, &m);
    *singal = m;
}
void CCU215::parse_front_whl_angle_deg(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> Motorola(3, 24)) & 0xffff;
    double m = 0;
    HexToDecimal(x, 0.005, -90, &m);
    *singal = m;
}
void CCU215::parse_angular_velocity_degps(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> Motorola(5, 40)) & 0xffff;
    double m = 0;
    HexToDecimal(x, 0.01, -180, &m);
    *singal = m;
}
void CCU215::parse_err_level(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 52)) & 0xf;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
