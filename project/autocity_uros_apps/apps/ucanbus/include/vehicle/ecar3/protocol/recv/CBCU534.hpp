/*
 * @Author: hanson
 * @Date: 2024-08-29 18:24:39
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 18:25:47
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CBCU534.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU534_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU534_HPP_

#include "protocol/BaseProtocol.hpp"

class CBCU534 : public BaseProtocol
{
private:
    /* data */
public:
    CBCU534(/* args */) : BaseProtocol(0x534)
    {
    }
    ~CBCU534() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_sweep_mode(const uint64_t data, uint8_t *singal) const;
    void parse_sweep_sys_status(const uint64_t data, uint8_t *singal) const;
    void parse_sweep_estop_status(const uint64_t data, uint8_t *singal) const;
    void parse_shake_dust_status(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_stretch_status(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_stretch_status(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_drop_status(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_drop_status(const uint64_t data, uint8_t *singal) const;
    void parse_rear_brush_drop_status(const uint64_t data, uint8_t *singal) const;
    void parse_main_brush_drop_status(const uint64_t data, uint8_t *singal) const;
    void parse_suction_drop_status(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_motor_status(const uint64_t data, uint8_t *singal) const;
    void parse_right_front_brush_motor_status(const uint64_t data, uint8_t *singal) const;
    void parse_left_rear_brush_motor_status(const uint64_t data, uint8_t *singal) const;
    void parse_right_rear_brush_motor_status(const uint64_t data, uint8_t *singal) const;
    void parse_main_brush_motor_status(const uint64_t data, uint8_t *singal) const;
    void parse_left_front_brush_expand_dist_mm(const uint64_t data, double *singal) const;
    void parse_right_front_brush_expand_dist_mm(const uint64_t data, double *singal) const;
    void parse_ctfg_fan1_status(const uint64_t data, uint8_t *singal) const;
    void parse_ctfg_fan2_status(const uint64_t data, uint8_t *singal) const;
    void parse_front_fender_status(const uint64_t data, uint8_t *singal) const;
    void parse_water_pump_status(const uint64_t data, uint8_t *singal) const;
    void parse_brush_water_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_fan_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_suction_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_roll_swp_water_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_dustbin_clean_water_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_water_boxlid_status(const uint64_t data, uint8_t *singal) const;
    void parse_water_drain_valve_status(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CBCU534_HPP_
