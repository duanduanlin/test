/*
 * @Author: hanson
 * @Date: 2024-08-23 17:21:05
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:35:19
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\node\UdepotNode.hpp
 */

#ifndef __UCANBUS_INCLUDE_UCANBUSNODE__H_
#define __UCANBUS_INCLUDE_UCANBUSNODE__H_

#include "node/BaseNode.hpp"
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"

class UdepotNode : public BaseNode
{
private:
    std::shared_ptr<Subscriber<WaterDepotCmdMsgWrap>> _water_depot_cmd_sub;
    std::shared_ptr<Publisher<WaterDepotStatusMsgWrap>> _water_depot_status_pub;
    static bool _save_publish_data;

public:
    UdepotNode(const std::string &node_name);
    ~UdepotNode();

    int Setup();

    WaterDepotCmdMsgWrap *GetWaterDepotCmdMsg();

    void PublishWaterDepotStatus(WaterDepotStatusMsgWrap &msg);

private:
    static void _control_callback(WaterDepotCmdMsgWrap &msg);
};
#endif //__UCANBUS_INCLUDE_UCANBUSNODE__H_
