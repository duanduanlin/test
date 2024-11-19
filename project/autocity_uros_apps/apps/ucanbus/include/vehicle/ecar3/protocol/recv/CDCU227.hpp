/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 18:30:28
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CDCU227.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CDCU227_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CDCU227_HPP_

#include "protocol/BaseProtocol.hpp"

class CDCU227 : public BaseProtocol
{
private:
    /* data */
public:
    CDCU227(/* args */) : BaseProtocol(0x227)
    {
    }
    ~CDCU227() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_wireless_chg_coupling_status(const uint64_t data, uint8_t *singal) const;
    void parse_wireless_charging_status(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CDCU227_HPP_
