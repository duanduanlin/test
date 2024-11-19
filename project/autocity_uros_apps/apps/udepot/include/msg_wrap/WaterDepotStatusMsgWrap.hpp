/*
 * @Author: hanson
 * @Date: 2024-08-23 10:35:59
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:26:03
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_wrap\WaterDepotStatusMsgWrap.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTSTATUSMSGWRAP_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTSTATUSMSGWRAP_HPP_


#include <udepot_status_msgs/msg/water_depot_status.h>
#include "msg_wrap/BaseMsgWrap.hpp"

#define WaterDepotStatusMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(udepot_status_msgs, msg, WaterDepotStatus))

using WaterDepotStatusMsg = udepot_status_msgs__msg__WaterDepotStatus;
class WaterDepotStatusMsgWrap : public BaseMsgWrap<WaterDepotStatusMsg>
{

private:
    /* data */

public:
    WaterDepotStatusMsgWrap(/* args */);
    ~WaterDepotStatusMsgWrap();

    void Setup() override;
    void Update() override;
    void Reset() override;

    std::string GetPrintableStr() override;
};

#endif // APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTSTATUSMSGWRAP_HPP_
