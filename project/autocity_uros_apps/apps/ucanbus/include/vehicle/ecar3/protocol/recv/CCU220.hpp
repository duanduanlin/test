/*
 * @Author: hanson
 * @Date: 2024-08-29 15:50:53
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:51:01
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU220.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU220_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU220_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU220 : public BaseProtocol
{
private:
    /* data */
public:
    CCU220(/* args */) : BaseProtocol(0x220)
    {
    }
    ~CCU220() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_bodycmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bodycmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bodycmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bodycmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_headlamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_turnllamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_turnrlamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_backlamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_buzzer_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_runlamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brklamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_foglamp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_horn_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_widthlamp_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU220_HPP_
