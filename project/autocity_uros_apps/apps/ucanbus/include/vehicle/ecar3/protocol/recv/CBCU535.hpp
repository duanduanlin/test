/*
 * @Author: hanson
 * @Date: 2024-08-29 15:04:20
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:05:43
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CBCU535.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU535_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU535_HPP_

#include "protocol/BaseProtocol.hpp"

class CBCU535 : public BaseProtocol
{
private:
    /* data */
public:
    CBCU535(/* args */) : BaseProtocol(0x535)
    {
    }
    ~CBCU535() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_left_front_brush_stretch_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_stretch_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_drop_mtr_fault_err(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_rear_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_main_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_suction_drop_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_front_fender_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_door_openclose_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_door_lock_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_main_brush_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_left_rear_brush_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_right_rear_brush_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_ctfgal_mtr1_err(const uint64_t data, uint8_t *singal) const;
    void parse_ctfgal_mtr2_err(const uint64_t data, uint8_t *singal) const;
    void parse_shake_dust_mtr_err(const uint64_t data, uint8_t *singal) const;
    void parse_water_pump_err(const uint64_t data, uint8_t *singal) const;
    void parse_brush_water_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_fan_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_suction_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_roll_swp_water_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_selfcleaning_water_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_water_drain_valve_err(const uint64_t data, uint8_t *singal) const;
    void parse_low_water_level_alarm(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_overflow_alarm(const uint64_t data, uint8_t *singal) const;
    void parse_water_pump_pressure_err(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_fall_pose_alram(const uint64_t data, uint8_t *singal) const;
    void parse_adcu_msg_offline_err(const uint64_t data, uint8_t *singal) const;
    void parse_water_boxlid_mtr_err(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU535_HPP_
