/*
 * @Author: hanson
 * @Date: 2024-08-28 14:33:20
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 14:51:37
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\send\RDCU155.cpp
 */

#include "vehicle/ecar3/protocol/send/RDCU155.hpp"

void RDCU155::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    _update_dustbin_lock_cmd();
    _update_dustbin_door_cmd();
    _update_dustbin_liftdrop_cmd();
    _update_dustbin_overturn_cmd();
    _update_dustbin_lift_angle_gear_cmd();
    _update_fan_cmd();
    _update_left_front_brush_motor_cmd();
    _update_right_front_brush_motor_cmd();
    _update_left_rear_brush_motor_cmd();
    _update_right_rear_brush_motor_cmd();
    _update_main_brush_motor_cmd();
    _update_fan_mode_cmd();
    _update_fan_gear_cmd();
    _update_fan_speed_rpm();
    _update_left_front_brush_motor_mode_cmd();
    _update_left_front_brush_motor_gear_cmd();
    _update_left_front_brush_motor_spd_rpm();
    _update_right_front_brush_motor_mode_cmd();
    _update_right_front_brush_motor_gear_cmd();
    _update_right_front_brush_motor_spd_rpm();

    _update_rollcnt();
    _update_checksum();
    *data = ReverseByteOrder(_data_to_update);
}

void RDCU155::ResetCmd()
{ // Manual inspection!
    _dustbin_lock_cmd = RDCU_DUSTBIN_LOCK_CMD_INVALID;
    _dustbin_door_cmd = RDCU_DUSTBIN_DOOR_CMD_INVALID;
    _dustbin_liftdrop_cmd = RDCU_DUSTBIN_LIFTDROP_CMD_INVALID;
    _dustbin_overturn_cmd = RDCU_DUSTBIN_OVERTURN_CMD_INVALID;
    _dustbin_lift_angle_gear_cmd = RDCU_DUSTBIN_LIFT_ANGLE_GEAR_CMD_1; // 45°

    _fan_cmd = 0;
    _left_front_brush_motor_cmd = 0;
    _right_front_brush_motor_cmd = 0;
    _left_rear_brush_motor_cmd = 0;
    _right_rear_brush_motor_cmd = 0;
    _main_brush_motor_cmd = 0;

    _fan_mode_cmd = RDCU_FAN_CTRL_MODE_GEAR;
    _fan_gear_cmd = RDCU_FAN_GEAR_MEDIUM;
    _fan_speed_rpm = 0;

    _left_front_brush_motor_mode_cmd = RDCU_BRUSH_MTR_CTRL_MODE_GEAR;
    _left_front_brush_motor_gear_cmd = RDCU_BRUSH_MOTOR_GEAR_MEDIUM;
    _left_front_brush_motor_spd_rpm = 0;

    _right_front_brush_motor_mode_cmd = RDCU_BRUSH_MTR_CTRL_MODE_GEAR;
    _right_front_brush_motor_gear_cmd = RDCU_BRUSH_MOTOR_GEAR_MEDIUM;
    _right_front_brush_motor_spd_rpm = 0;
}

void RDCU155::_update_dustbin_lock_cmd()
{
    uint64_t x = CmdToHex(_dustbin_lock_cmd, 1, 0) & 0x3;
    x <<= Motorola(0, 6);
    _data_to_update |= x;
}

void RDCU155::_update_dustbin_door_cmd()
{
    uint64_t x = CmdToHex(_dustbin_door_cmd, 1, 0) & 0x3;
    x <<= Motorola(0, 4);
    _data_to_update |= x;
}

void RDCU155::_update_dustbin_liftdrop_cmd()
{
    uint64_t x = CmdToHex(_dustbin_liftdrop_cmd, 1, 0) & 0x3;
    x <<= Motorola(0, 2);
    _data_to_update |= x;
}

void RDCU155::_update_dustbin_overturn_cmd()
{
    uint64_t x = CmdToHex(_dustbin_overturn_cmd, 1, 0) & 0x3;
    x <<= Motorola(0, 0);
    _data_to_update |= x;
}

