/*
 * @Author: hanson
 * @Date: 2024-08-29 16:09:48
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 16:09:54
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU2A5.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A5_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A5_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU2A5 : public BaseProtocol
{
private:
    /* data */
public:
    CCU2A5(/* args */) : BaseProtocol(0x2a5)
    {
    }
    ~CCU2A5() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_vehvin_c1(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c2(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c3(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c4(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c5(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c6(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c7(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A5_HPP_
