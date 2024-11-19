/*
 * @Author: hanson
 * @Date: 2024-08-28 15:59:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-08 17:52:07
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotController.cpp
 */
#include "vehicle/water_depot/WaterDepotController.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

int WaterDepotController::Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, WaterDepotCmdMsgWrap *msg, ChassisDetail *chassis)
{
    LOG_INFO("setup vehicle controller\r\n");
    if (msg == nullptr || chassis == nullptr)
    {
        LOG_ERRO("invalid param\r\n");
        return -1;
    }
    _control_cmd_msg = msg;
    _chassis_detail = chassis;

    _writeIO_101 = static_cast<CANIO101 *>(protocol_map[0x101]);
    _readIO_201 = static_cast<CANIO201 *>(protocol_map[0x201]);

    if (!_writeIO_101 || !_readIO_201)
    {
        LOG_ERRO("setup vehicle controller failed\r\n");
        return -1;
    }

    return 0;
}

int WaterDepotController::UpdateControlCmd()
{
    _control_cmd_msg->Update();
    auto chassis_detail = _chassis_detail->GetWaterDepotChassis();
    auto chassis_cmd = _control_cmd_msg->GetWaterDepotCmd();

    LOG_INFO_EVERY_SECOND("water_button_status:%d,estop_button_status:%d,water_valve:%d,fault_light:%d,work_light:%d,network_light:%d\r\n", chassis_detail->water_button_status, chassis_detail->estop_button_status,chassis_cmd.water_valve_cmd, chassis_cmd.fault_light_cmd, chassis_cmd.work_light_cmd, chassis_cmd.network_light_cmd);

    if (chassis_detail->water_button_status || chassis_cmd.water_valve_cmd)
    {
        _writeIO_101->SetWaterValve(1);
        _writeIO_101->SetWorkLight(1);
    }
    else
    {
        _writeIO_101->SetWaterValve(0);
        _writeIO_101->SetWorkLight(0);
    }

    if (chassis_detail->estop_button_status || chassis_cmd.fault_light_cmd)
    {
        _writeIO_101->SetFaultLight(0);
    }
    else
    {
        _writeIO_101->SetFaultLight(1);
    }

    _writeIO_101->SetNetLight(chassis_cmd.network_light_cmd);
    return 0;
}
