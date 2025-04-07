/*
 * @Author: hanson
 * @Date: 2024-08-23 17:24:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 11:21:14
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotNode.cpp
 */
#include "vehicle/water_depot/WaterDepotNode.hpp"
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
        namespace water
        {
            bool WaterDepotNode::_save_publish_data = false;

            WaterDepotNode::WaterDepotNode(const std::string &node_name) : BaseDepotNode(node_name)
            {
                _save_publish_data = GetParamWithDefault<bool>("save_publish_data", false);
            }

            WaterDepotNode::~WaterDepotNode()
            {
            }

            int WaterDepotNode::Setup(const std::string &sub_topic, const std::string &pub_topic)
            {
                LOG_INFO("Setup WaterDepotNode\r\n");
                if (!IsOk())
                {
                    return -1;
                }

                _depot_cmd_sub = CreateSubscription<WaterDepotCmdMsgWrap>(sub_topic, &WaterDepotNode::_control_callback);
                if (_depot_cmd_sub == nullptr)
                {
                    LOG_ERRO("create _depot_cmd_sub failed\r\n");
                    return -1;
                }

                _depot_status_pub = CreatePublisher<WaterDepotStatusMsgWrap>(pub_topic);
                if (_depot_status_pub == nullptr)
                {
                    LOG_ERRO("create _depot_status_pub failed\r\n");
                    return -1;
                }
                return 0;
            }

            WaterDepotCmdMsgWrap *WaterDepotNode::GetDepotCmdMsg()
            {
                return _depot_cmd_sub->GetMsg();
            }

            void WaterDepotNode::_control_callback(WaterDepotCmdMsgWrap &msg)
            {
                msg.SetTime();
                if (_save_publish_data)
                    TraceWaterDepotCmdTopic(msg);
                LOG_INFO_EVERY_SECOND("got cmd len %d\n", msg.GetMsgLen());
            }

            void WaterDepotNode::PublishDepotStatus(WaterDepotStatusMsgWrap &msg)
            {
                msg.Update();
                _depot_status_pub->Publish(msg);
                if (_save_publish_data)
                    TraceWaterDepotStatusTopic(msg);
                LOG_INFO_EVERY_SECOND("send status len %d\n", msg.GetMsgLen());
            }
        }
    }
}
