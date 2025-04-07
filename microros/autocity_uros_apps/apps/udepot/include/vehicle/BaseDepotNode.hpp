/*
 * @Author: hanson
 * @Date: 2024-08-23 17:21:05
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:35:10
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\BaseDepotNode.hpp
 */

#ifndef INCLUDE_VEHICLE_WATER_DEPOT__NODE_BASEDEPOTNODE_HPP_
#define INCLUDE_VEHICLE_WATER_DEPOT__NODE_BASEDEPOTNODE_HPP_

#include "node/BaseNode.hpp"

namespace auto_city
{
    namespace udepot
    {
        template <typename MessageCMD, typename MessageStatus>
        class BaseDepotNode : public BaseNode
        {
        protected:
            std::shared_ptr<Subscriber<MessageCMD>> _depot_cmd_sub;
            std::shared_ptr<Publisher<MessageStatus>> _depot_status_pub;

        public:
            BaseDepotNode(const std::string &node_name) : BaseNode(node_name)
            {
            }
            virtual ~BaseDepotNode() = default;

            virtual int Setup(const std::string &sub_topic, const std::string &pub_topic) = 0;

            virtual MessageCMD *GetDepotCmdMsg() = 0;

            virtual void PublishDepotStatus(MessageStatus &msg) = 0;
        };

    }
}
#endif // INCLUDE_VEHICLE_WATER_DEPOT__NODE_BASEDEPOTNODE_HPP_
