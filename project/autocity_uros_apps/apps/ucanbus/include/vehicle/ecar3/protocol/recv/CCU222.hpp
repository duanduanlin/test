/*
 * @Author: hanson
 * @Date: 2024-08-29 14:59:32
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:01:03
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU222.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU222_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU222_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU222 : public BaseProtocol
{
private:
    /* data */
public:
    CCU222(/* args */) : BaseProtocol(0x222)
    {
    }
    ~CCU222() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_lvbat_volt(const uint64_t data, double *singal) const;
    void parse_ccu_bms_vehbatsoc(const uint64_t data, double *singal) const;
    void parse_ccu_bms_batsoh(const uint64_t data, double *singal) const;
    void parse_ccu_bms_batvolt(const uint64_t data, double *singal) const;
    void parse_ccu_bms_batcurt(const uint64_t data, double *singal) const;
    void parse_ccu_bms_battemp(const uint64_t data, double *singal) const;
    void parse_ccu_bms_chgst(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bms_dischgst(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bms_feedbackst(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bms_chgconnectst(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU222_HPP_
