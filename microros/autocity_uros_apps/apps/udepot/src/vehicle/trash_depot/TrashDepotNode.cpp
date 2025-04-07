/*
 * @Author: hanson
 * @Date: 2024-08-23 17:24:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 11:21:38
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\TrashDepotNode.cpp
 */
#include "vehicle/trash_depot/TrashDepotNode.hpp"
#include "trace/LogTrace.hpp"
#include "trace/TopicTrace.hpp"
#include "param/ParamHelper.hpp"

template <typename MessageT>
MessageT auto_city::BaseNode::Subscriber<MessageT>::_msg;

template <typename MessageT>
void (*auto_city::BaseNode::Subscriber<MessageT>::_onRecv)(MessageT &msg) = nullptr;
namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            bool TrashDepotNode::_save_publish_data = false;

            TrashDepotNode::TrashDepotNode(const std::string &node_name) : BaseDepotNode(node_name)
            {
                _save_publish_data = GetParamWithDefault<bool>("save_publish_data", false);
            }

            TrashDepotNode::~TrashDepotNode()
            {
            }

            int TrashDepotNode::Setup(const std::string &sub_topic, const std::string &pub_topic)
            {
                LOG_INFO("Setup TrashDepotNode\r\n");
                if (!IsOk())
                {
                    return -1;
                }

                _depot_cmd_sub = CreateSubscription<TrashDepotCmdMsgWrap>(sub_topic, &TrashDepotNode::_control_callback);
                if (_depot_cmd_sub == nullptr)
                {
                    LOG_ERRO("create _depot_cmd_sub failed\r\n");
                    return -1;
                }

                _depot_status_pub = CreatePublisher<TrashDepotStatusMsgWrap>(pub_topic);
                if (_depot_status_pub == nullptr)
                {
                    LOG_ERRO("create _depot_status_pub failed\r\n");
                    return -1;
                }
                return 0;
            }

            TrashDepotCmdMsgWrap *TrashDepotNode::GetDepotCmdMsg()
            {
                return _depot_cmd_sub->GetMsg();
            }

            void TrashDepotNode::_control_callback(TrashDepotCmdMsgWrap &msg)
            {
                msg.SetTime();
                if (_save_publish_data)
                    TraceTrashDepotCmdTopic(msg);
                LOG_INFO_EVERY_SECOND("got cmd len %d\n", msg.GetMsgLen());
            }

            void TrashDepotNode::PublishDepotStatus(TrashDepotStatusMsgWrap &msg)
            {
                msg.Update();
                _depot_status_pub->Publish(msg);
                if (_save_publish_data)
                    TraceTrashDepotStatusTopic(msg);
                LOG_INFO_EVERY_SECOND("send status len %d\n", msg.GetMsgLen());
            }
        }
    }
}
