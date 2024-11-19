/*
 * @Author: hanson
 * @Date: 2024-08-23 17:24:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-30 11:09:36
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\node\UcanbusNode.cpp
 */
#include "node/UcanbusNode.hpp"
#include "trace/TopicTrace.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

template <typename MessageT>
MessageT BaseNode::Subscriber<MessageT>::_msg;

template <typename MessageT>
void (*BaseNode::Subscriber<MessageT>::_onRecv)(MessageT &msg) = nullptr;

bool UcanbusNode::_save_publish_data = false;

UcanbusNode::UcanbusNode(const std::string &node_name) : BaseNode(node_name)
{
    _save_publish_data = GetParamWithDefault<bool>("save_publish_data", false);
}

UcanbusNode::~UcanbusNode()
{
}

int UcanbusNode::Setup()
{
    LOG_INFO("Setup UcanbusNode\r\n");
    if (!IsOk())
    {
        return -1;
    }

    // _std_pub = CreatePublisher<StdMsgWrap>("/ucanbus/test");

    // if (_std_pub == nullptr)
    // {
    //     LOG_ERRO("create _std_pub failed\r\n");
    //     return -1;
    // }
    _chassic_pub = CreatePublisher<ChassisMsgWrap>("/ucanbus/chassis");
    if (_chassic_pub == nullptr)
    {
        LOG_ERRO("create _chassic_pub failed\r\n");
        return -1;
    }

    _control_cmd_sub = CreateSubscription<ControlMsgWrap>("/ucanbus/control_cmd", &UcanbusNode::_control_callback);
    if (_control_cmd_sub == nullptr)
    {
        LOG_ERRO("create _control_cmd_sub failed\r\n");
        return -1;
    }
    return 0;
}

void UcanbusNode::PublishChassis(ChassisMsgWrap &msg)
{
    msg.Update();
    _chassic_pub->Publish(msg);
    if (_save_publish_data)
        TraceChassisTopic(msg);
    LOG_INFO_EVERY_SECOND("send chassis len %d\n", msg.GetMsgLen());
}

// void UcanbusNode::PublishStdMsg(StdMsgWrap &msg)
// {
//     LOG_DEBG("PublishStdMsg 0\r\n");
//     msg.Update();
//     LOG_DEBG("PublishStdMsg 1\r\n");
//     _std_pub->Publish(msg);
//     LOG_DEBG("PublishStdMsg 2\r\n");
//     LOG_DEBG("send std len %d\n", msg.GetMsgLen());
// }

ControlMsgWrap *UcanbusNode::GetControlCmdMsg()
{
    return _control_cmd_sub->GetMsg();
}

void UcanbusNode::_control_callback(ControlMsgWrap &msg)
{
    msg.SetTime();
    if (_save_publish_data)
        TraceControlTopic(msg);
    LOG_INFO_EVERY_SECOND("got control len %d\n", msg.GetMsgLen());
}
