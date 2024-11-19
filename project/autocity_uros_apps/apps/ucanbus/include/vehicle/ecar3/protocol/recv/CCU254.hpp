/*
 * @Author: hanson
 * @Date: 2024-08-29 14:53:02
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 14:54:16
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU254.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU254_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU254_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU254 : public BaseProtocol
{
private:
    /* data */
public:
    CCU254(/* args */) : BaseProtocol(0x254)
    {
    }
    ~CCU254() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_totaltrip_meter(const uint64_t data, double *singal) const;
    void parse_ccu_remain_mileage(const uint64_t data, double *singal) const;
    void parse_ccu_totalodo_meter(const uint64_t data, double *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU254_HPP_
