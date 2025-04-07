/*
 * @Author: hanson
 * @Date: 2024-08-23 17:21:05
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-26 14:49:14
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotNode.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTNODE_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTNODE_HPP_

#include "vehicle/BaseDepotNode.hpp"
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotNode : public BaseDepotNode<WaterDepotCmdMsgWrap, WaterDepotStatusMsgWrap>
            {
            private:
                static bool _save_publish_data;

            public:
                WaterDepotNode(const std::string &node_name);
                virtual ~WaterDepotNode();

                int Setup(const std::string &sub_topic, const std::string &pub_topic) override;

                WaterDepotCmdMsgWrap *GetDepotCmdMsg() override;

                void PublishDepotStatus(WaterDepotStatusMsgWrap &msg) override;

            private:
                static void _control_callback(WaterDepotCmdMsgWrap &msg);
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTNODE_HPP_
