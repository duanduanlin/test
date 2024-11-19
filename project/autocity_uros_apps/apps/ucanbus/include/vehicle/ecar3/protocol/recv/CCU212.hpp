/*
 * @Author: hanson
 * @Date: 2024-08-29 15:23:11
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:24:17
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU212.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU212_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU212_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU212 : public BaseProtocol
{
private:
    /* data */
public:
    CCU212(/* args */) : BaseProtocol(0x212)
    {
    }
    ~CCU212() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_brkcmdperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkcmddrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkcmdchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkcmdoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkcmdoverrge_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbmsgperd_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbmsgdrop_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbmsgchksum_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbmsgoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkfldlack_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbcurtsenor_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbtempsenor_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbovertemp_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_brkpresrsenor_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ecupwrsupply_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvbridge_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_drvmtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbcan_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpwrswh_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbweeping_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpresfolw_alarm(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpresctrlvib_alarm(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbtempsenor_alarm(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbworkmode_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbbrkpres_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpresfolw_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbpresctrlvib_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbloadmismatch_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbovercurt_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehbbrkcmdabnormal_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU212_HPP_
