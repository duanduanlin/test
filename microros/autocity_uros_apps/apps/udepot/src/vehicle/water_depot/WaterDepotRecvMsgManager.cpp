/*
 * @Author: hanson
 * @Date: 2024-08-27 17:49:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-05 16:05:44
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotRecvMsgManager.cpp
 */
#include "vehicle/water_depot/WaterDepotRecvMsgManager.hpp"
#include "vehicle/water_depot/protocol/CANIO101.hpp"
#include "vehicle/water_depot/protocol/CANIO201.hpp"
#include "vehicle/water_depot/protocol/CANIO301.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            int WaterDepotRecvMsgManager::Setup()
            {
                LOG_INFO("recv manager setup\r\n");
                AddProtocol<CANIO101, true>();
                AddProtocol<CANIO201, true>();
                AddProtocol<CANIO301, true>();

                if (_flow_sensor.SetUp(GetParamWithDefault<std::string>("modbus_interfaces", "/dev/ttyS9").c_str(), GetParamWithDefault<int>("modbus_bitrate", 115200)) < 0)
                {
                    LOG_ERRO("sensor flow init failed\r\n");
                    // return -1;
                }
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

            void WaterDepotRecvMsgManager::UpdateSensor()
            {
                WaterDepotStatusMsg *chassis_msgs = _chassis_msg_wrap.GetMsg();
                _chassis_msg_wrap.Lock();
                chassis_msgs->instantaneous_flow = _flow_sensor.ReadInsFlowValue();
                chassis_msgs->total_flow = _flow_sensor.ReadTotalFlowValue();
                _chassis_msg_wrap.Unlock();
            }
        }
    }
}
