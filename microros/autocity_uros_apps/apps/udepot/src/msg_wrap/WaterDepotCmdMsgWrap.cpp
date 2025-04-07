/*
 * @Author: hanson
 * @Date: 2024-08-23 17:27:19
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 17:55:20
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\msg_wrap\WaterDepotCmdMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        WaterDepotCmdMsgWrap::WaterDepotCmdMsgWrap(/* args */) : BaseMsgWrap(WaterDepotCmdMsgType)
        {
            Setup();
        }

        WaterDepotCmdMsgWrap::~WaterDepotCmdMsgWrap()
        {
        }

        void WaterDepotCmdMsgWrap::Setup()
        {
            memset(&_water_depot_cmd, 0, sizeof(WaterDepotCmdMsg));
        }

        void WaterDepotCmdMsgWrap::Update()
        {
            WaterDepotCmdMsg *msgs = GetMsg();
            memcpy(&_water_depot_cmd, msgs, sizeof(WaterDepotCmdMsg));
        }

        void WaterDepotCmdMsgWrap::Reset()
        {
            WaterDepotCmdMsg *msgs = GetMsg();
            Lock();
            memset(&_water_depot_cmd, 0, sizeof(WaterDepotCmdMsg));
            Unlock();
        }

        std::string WaterDepotCmdMsgWrap::GetPrintableStr()
        {
            std::stringstream ss;
            WaterDepotCmdMsg *msgs = GetMsg();
            ss << "net_light:" << msgs->network_light_cmd << " ";
            ss << "work_light:" << msgs->work_light_cmd << " ";
            ss << "fault_light:" << msgs->fault_light_cmd << " ";
            ss << "flow_reset:" << msgs->flow_reset_cmd << " ";
            ss << "water_valve:" << msgs->water_valve_cmd << " ";

            return ss.str();
        }
    }
}
