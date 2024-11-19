/*
 * @Author: hanson
 * @Date: 2024-08-29 16:02:25
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:02:32
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU252.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU252_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU252_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU252 : public BaseProtocol
{
private:
    /* data */
public:
    CCU252(/* args */) : BaseProtocol(0x252)
    {
    }
    ~CCU252() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_left_rear_whl_speed_kmph(const uint64_t data, double *singal) const;
    void parse_right_rear_whl_speed_kmph(const uint64_t data, double *singal) const;
    void parse_left_rear_whl_validity(const uint64_t data, uint8_t *singal) const;
    void parse_right_rear_whl_validity(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU252_HPP_
