/*
 * @Author: hanson
 * @Date: 2024-08-29 15:19:22
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:19:29
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU213.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU213_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU213_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU213 : public BaseProtocol
{
private:
    /* data */
public:
    CCU213(/* args */) : BaseProtocol(0x213)
    {
    }
    ~CCU213() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_park_work_mode(const uint64_t data, uint8_t *singal) const;
    void parse_park_status(const uint64_t data, uint8_t *singal) const;
    void parse_park_release_swh_status(const uint64_t data, uint8_t *singal) const;
    void parse_err_level(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU213_HPP_
