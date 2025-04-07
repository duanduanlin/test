/*
 * @Author: hanson
 * @Date: 2024-08-23 17:21:05
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:26:16
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotNode.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_WATERDEPOTNODE_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_WATERDEPOTNODE_HPP_

#include "vehicle/BaseDepotNode.hpp"
#include "msg_wrap/TrashDepotCmdMsgWrap.hpp"
#include "msg_wrap/TrashDepotStatusMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotNode : public BaseDepotNode<TrashDepotCmdMsgWrap, TrashDepotStatusMsgWrap>
            {
            private:
                static bool _save_publish_data;

            public:
                TrashDepotNode(const std::string &node_name);
                virtual ~TrashDepotNode();

                int Setup(const std::string &sub_topic, const std::string &pub_topic) override;

                TrashDepotCmdMsgWrap *GetDepotCmdMsg() override;

                void PublishDepotStatus(TrashDepotStatusMsgWrap &msg) override;

            private:
                static void _control_callback(TrashDepotCmdMsgWrap &msg);
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTNODE_HPP_
