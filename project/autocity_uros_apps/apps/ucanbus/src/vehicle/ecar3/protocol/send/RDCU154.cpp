/*
 * @Author: hanson
 * @Date: 2024-08-28 14:01:42
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 14:27:24
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\send\RDCU154.cpp
 */
#include "vehicle/ecar3/protocol/send/RDCU154.hpp"

void RDCU154::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    _update_tgt_sweep_mode();
    _update_sweep_cmd();
    _update_dump_cmd();
    _update_sweep_estop_cmd();
    _update_brush_water_valve_cmd();
    _update_fan_dust_fall_valve_cmd();
    _update_suction_dust_fall_valve_cmd();
    _update_dustbin_dust_fall_valve_cmd();
    _update_roll_swp_water_valve_cmd();
    _update_dustbin_clean_water_valve_cmd();
    _update_water_boxlid_cmd();
    _update_water_drain_valve_cmd();
    _update_left_front_brush_abd_dist();
    _update_right_front_brush_abd_dist();
    _update_left_front_brush_extension_rod_cmd();
    _update_right_front_brush_extension_rod_cmd();
    _update_left_front_brush_lift_rod_cmd();
    _update_right_front_brush_lift_rod_cmd();
    _update_rear_brush_lift_rod_cmd();
    _update_suction_lift_rod_cmd();
    _update_main_brush_lift_rod_cmd();
    _update_front_fender_cmd();
    _update_shake_dust_Cmd();

    _update_rollcnt();
    _update_checksum();
    *data = ReverseByteOrder(_data_to_update);
}

void RDCU154::ResetCmd()
{ // Manual inspection!
    _tgt_sweep_mode = RDCU_TGT_SWEEP_MODE_DRIVE;
    _sweep_cmd = RDCU_SWEEP_CMD_OFF;
    _dump_cmd = RDCU_GARBAGE_DUMP_CMD_OFF;
    _sweep_estop_cmd = RDCU_SWEEP_ESTOP_CMD_NORAML;
    _brush_water_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _fan_dust_fall_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _suction_dust_fall_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _dustbin_dust_fall_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _roll_swp_water_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _dustbin_clean_water_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _water_boxlid_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _water_drain_valve_cmd = RDCU_WATER_VALVE_CTRL_CLOSE;
    _left_front_brush_abd_dist = 0;
    _right_front_brush_abd_dist = 0;
    _left_front_brush_extension_rod_cmd = RDCU_BRUSH_ABD_CMD_INVALID;
    _right_front_brush_extension_rod_cmd = RDCU_BRUSH_ABD_CMD_INVALID;
    _left_front_brush_lift_rod_cmd = RDCU_LIFT_ROD_CMD_INVALID;
    _right_front_brush_lift_rod_cmd = RDCU_LIFT_ROD_CMD_INVALID;
    _rear_brush_lift_rod_cmd = RDCU_LIFT_ROD_CMD_INVALID;
    _suction_lift_rod_cmd = RDCU_LIFT_ROD_CMD_INVALID;
    _main_brush_lift_rod_cmd = RDCU_LIFT_ROD_CMD_INVALID;
    _front_fender_cmd = 0; // close
    _shake_dust_cmd = 0;   // close
}

void RDCU154::_update_tgt_sweep_mode()
{
    uint64_t x = CmdToHex(_tgt_sweep_mode, 1, 0) & 0x1;
    x <<= Motorola(0, 7);
    _data_to_update |= x;
}

void RDCU154::_update_sweep_cmd()
{
    uint64_t x = CmdToHex(_sweep_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 6);
    _data_to_update |= x;
}

void RDCU154::_update_dump_cmd()
{
    uint64_t x = CmdToHex(_dump_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 5);
    _data_to_update |= x;
}

void RDCU154::_update_sweep_estop_cmd()
{
    uint64_t x = CmdToHex(_sweep_estop_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 4);
    _data_to_update |= x;
}

