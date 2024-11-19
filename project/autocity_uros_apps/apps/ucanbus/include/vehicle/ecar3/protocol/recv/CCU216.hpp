/*
 * @Author: hanson
 * @Date: 2024-08-29 15:39:52
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:40:00
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU216.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU216_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU216_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU216 : public BaseProtocol
{
private:
    /* data */
public:
    CCU216(/* args */) : BaseProtocol(0x216)
    {
    }
    ~CCU216() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_strcmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_strcmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_strcmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_strcmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_strcmdoverrge_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsmsgperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsmsgdrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsmsgchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsmsgoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsworkmode_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epsstrangle_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_ecuovervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_ecuundervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_mtrovercurt_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_ecuovertemp_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_mtrovertemp_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_anglesensor_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_anglealignm_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_strmtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_eps_cancom_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU216_HPP_
