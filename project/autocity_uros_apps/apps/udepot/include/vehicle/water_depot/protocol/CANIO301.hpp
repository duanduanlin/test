/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 16:27:48
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\protocol\recv\CANIO301.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_RECV_CANIO301_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_RECV_CANIO301_HPP_

#include "protocol/BaseProtocol.hpp"

class CANIO301 : public BaseProtocol
{
private:
public:
    CANIO301(/* args */) : BaseProtocol(0x301)
    {
    }
    ~CANIO301() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_water_button_status(const uint64_t data, uint8_t *singal) const;
    void parse_estop_button_status(const uint64_t data, uint8_t *singal) const;
};

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_RECV_CANIO101_HPP_
