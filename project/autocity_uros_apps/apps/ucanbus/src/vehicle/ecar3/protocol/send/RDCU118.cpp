/*
 * @Author: hanson
 * @Date: 2024-08-28 11:13:04
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 13:35:21
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\send\RDCU118.cpp
 */
#include "vehicle/ecar3/protocol/send/RDCU118.hpp"

void RDCU118::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    _update_active();
    _update_park_enable();
    _update_drive_ctrl_mode();
    _update_tgt_gear();
    _update_tgt_throttle();
    _update_tgt_brk();
    _update_tgt_str_angle();

    _update_rollcnt();
    _update_checksum();
    *data = ReverseByteOrder(_data_to_update);
}

void RDCU118::ResetCmd()
{ // Manual inspection!
    _active = ACTIVE_DISABLE;
    _drive_ctrl_mode = RDCU_DRIVE_CONTROL_MODE_SPEED;
    _tgt_gear = RDCU_TARGET_GEAR_N;
    _tgt_throttle = 0;
    _tgt_brk = 0;
    _tgt_str_angle = 0;
    _park_enable = 0;
}

void RDCU118::_update_active()
{
    uint64_t x = CmdToHex(_active, 1, 0) & 0x1;
    x <<= Motorola(0, 7);
    _data_to_update |= x;
}

void RDCU118::_update_park_enable()
{
    uint64_t x = CmdToHex(_park_enable, 1, 0) & 0x1;
    x <<= Motorola(0, 6);
    _data_to_update |= x;
}

void RDCU118::_update_drive_ctrl_mode()
{
    uint64_t x = CmdToHex(_drive_ctrl_mode, 1, 0) & 0x3;
    x <<= Motorola(0, 4);
    _data_to_update |= x;
}

void RDCU118::_update_tgt_gear()
{
    uint64_t x = CmdToHex(_tgt_gear, 1, 0) & 0xF;
    x <<= Motorola(0, 0);
    _data_to_update |= x;
}

void RDCU118::_update_tgt_throttle()
{
    _tgt_throttle = BoundedValue(_tgt_throttle, 0.0, 102.0);
    uint64_t x = CmdToHex(_tgt_throttle, 0.4, 0) & 0xff;
    x <<= Motorola(1, 8);
    _data_to_update |= x;
}

void RDCU118::_update_tgt_brk()
{
    _tgt_brk = BoundedValue(_tgt_brk, 0.0, 102.0);
    uint64_t x = CmdToHex(_tgt_brk, 0.4, 0) & 0xff;
    x <<= Motorola(2, 16);
    _data_to_update |= x;
}

void RDCU118::_update_tgt_str_angle()
{
    _tgt_str_angle = BoundedValue(_tgt_str_angle, -1000.0, 5553.5);
    uint64_t x = CmdToHex(_tgt_str_angle, 0.1, -1000) & 0xffff;
    x <<= Motorola(4, 32);
    _data_to_update |= x;
}
