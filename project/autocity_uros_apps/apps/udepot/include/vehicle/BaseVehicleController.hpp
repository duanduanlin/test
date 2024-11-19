/*
 * @Author: hanson
 * @Date: 2024-08-28 15:28:17
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 14:24:30
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\BaseVehicleController.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_

#include <unordered_map>
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"
#include "protocol/BaseProtocol.hpp"
// #include "common/TaskRequestStatusBridge.hpp"

class BaseVehicleController
{
protected:
    /* data */
    WaterDepotCmdMsgWrap *_control_cmd_msg;
    ChassisDetail *_chassis_detail;
    // std::shared_ptr<TaskRequestStatusBridge> _task_request_status_bridge;

public:
    BaseVehicleController(/* args */) = default;
    virtual ~BaseVehicleController() = default;

    virtual int Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, WaterDepotCmdMsgWrap *msg, ChassisDetail *chassis) = 0;
    virtual int UpdateControlCmd() = 0;

    // std::shared_ptr<TaskRequestStatusBridge> GetTaskRequestStatusBridge() const
    // {
    //     return _task_request_status_bridge;
    // }

    // void SetTaskRequestStatusBridge(std::shared_ptr<TaskRequestStatusBridge> task_request_status_bridge)
    // {
    //     _task_request_status_bridge = task_request_status_bridge;
    // }
};


#endif // APPS_UDEPOT_INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_