void RDCU154::_update_brush_water_valve_cmd()
{
    uint64_t x = CmdToHex(_brush_water_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 3);
    _data_to_update |= x;
}

void RDCU154::_update_fan_dust_fall_valve_cmd()
{
    uint64_t x = CmdToHex(_fan_dust_fall_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 2);
    _data_to_update |= x;
}

void RDCU154::_update_suction_dust_fall_valve_cmd()
{
    uint64_t x = CmdToHex(_suction_dust_fall_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 1);
    _data_to_update |= x;
}

void RDCU154::_update_dustbin_dust_fall_valve_cmd()
{
    uint64_t x = CmdToHex(_dustbin_dust_fall_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(0, 0);
    _data_to_update |= x;
}

void RDCU154::_update_roll_swp_water_valve_cmd()
{
    uint64_t x = CmdToHex(_roll_swp_water_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 15);
    _data_to_update |= x;
}

void RDCU154::_update_dustbin_clean_water_valve_cmd()
{
    uint64_t x = CmdToHex(_dustbin_clean_water_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 14);
    _data_to_update |= x;
}

void RDCU154::_update_water_boxlid_cmd()
{
    uint64_t x = CmdToHex(_water_boxlid_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 13);
    _data_to_update |= x;
}

void RDCU154::_update_water_drain_valve_cmd()
{
    uint64_t x = CmdToHex(_water_drain_valve_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 12);
    _data_to_update |= x;
}

void RDCU154::_update_left_front_brush_abd_dist()
{
    _left_front_brush_abd_dist = BoundedValue(_left_front_brush_abd_dist, 0.0, 275.0);
    uint64_t x = CmdToHex(_left_front_brush_abd_dist, 10, 0) & 0x3ff;
    x <<= Motorola(2, 18);
    _data_to_update |= x;
}

void RDCU154::_update_right_front_brush_abd_dist()
{
    _right_front_brush_abd_dist = BoundedValue(_right_front_brush_abd_dist, 0.0, 275.0);
    uint64_t x = CmdToHex(_right_front_brush_abd_dist, 10, 0) & 0x3ff;
    x <<= Motorola(3, 24);
    _data_to_update |= x;
}

void RDCU154::_update_left_front_brush_extension_rod_cmd()
{
    uint64_t x = CmdToHex(_left_front_brush_extension_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(4, 38);
    _data_to_update |= x;
}

void RDCU154::_update_right_front_brush_extension_rod_cmd()
{
    uint64_t x = CmdToHex(_right_front_brush_extension_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(4, 36);
    _data_to_update |= x;
}

void RDCU154::_update_left_front_brush_lift_rod_cmd()
{
    uint64_t x = CmdToHex(_left_front_brush_lift_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(4, 34);
    _data_to_update |= x;
}

void RDCU154::_update_right_front_brush_lift_rod_cmd()
{
    uint64_t x = CmdToHex(_right_front_brush_lift_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(4, 32);
    _data_to_update |= x;
}

void RDCU154::_update_rear_brush_lift_rod_cmd()
{
    uint64_t x = CmdToHex(_rear_brush_lift_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(5, 46);
    _data_to_update |= x;
}

void RDCU154::_update_suction_lift_rod_cmd()
{
    uint64_t x = CmdToHex(_suction_lift_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(5, 44);
    _data_to_update |= x;
}

void RDCU154::_update_main_brush_lift_rod_cmd()
{
    uint64_t x = CmdToHex(_main_brush_lift_rod_cmd, 1, 0) & 0x3;
    x <<= Motorola(5, 42);
    _data_to_update |= x;
}

void RDCU154::_update_front_fender_cmd()
{
    uint64_t x = CmdToHex(_front_fender_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 41);
    _data_to_update |= x;
}
void RDCU154::_update_shake_dust_Cmd()
{
    uint64_t x = CmdToHex(_shake_dust_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 40);
    _data_to_update |= x;
}
