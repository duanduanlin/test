/*
 * @Author: hanson
 * @Date: 2024-08-29 15:12:29
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:13:36
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU211.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU211_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU211_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU211 : public BaseProtocol
{
private:
    /* data */
public:
    CCU211(/* args */) : BaseProtocol(0x211)
    {
    }
    ~CCU211() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_brake_work_mode(const uint64_t data, uint8_t *singal) const;
    void parse_brake_mode(const uint64_t data, uint8_t *singal) const;
    void parse_brake_pressure_bar(const uint64_t data, double *singal) const;
    void parse_brake_pedal_pos(const uint64_t data, double *singal) const;
    void parse_err_level(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU211_HPP_
