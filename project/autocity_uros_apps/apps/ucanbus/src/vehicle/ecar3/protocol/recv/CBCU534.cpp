/*
 * @Author: hanson
 * @Date: 2024-08-29 18:25:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 18:27:11
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\recv\CBCU534.cpp
 */
#include "vehicle/ecar3/protocol/recv/CBCU534.hpp"

void CBCU534::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_sweep_mode(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.sweep_mode);
    parse_sweep_sys_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.sweep_sys_status);
    parse_sweep_estop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.sweep_estop_status);
    parse_shake_dust_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.shake_dust_status);
    parse_left_front_brush_stretch_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.left_front_brush_stretch_status);
    parse_right_front_brush_stretch_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.right_front_brush_stretch_status);
    parse_left_front_brush_drop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.left_front_brush_drop_status);
    parse_right_front_brush_drop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.right_front_brush_drop_status);
    parse_rear_brush_drop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.rear_brush_drop_status);
    parse_main_brush_drop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.main_brush_drop_status);
    parse_suction_drop_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.suction_drop_status);
    parse_left_front_brush_motor_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.left_front_brush_motor_status);
    parse_right_front_brush_motor_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.right_front_brush_motor_status);
    parse_left_rear_brush_motor_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.left_rear_brush_motor_status);
    parse_right_rear_brush_motor_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.right_rear_brush_motor_status);
    parse_main_brush_motor_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.main_brush_motor_status);
    parse_left_front_brush_expand_dist_mm(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.left_front_brush_expand_dist_mm);
    parse_right_front_brush_expand_dist_mm(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.right_front_brush_expand_dist_mm);
    parse_ctfg_fan1_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.ctfg_fan1_status);
    parse_ctfg_fan2_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.ctfg_fan2_status);
    parse_front_fender_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.front_fender_status);
    parse_water_pump_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.water_pump_status);
    parse_brush_water_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.brush_water_valve_status);
    parse_fan_dust_fall_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.fan_dust_fall_valve_status);
    parse_suction_dust_fall_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.suction_dust_fall_valve_status);
    parse_dustbin_dust_fall_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.dustbin_dust_fall_valve_status);
    parse_roll_swp_water_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.roll_swp_water_valve_status);
    parse_dustbin_clean_water_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.dustbin_clean_water_valve_status);
    parse_water_boxlid_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.water_boxlid_status);
    parse_water_drain_valve_status(data, &chassis_detail->GetEcar3Chassis()->cbcu534_a_.water_drain_valve_status);
}

void CBCU534::parse_sweep_mode(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 7)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_sweep_sys_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 6)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_sweep_estop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 5)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_shake_dust_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 4)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_left_front_brush_stretch_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_right_front_brush_stretch_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_left_front_brush_drop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 1)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_right_front_brush_drop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_rear_brush_drop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 15)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_main_brush_drop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 14)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_suction_drop_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 13)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_left_front_brush_motor_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 12)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_right_front_brush_motor_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 11)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_left_rear_brush_motor_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 10)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_right_rear_brush_motor_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 9)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_main_brush_motor_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(1, 8)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_left_front_brush_expand_dist_mm(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(3, 30) - 6)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 6;
    double m = 0;
    HexToDecimal(a, 10, 0, &m);
    *singal = m;
}
void CBCU534::parse_right_front_brush_expand_dist_mm(const uint64_t data, double *singal) const
{
    uint16_t x = (data >> (Motorola(4, 36) - 6)) & 0xffff;
    uint16_t a = ((uint16_t)(x)) >> 6;
    double m = 0;
    HexToDecimal(a, 10, 0, &m);
    *singal = m;
}
void CBCU534::parse_ctfg_fan1_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 35)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_ctfg_fan2_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 34)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_front_fender_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 33)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_water_pump_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(4, 32)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_brush_water_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 47)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_fan_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 46)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_suction_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 45)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_dustbin_dust_fall_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 44)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_roll_swp_water_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 43)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_dustbin_clean_water_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 42)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_water_boxlid_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 41)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
void CBCU534::parse_water_drain_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(5, 40)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
