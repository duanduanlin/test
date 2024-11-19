/*
 * @Author: hanson
 * @Date: 2024-08-29 15:15:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:17:08
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU215.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU215_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU215_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU215 : public BaseProtocol
{
private:
    /* data */
public:
    CCU215(/* args */) : BaseProtocol(0x215)
    {
    }
    ~CCU215() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_eps_work_mode(const uint64_t data, uint8_t *singal) const;
    void parse_steering_wheel_torque_nm(const uint64_t data, double *singal) const;
    void parse_front_whl_angle_deg(const uint64_t data, double *singal) const;
    void parse_angular_velocity_degps(const uint64_t data, double *singal) const;
    void parse_err_level(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU215_HPP_
