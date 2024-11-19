/*
 * @Author: hanson
 * @Date: 2024-08-27 17:49:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-13 16:56:45
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotRecvMsgManager.cpp
 */
#include "vehicle/water_depot/WaterDepotRecvMsgManager.hpp"
#include "vehicle/water_depot/protocol/CANIO101.hpp"
#include "vehicle/water_depot/protocol/CANIO201.hpp"
#include "vehicle/water_depot/protocol/CANIO301.hpp"
#include "trace/LogTrace.hpp"

int WaterDepotRecvMsgManager::Setup()
{
    LOG_INFO("recv manager setup\r\n");
    AddProtocol<CANIO101, true>();
    AddProtocol<CANIO201, true>();
    AddProtocol<CANIO301, true>();
    return 0;
}

void WaterDepotRecvMsgManager::UpdateChassis()
{
    auto chassis_detail = _chassis_detail.GetWaterDepotChassis();
    WaterDepotStatusMsg *chassis_msgs = _chassis_msg_wrap.GetMsg();
    _chassis_msg_wrap.Lock();
    chassis_msgs->network_light_status = chassis_detail->network_light_status;
    chassis_msgs->work_light_status = chassis_detail->work_light_status;
    chassis_msgs->fault_light_status = chassis_detail->fault_light_status;
    chassis_msgs->water_valve_status = chassis_detail->water_valve_status;
    chassis_msgs->estop_button_status = chassis_detail->estop_button_status;
    chassis_msgs->water_button_status = chassis_detail->water_button_status;
    _chassis_msg_wrap.Unlock();
}