void RDCU155::_update_dustbin_lift_angle_gear_cmd()
{
    uint64_t x = CmdToHex(_dustbin_lift_angle_gear_cmd, 1, 0) & 0x3;
    x <<= Motorola(1, 14);
    _data_to_update |= x;
}

void RDCU155::_update_fan_cmd()
{
    uint64_t x = CmdToHex(_fan_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 13);
    _data_to_update |= x;
}

void RDCU155::_update_left_front_brush_motor_cmd()
{
    uint64_t x = CmdToHex(_left_front_brush_motor_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 12);
    _data_to_update |= x;
}

void RDCU155::_update_right_front_brush_motor_cmd()
{
    uint64_t x = CmdToHex(_right_front_brush_motor_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 11);
    _data_to_update |= x;
}

void RDCU155::_update_left_rear_brush_motor_cmd()
{
    uint64_t x = CmdToHex(_left_rear_brush_motor_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 10);
    _data_to_update |= x;
}

void RDCU155::_update_right_rear_brush_motor_cmd()
{
    uint64_t x = CmdToHex(_right_rear_brush_motor_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 9);
    _data_to_update |= x;
}

void RDCU155::_update_main_brush_motor_cmd()
{
    uint64_t x = CmdToHex(_main_brush_motor_cmd, 1, 0) & 0x1;
    x <<= Motorola(1, 8);
    _data_to_update |= x;
}

void RDCU155::_update_fan_mode_cmd()
{
    uint64_t x = CmdToHex(_fan_mode_cmd, 1, 0) & 0x3;
    x <<= Motorola(2, 22);
    _data_to_update |= x;
}

void RDCU155::_update_fan_gear_cmd()
{
    uint64_t x = CmdToHex(_fan_gear_cmd, 1, 0) & 0x3;
    x <<= Motorola(2, 20);
    _data_to_update |= x;
}

void RDCU155::_update_fan_speed_rpm()
{
    _fan_speed_rpm = BoundedValue(_fan_speed_rpm, 0.0, 3500.0);
    uint64_t x = CmdToHex(_fan_speed_rpm, 10, 2000) & 0xff;
    x <<= Motorola(3, 28);
    _data_to_update |= x;
}

void RDCU155::_update_left_front_brush_motor_mode_cmd()
{
    uint64_t x = CmdToHex(_left_front_brush_motor_mode_cmd, 1, 0) & 0x3;
    x <<= Motorola(3, 26);
    _data_to_update |= x;
}

void RDCU155::_update_left_front_brush_motor_gear_cmd()
{
    uint64_t x = CmdToHex(_left_front_brush_motor_gear_cmd, 1, 0) & 0x3;
    x <<= Motorola(3, 24);
    _data_to_update |= x;
}

void RDCU155::_update_left_front_brush_motor_spd_rpm()
{
    _left_front_brush_motor_spd_rpm = BoundedValue(_left_front_brush_motor_spd_rpm, 0.0, 120.0);
    uint64_t x = CmdToHex(_left_front_brush_motor_spd_rpm, 5, 60) & 0xff;
    x <<= Motorola(4, 32);
    _data_to_update |= x;
}

void RDCU155::_update_right_front_brush_motor_mode_cmd()
{
    uint64_t x = CmdToHex(_right_front_brush_motor_mode_cmd, 1, 0) & 0x3;
    x <<= Motorola(5, 46);
    _data_to_update |= x;
}

void RDCU155::_update_right_front_brush_motor_gear_cmd()
{
    uint64_t x = CmdToHex(_right_front_brush_motor_gear_cmd, 1, 0) & 0x3;
    x <<= Motorola(5, 44);
    _data_to_update |= x;
}

void RDCU155::_update_right_front_brush_motor_spd_rpm()
{
    _right_front_brush_motor_spd_rpm = BoundedValue(_right_front_brush_motor_spd_rpm, 0.0, 120.0);
    uint64_t x = CmdToHex(_right_front_brush_motor_spd_rpm, 5, 60) & 0xff;
    x <<= Motorola(6, 52);
    _data_to_update |= x;
}
