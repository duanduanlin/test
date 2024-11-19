/*
 * @Author: hanson
 * @Date: 2024-08-29 15:08:40
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:31:28
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CBCU537.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU537_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU537_HPP_

#include "protocol/BaseProtocol.hpp"

class CBCU537 : public BaseProtocol
{
private:
    /* data */
public:
    CBCU537(/* args */) : BaseProtocol(0x537)
    {
    }
    ~CBCU537() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_remain_water(const uint64_t data, double *singal) const;
    void parse_dustbin_pose_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_lock_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_door_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_lift_pose_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_overturn_pose_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_lift_angle_gear_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_full_status(const uint64_t data, uint8_t *singal) const;
    void parse_sweep_lamp_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_sater_lvl_status(const uint64_t data, uint8_t *singal) const;
    void parse_dump_status(const uint64_t data, uint8_t *singal) const;
    void parse_brush_motor1_speed_rpm(const uint64_t data, double *singal) const;
    void parse_brush_motor2_speed_rpm(const uint64_t data, double *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU537_HPP_
