/*
 * @Author: hanson
 * @Date: 2024-08-28 14:56:08
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-30 14:24:17
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\send\RDCU6F0.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU6F0_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU6F0_HPP_

#include "protocol/BaseProtocol.hpp"

class RDCU6F0 : public BaseProtocol
{
public:
    enum AudioControlCmd
    {
        AUDIO_CMD_PLAY = 0x0, // 播放
        AUDIO_CMD_STOP = 0x1, // 停止
    };

    enum AudioControlMode
    {
        AUDIO_MODE_DISABLE = 0x0,           // 不播放
        AUDIO_MODE_SINGLE = 0x1,            // 单次播放
        AUDIO_MODE_CYCLE_BY_NUM = 0x2,      // 按次数循环播放
        AUDIO_MODE_CYCLE_BY_DURATION = 0x3, // 按时间循环播放
    };

private:
    /* data */
    uint8_t _play_audio_pause;           // 暂停播放
    uint8_t _play_audio_num;             // 需要播放的音频编号
    uint8_t _play_audio_volume;          // 需要播放的音频音量0-100
    uint8_t _play_audio_mode;            // 播放模式
    uint8_t _play_audio_cycle_cnt;       // 播放循环次数
    uint16_t _play_audio_cycle_duration; // 播放循环时长
    uint8_t _play_audio_cycle_interval;  // 播放循环间隔
public:
    RDCU6F0(/* args */) : BaseProtocol(0x6f0)
    {
        ResetCmd();
    }
    ~RDCU6F0() = default;

    void UpdateCmd(uint64_t *data) override;
    void ResetCmd() override;

    void SetPlayAudioPause(const uint8_t val)
    {
        _play_audio_pause = val;
    }

    void SetPlayAudioNum(const uint8_t val)
    {
        _play_audio_num = val;
    }

    void SetPlayAudioVolume(const uint8_t val)
    {
        _play_audio_volume = val;
    }

    void SetPlayAudioMode(const uint8_t val)
    {
        _play_audio_mode = val;
    }

    void SetPlayAudioCycleCnt(const uint8_t val)
    {
        _play_audio_cycle_cnt = val;
    }

    void SetPlayAudioCycleDuration(const uint16_t val)
    {
        _play_audio_cycle_duration = val;
    }

    void SetPlayAudioCycleInterval(const uint8_t val)
    {
        _play_audio_cycle_interval = val;
    }

private:
    void _update_play_audio_pause();
    void _update_play_audio_num();
    void _update_play_audio_volume();
    void _update_play_audio_mode();
    void _update_play_audio_cycle_cnt();
    void _update_play_audio_cycle_duration();
    void _update_play_audio_cycle_interval();
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_SEND_RDCU6F0_HPP_
