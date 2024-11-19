/*
 * @Author: hanson
 * @Date: 2024-08-28 15:28:17
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-20 16:59:35
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\vehicle\BaseVehicleController.hpp
 */
#ifndef INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_
#define INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_

#include <unordered_map>
#include "msg_wrap/ControlMsgWrap.hpp"
#include "msg_wrap/ChassisMsgWrap.hpp"
#include "protocol/BaseProtocol.hpp"
#include "common/TaskRequestStatusBridge.hpp"

class BaseVehicleController
{
protected:
    /* data */
    ControlMsgWrap *_control_cmd_msg;
    ChassisDetail *_chassis_detail;
    std::shared_ptr<TaskRequestStatusBridge> _task_request_status_bridge;

public:
    BaseVehicleController(/* args */) = default;
    virtual ~BaseVehicleController() = default;

    virtual int Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, ControlMsgWrap *msg, ChassisDetail *chassis) = 0;
    virtual int UpdateControlCmd() = 0;

    std::shared_ptr<TaskRequestStatusBridge> GetTaskRequestStatusBridge() const
    {
        return _task_request_status_bridge;
    }

    void SetTaskRequestStatusBridge(std::shared_ptr<TaskRequestStatusBridge> task_request_status_bridge)
    {
        _task_request_status_bridge = task_request_status_bridge;
    }
};

#endif // INCLUDE_VEHICLE_BASEVEHICLECONTROLLER_HPP_
