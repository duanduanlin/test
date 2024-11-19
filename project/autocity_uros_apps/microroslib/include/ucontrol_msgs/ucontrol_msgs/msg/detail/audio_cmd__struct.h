// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ucontrol_msgs:msg/AudioCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__AUDIO_CMD__STRUCT_H_
#define UCONTROL_MSGS__MSG__DETAIL__AUDIO_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'AUDIO_CMD_PLAY'.
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_CMD_PLAY = 1
};

/// Constant 'AUDIO_CMD_PAUSE'.
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_CMD_PAUSE = 0
};

/// Constant 'AUDIO_NUM_NONE'.
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_NONE = 0
};

/// Constant 'AUDIO_NUM_START'.
/**
  * 车辆起步
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_START = 1
};

/// Constant 'AUDIO_NUM_TURN_LEFT'.
/**
  * 车辆左转
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_TURN_LEFT = 2
};

/// Constant 'AUDIO_NUM_TURN_RIGHT'.
/**
  * 车辆右转
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_TURN_RIGHT = 3
};

/// Constant 'AUDIO_NUM_TURN_BACK'.
/**
  * 倒车
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_TURN_BACK = 4
};

/// Constant 'AUDIO_NUM_PULL_OVER'.
/**
  * 靠边停车
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_PULL_OVER = 5
};

/// Constant 'AUDIO_NUM_WORKING'.
/**
  * 作业中
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_WORKING = 6
};

/// Constant 'AUDIO_NUM_PATROL'.
/**
  * 巡逻中
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_NUM_PATROL = 7
};

/// Constant 'AUDIO_MODE_DISABLE'.
/**
  * 不播放
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_MODE_DISABLE = 0
};

/// Constant 'AUDIO_MODE_SINGLE'.
/**
  * 单次播放
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_MODE_SINGLE = 1
};

/// Constant 'AUDIO_MODE_CYCLE_BY_NUM'.
/**
  * 按次数循环播放
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_MODE_CYCLE_BY_NUM = 2
};

/// Constant 'AUDIO_MODE_CYCLE_BY_DURATION'.
/**
  * 按时间循环播放
 */
enum
{
  ucontrol_msgs__msg__AudioCMD__AUDIO_MODE_CYCLE_BY_DURATION = 3
};

/// Struct defined in msg/AudioCMD in the package ucontrol_msgs.
/**
  * audio control command
  * 控制指令
 */
typedef struct ucontrol_msgs__msg__AudioCMD
{
  int8_t audio_cmd;
  /// 要播放的音频
  int8_t audio_num;
  /// 音量0-100
  int8_t audio_volume;
  /// 播放模式
  int8_t audio_mode;
  /// 循环次数
  int8_t play_cycle_cnt;
  /// 循环时长
  int16_t play_cycle_duration;
  /// 循环间隔
  int8_t play_cycle_interval;
  /// 鸣笛
  int8_t horn_cmd;
} ucontrol_msgs__msg__AudioCMD;

// Struct for a sequence of ucontrol_msgs__msg__AudioCMD.
typedef struct ucontrol_msgs__msg__AudioCMD__Sequence
{
  ucontrol_msgs__msg__AudioCMD * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ucontrol_msgs__msg__AudioCMD__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__AUDIO_CMD__STRUCT_H_
