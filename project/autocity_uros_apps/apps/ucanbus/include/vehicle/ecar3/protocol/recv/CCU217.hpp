/*
 * @Author: hanson
 * @Date: 2024-08-29 14:40:17
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:41:57
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU217.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU217_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU217_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU217 : public BaseProtocol
{
private:
    /* data */
public:
    CCU217(/* args */) : BaseProtocol(0x217)
    {
    }
    ~CCU217() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_mcu_work_mode(const uint64_t data, uint8_t *singal) const;
    void parse_gear(const uint64_t data, uint8_t *singal) const;
    void parse_run_direction(const uint64_t data, uint8_t *singal) const;
    void parse_throttle(const uint64_t data, double *singal) const;
    void parse_mcu_current(const uint64_t data, double *singal) const;
    void parse_motor_speed_rpm(const uint64_t data, double *singal) const;
    void parse_err_level(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU217_HPP_
