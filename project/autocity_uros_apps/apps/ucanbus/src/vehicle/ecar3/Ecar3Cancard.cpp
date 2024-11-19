/*
 * @Author: hanson
 * @Date: 2024-08-27 11:28:28
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-26 16:27:12
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\vehicle\ecar3\Ecar3Cancard.cpp
 */
#include "vehicle/ecar3/Ecar3Cancard.hpp"
#include "trace/CanTrace.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

Ecar3Cancard::Ecar3Cancard(const std::string name) : BaseCancard(name)
{
    LOG_INFO("can_interfaces:%s\r\n", name.c_str());
    _save_can_data = GetParamWithDefault<bool>("save_can_data", false);
}

Ecar3Cancard::~Ecar3Cancard()
{
}

int Ecar3Cancard::CanSend(std::vector<can_frame> &frames)
{
    for (auto i : frames)
    {
        if (CanSend(i) < 0)
        {
            LOG_ERRO("can_id:%04x send failed\r\n", i.can_id);
        }
    }

    return 0;
}

int Ecar3Cancard::CanSend(can_frame &frame)
{
    if (_save_can_data)
    {
        TraceCanSendFrame(frame);
    }

    return BaseCancard::CanSend(frame);
}

int Ecar3Cancard::CanRecv(can_frame &aframe)
{
    int ret = BaseCancard::CanRecv(aframe);
    if (ret <= 0)
    {
        // LOG_ERRO("can recv failed\r\n");
        return -1;
    }

    if (_save_can_data)
    {
        TraceCanRecvFrame(aframe);
    }

    return ret;
}
