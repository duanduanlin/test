/*
 * @Author: hanson
 * @Date: 2024-08-29 16:05:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:06:36
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU251.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU251_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU251_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU251 : public BaseProtocol
{
private:
    /* data */
public:
    CCU251(/* args */) : BaseProtocol(0x251)
    {
    }
    ~CCU251() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_left_front_whl_speed_kmph(const uint64_t data, double *singal) const;
    void parse_right_front_whl_speed_kmph(const uint64_t data, double *singal) const;
    void parse_left_front_whl_validity(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_whl_validity(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU251_HPP_
