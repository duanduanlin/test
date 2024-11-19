/*
 * @Author: hanson
 * @Date: 2024-08-29 15:54:04
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:54:11
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU261.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU261_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU261_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU261 : public BaseProtocol
{
private:
    /* data */
public:
    CCU261(/* args */) : BaseProtocol(0x261)
    {
    }
    ~CCU261() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_powercmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_powercmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_powercmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_powercmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_pdumsgperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_pdumsgdrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_pdumsgchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_pdumsgoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_chas12v_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ad12v1_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ad12v2_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ad24v_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ccupwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bmspwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epspwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_siupwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_tpmspwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_datarecpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_emgcyrmtpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuwakeup_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bmswakeup_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbwakeup_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epswakeup_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbwakeup_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_rsrvdwakeup1_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_rsrvdwakeup2_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_rsrvdwakeup3_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_rsrvdwakeup4_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU261_HPP_
