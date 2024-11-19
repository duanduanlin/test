/*
 * @Author: hanson
 * @Date: 2024-08-29 15:35:20
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:35:25
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU214.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU214_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU214_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU214 : public BaseProtocol
{
private:
    /* data */
public:
    CCU214(/* args */) : BaseProtocol(0x214)
    {
    }
    ~CCU214() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_prkcmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_prkcmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_prkcmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_prkcmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_prkcmdoverrge_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbmsgperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbmsgdrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbmsgchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbmsgoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbparkinvalid_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbenablefeedback_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbovervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbundervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbrelay_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbcancom_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbleftlockingact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbrightlockingact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbleftunlockingact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbrightunlockingact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbfallback_warning(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbprotectoff_active(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbmtroffcurt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbtempsenor_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbovertemplevel1_warning(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbovertemplevel2_warning(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epbwakeuphw_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU214_HPP_
