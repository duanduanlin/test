/*
 * @Author: hanson
 * @Date: 2024-08-23 17:24:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:47:15
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\node\UdepotNode.cpp
 */
#include "node/UdepotNode.hpp"
#include "trace/LogTrace.hpp"
#include "trace/TopicTrace.hpp"
#include "param/ParamHelper.hpp"

template <typename MessageT>
MessageT BaseNode::Subscriber<MessageT>::_msg;

template <typename MessageT>
void (*BaseNode::Subscriber<MessageT>::_onRecv)(MessageT &msg) = nullptr;

bool UdepotNode::_save_publish_data = false;

UdepotNode::UdepotNode(const std::string &node_name) : BaseNode(node_name)
{
    _save_publish_data = GetParamWithDefault<bool>("save_publish_data", false);
}

UdepotNode::~UdepotNode()
{
}

int UdepotNode::Setup()
{
    LOG_INFO("Setup UdepotNode\r\n");
    if (!IsOk())
    {
        return -1;
    }

    _water_depot_cmd_sub = CreateSubscription<WaterDepotCmdMsgWrap>("/udepot/water_depot_cmd", &UdepotNode::_control_callback);
    if (_water_depot_cmd_sub == nullptr)
    {
        LOG_ERRO("create _water_depot_cmd_sub failed\r\n");
        return -1;
    }

    _water_depot_status_pub = CreatePublisher<WaterDepotStatusMsgWrap>("/udepot/water_depot_status");
    if (_water_depot_status_pub == nullptr)
    {
        LOG_ERRO("create _water_depot_status_pub failed\r\n");
        return -1;
    }
    return 0;
}

WaterDepotCmdMsgWrap *UdepotNode::GetWaterDepotCmdMsg()
{
    return _water_depot_cmd_sub->GetMsg();
}

void UdepotNode::_control_callback(WaterDepotCmdMsgWrap &msg)
{
    msg.SetTime();
    if (_save_publish_data)
        TraceWaterDepotCmdTopic(msg);
    LOG_INFO_EVERY_SECOND("got cmd len %d\n", msg.GetMsgLen());
}

void UdepotNode::PublishWaterDepotStatus(WaterDepotStatusMsgWrap &msg)
{
    msg.Update();
    _water_depot_status_pub->Publish(msg);
    if (_save_publish_data)
        TraceWaterDepotStatusTopic(msg);
    LOG_INFO_EVERY_SECOND("send status len %d\n", msg.GetMsgLen());
}
