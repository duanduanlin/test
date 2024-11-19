/*
 * @Author: hanson
 * @Date: 2024-08-23 14:29:06
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-24 15:07:24
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\msg_wrap\ControlMsgWrap.hpp
 */
#ifndef INCLUDE_MSG_WRAP_CONTROLCMDMSG_HPP_
#define INCLUDE_MSG_WRAP_CONTROLCMDMSG_HPP_

#include <ucontrol_msgs/msg/control_cmd.h>
#include "msg_wrap/BaseMsgWrap.hpp"

#define ControlCmdMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(ucontrol_msgs, msg, ControlCMD))
using ChassisCmdMsg = ucontrol_msgs__msg__ChassisCMD;
using SweeperCmdMsg = ucontrol_msgs__msg__SweeperCMD;
using LightCmdMsg = ucontrol_msgs__msg__LightCMD;
using AudioCmdMsg = ucontrol_msgs__msg__AudioCMD;
using ControlCmdMsg = ucontrol_msgs__msg__ControlCMD;

class ControlMsgWrap : public BaseMsgWrap<ControlCmdMsg>
{
private:
    /* chassis cmd */
    ChassisCmdMsg _chassis_cmd;
    /*sweeper cmd */
    SweeperCmdMsg _sweeper_cmd;
    /*light cmd */
    LightCmdMsg _light_cmd;
    /*audio cmd */
    AudioCmdMsg _audio_cmd;

public:
    ControlMsgWrap(/* args */);
    ~ControlMsgWrap();

    void Setup() override;
    void Update() override;
    void Reset() override;

    std::string GetPrintableStr() override;

    ChassisCmdMsg &GetChassisCmd()
    {
        return _chassis_cmd;
    }

    SweeperCmdMsg &GetSweeperCmd()
    {
        return _sweeper_cmd;
    }

    LightCmdMsg &GetLightCmd()
    {
        return _light_cmd;
    }

    AudioCmdMsg &GetAudioCmd()
    {
        return _audio_cmd;
    }
};
#endif // INCLUDE_MSG_WRAP_CONTROLCMDMSG_HPP_
