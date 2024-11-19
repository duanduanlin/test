/*
 * @Author: hanson
 * @Date: 2024-08-28 13:42:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 13:54:18
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\send\RDCU119.cpp
 */
#include "vehicle/ecar3/protocol/send/RDCU119.hpp"

void RDCU119::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    _update_width_lamp_cmd();
    _update_brake_lamp_cmd();
    _update_fog_lamp_cmd();
    _update_head_lamp_cmd();
    _update_double_flash_lamp_cmd();
    _update_left_turn_lamp_cmd();
    _update_right_turn_lamp_cmd();
    _update_back_lamp_cmd();
    _update_buzzer_cmd();
    _update_horn_cmd();
    _update_run_lamp_cmd();

    _update_rollcnt();
    _update_checksum();
    *data = ReverseByteOrder(_data_to_update);
}

void RDCU119::ResetCmd()
{ // Manual inspection!
    _width_lamp_cmd = 0;
    _brake_lamp_cmd = 0;
    _fog_lamp_cmd = 0;
    _head_lamp_cmd = 0;
    _double_flash_lamp_cmd = 0;
    _left_turn_lamp_cmd = 0;
    _right_turn_lamp_cmd = 0;
    _back_lamp_cmd = 0;
    _buzzer_cmd = 0;
    _horn_cmd = 0;
    _run_lamp_cmd = 0;
}

void RDCU119::_update_width_lamp_cmd()
{
    uint64_t x = CmdToHex(_width_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(4, 34);
    _data_to_update |= x;
}

void RDCU119::_update_brake_lamp_cmd()
{
    uint64_t x = CmdToHex(_brake_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(4, 33);
    _data_to_update |= x;
}

void RDCU119::_update_fog_lamp_cmd()
{
    uint64_t x = CmdToHex(_fog_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(4, 32);
    _data_to_update |= x;
}

void RDCU119::_update_head_lamp_cmd()
{
    uint64_t x = CmdToHex(_head_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 47);
    _data_to_update |= x;
}

void RDCU119::_update_double_flash_lamp_cmd()
{
    uint64_t x = CmdToHex(_double_flash_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 46);
    _data_to_update |= x;
}

void RDCU119::_update_left_turn_lamp_cmd()
{
    uint64_t x = CmdToHex(_left_turn_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 45);
    _data_to_update |= x;
}

void RDCU119::_update_right_turn_lamp_cmd()
{
    uint64_t x = CmdToHex(_right_turn_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 44);
    _data_to_update |= x;
}

void RDCU119::_update_back_lamp_cmd()
{
    uint64_t x = CmdToHex(_back_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 43);
    _data_to_update |= x;
}

void RDCU119::_update_buzzer_cmd()
{
    uint64_t x = CmdToHex(_buzzer_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 42);
    _data_to_update |= x;
}

void RDCU119::_update_horn_cmd()
{
    uint64_t x = CmdToHex(_horn_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 41);
    _data_to_update |= x;
}

void RDCU119::_update_run_lamp_cmd()
{
    uint64_t x = CmdToHex(_run_lamp_cmd, 1, 0) & 0x1;
    x <<= Motorola(5, 40);
    _data_to_update |= x;
}
