/*
 * @Author: hanson
 * @Date: 2024-08-28 14:59:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 15:06:28
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\protocol\send\RDCU6F0.cpp
 */
#include "vehicle/ecar3/protocol/send/RDCU6F0.hpp"

void RDCU6F0::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    _update_play_audio_pause();
    _update_play_audio_num();
    _update_play_audio_volume();
    _update_play_audio_mode();
    _update_play_audio_cycle_cnt();
    _update_play_audio_cycle_duration();
    _update_play_audio_cycle_interval();

    *data = ReverseByteOrder(_data_to_update);
}

void RDCU6F0::ResetCmd()
{ // Manual inspection!
    _play_audio_pause = AUDIO_CMD_STOP;
    _play_audio_num = 0; // 不播放
    _play_audio_volume = 0;
    _play_audio_mode = AUDIO_MODE_DISABLE;
    _play_audio_cycle_cnt = 0;
    _play_audio_cycle_duration = 0;
    _play_audio_cycle_interval = 0;
}

void RDCU6F0::_update_play_audio_pause()
{
    uint64_t x = CmdToHex(_play_audio_pause, 1, 0) & 0x1;
    x <<= Motorola(0, 0);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_num()
{
    uint64_t x = CmdToHex(_play_audio_num, 1, 0) & 0x7F;
    x <<= Motorola(0, 1);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_volume()
{
    _play_audio_volume = BoundedValue(_play_audio_volume, (uint8_t)0, (uint8_t)100);
    uint64_t x = CmdToHex(_play_audio_volume, 1, 0);
    x <<= Motorola(1, 8);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_mode()
{
    uint64_t x = CmdToHex(_play_audio_mode, 1, 0) & 0x0F;
    x <<= Motorola(2, 16);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_cycle_cnt()
{
    uint64_t x = CmdToHex(_play_audio_cycle_cnt, 1, 0) & 0xFF;
    x <<= Motorola(3, 24);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_cycle_duration()
{
    uint64_t x = CmdToHex(_play_audio_cycle_duration, 1, 0) & 0xFFFF;
    x <<= Motorola(5, 40);
    _data_to_update |= x;
}

void RDCU6F0::_update_play_audio_cycle_interval()
{
    uint64_t x = CmdToHex(_play_audio_cycle_interval, 1, 0) & 0xFF;
    x <<= Motorola(6, 48);
    _data_to_update |= x;
}
