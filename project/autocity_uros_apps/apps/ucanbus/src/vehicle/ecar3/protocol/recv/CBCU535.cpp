/*
 * @Author: hanson
 * @Date: 2024-08-29 15:05:53
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:07:09
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CBCU535.cpp
 */
#include "vehicle/ecar3/protocol/recv/CBCU535.hpp"

void CBCU535::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_left_front_brush_stretch_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.left_front_brush_stretch_mtr_err);
    parse_right_front_brush_stretch_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.right_front_brush_stretch_mtr_err);
    parse_left_front_brush_drop_mtr_fault_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.left_front_brush_drop_mtr_fault_err);
    parse_right_front_brush_drop_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.right_front_brush_drop_mtr_err);
    parse_rear_brush_drop_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.rear_brush_drop_mtr_err);
    parse_main_brush_drop_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.main_brush_drop_mtr_err);
    parse_suction_drop_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.suction_drop_mtr_err);
    parse_front_fender_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.front_fender_mtr_err);
    parse_dustbin_door_openclose_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_door_openclose_mtr_err);
    parse_dustbin_door_lock_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_door_lock_mtr_err);
    parse_main_brush_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.main_brush_mtr_err);
    parse_left_front_brush_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.left_front_brush_mtr_err);
    parse_right_front_brush_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.right_front_brush_mtr_err);
    parse_left_rear_brush_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.left_rear_brush_mtr_err);
    parse_right_rear_brush_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.right_rear_brush_mtr_err);
    parse_ctfgal_mtr1_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.ctfgal_mtr1_err);
    parse_ctfgal_mtr2_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.ctfgal_mtr2_err);
    parse_shake_dust_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.shake_dust_mtr_err);
    parse_water_pump_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.water_pump_err);
    parse_brush_water_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.brush_water_valve_err);
    parse_fan_dust_fall_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.fan_dust_fall_valve_err);
    parse_suction_dust_fall_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.suction_dust_fall_valve_err);
    parse_dustbin_dust_fall_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_dust_fall_valve_err);
    parse_roll_swp_water_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.roll_swp_water_valve_err);
    parse_dustbin_selfcleaning_water_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_selfcleaning_water_valve_err);
    parse_water_drain_valve_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.water_drain_valve_err);
    parse_low_water_level_alarm(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.low_water_level_alarm);
    parse_dustbin_overflow_alarm(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_overflow_alarm);
    parse_water_pump_pressure_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.water_pump_pressure_err);
    parse_dustbin_fall_pose_alram(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.dustbin_fall_pose_alram);
    parse_adcu_msg_offline_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.adcu_msg_offline_err);
    parse_water_boxlid_mtr_err(data, &chassis_detail->GetEcar3Chassis()->cbcu535_a_.water_boxlid_mtr_err);
}

void CBCU535::parse_left_front_brush_stretch_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_right_front_brush_stretch_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_left_front_brush_drop_mtr_fault_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_right_front_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_rear_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_main_brush_drop_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_suction_drop_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_front_fender_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_door_openclose_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 22)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_door_lock_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 20)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_main_brush_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 19)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_left_front_brush_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 18)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_right_front_brush_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 17)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_left_rear_brush_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(2, 16)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_right_rear_brush_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 31)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_ctfgal_mtr1_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 30)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_ctfgal_mtr2_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 29)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_shake_dust_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 28)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_water_pump_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 27)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_brush_water_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 26)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_fan_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 25)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_suction_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(3, 24)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_dust_fall_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 39)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_roll_swp_water_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 38)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_selfcleaning_water_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 37)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_water_drain_valve_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 36)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_low_water_level_alarm(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 47)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_overflow_alarm(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 46)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_water_pump_pressure_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 45)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_dustbin_fall_pose_alram(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 44)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_adcu_msg_offline_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 43)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU535::parse_water_boxlid_mtr_err(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(6, 54)) & 0x3;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
