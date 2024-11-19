/*
 * @Author: hanson
 * @Date: 2024-08-23 17:26:10
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:34:03
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\msg_wrap\WaterDepotStatusMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"

WaterDepotStatusMsgWrap::WaterDepotStatusMsgWrap(/* args */) : BaseMsgWrap(WaterDepotStatusMsgType)
{
    Setup();
}

WaterDepotStatusMsgWrap::~WaterDepotStatusMsgWrap()
{
}

void WaterDepotStatusMsgWrap::Setup()
{
}

void WaterDepotStatusMsgWrap::Update()
{

}

void WaterDepotStatusMsgWrap::Reset()
{
}

std::string WaterDepotStatusMsgWrap::GetPrintableStr()
{
    std::stringstream ss;
    WaterDepotStatusMsg *msgs = GetMsg();
    ss << "net_light:" << msgs->network_light_status << " ";
    ss << "work_light:" << msgs->work_light_status << " ";
    ss << "fault_light:" << msgs->fault_light_status << " ";
    ss << "ins_flow:" << msgs->instantaneous_flow << " ";
    ss << "ins_flow:" << msgs->total_flow << " ";
    ss << "water_valve:" << msgs->water_valve_status << " ";
    ss << "estop_bt:" << msgs->estop_button_status << " ";
    ss << "water_bt:" << msgs->water_button_status << " ";

    return ss.str();
}
