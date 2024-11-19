/*
 * @Author: hanson
 * @Date: 2024-08-29 13:44:29
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 13:55:38
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU240.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU240_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU240_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU240 : public BaseProtocol
{
private:
    /* data */
public:
    CCU240(/* args */) : BaseProtocol(0x240)
    {
    }
    ~CCU240() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_vehicle_run_mode(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_veh_runlockrsn(const uint64_t data, uint8_t *singal) const;
    void parse_err_level(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ftcrash_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_rrcrash_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehemgcyswh_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_lvbat_lowvolt(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bat_lowsoc(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_bms_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_mcu_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ehb_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_eps_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_epb_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_siu_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_lpdu_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_tirepresralarm_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_canbusoff_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_segcodedispoffline_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_leddispofflie_err(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_chginhibit_flt(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_pwrupinhibit_flt(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_ademgcystop_st(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehemgcystop_reason(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_hpdu_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_cbcu_errlevel(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_veh_errcode(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU240_HPP_
