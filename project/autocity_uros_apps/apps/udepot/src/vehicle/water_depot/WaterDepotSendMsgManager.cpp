/*
 * @Author: hanson
 * @Date: 2024-08-28 10:06:49
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 17:39:59
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotSendMsgManager.cpp
 */
#include "vehicle/water_depot/WaterDepotSendMsgManager.hpp"
#include "vehicle/water_depot/protocol/CANIO101.hpp"
#include "vehicle/water_depot/protocol/CANIO201.hpp"
#include "trace/LogTrace.hpp"

WaterDepotSendMsgManager::WaterDepotSendMsgManager(/* args */)
{
}

WaterDepotSendMsgManager::~WaterDepotSendMsgManager()
{
}

int WaterDepotSendMsgManager::Setup()
{
    LOG_INFO("setup send msg manager\r\n");
    AddProtocol<CANIO101, true>();
    AddProtocol<CANIO201, true>();
    return 0;
}

std::vector<can_frame> WaterDepotSendMsgManager::GetCanFrames()
{
    std::vector<can_frame> can_frames;
    std::unordered_map<uint32_t, BaseProtocol *> &protocol_map = GetProtocolMap();

    for (auto i : protocol_map)
    {
        BaseProtocol *protocol = i.second;
        can_frames.push_back(protocol->GetCanFrame());
    }

    return can_frames;
}
