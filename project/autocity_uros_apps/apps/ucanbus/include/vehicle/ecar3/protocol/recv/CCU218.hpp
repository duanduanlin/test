/*
 * @Author: hanson
 * @Date: 2024-08-29 15:47:45
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:47:52
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU218.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU218_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU218_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU218 : public BaseProtocol
{
private:
    /* data */
public:
    CCU218(/* args */) : BaseProtocol(0x218)
    {
    }
    ~CCU218() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_drvcmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvcmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvcmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvcmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvcmdoverrge_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumsgperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumsgdrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumsgchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumsgoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumainpwrcur_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcucurtsensor_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuprechg_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcupwrovervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcupwrundervolt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcupwrovercurt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuovertemp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcucancom_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumtrovertemp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumtrphase_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuencoder_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumtrblock_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuenable_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcuthortact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcumtrspdact_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcu_errcode(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU218_HPP_
