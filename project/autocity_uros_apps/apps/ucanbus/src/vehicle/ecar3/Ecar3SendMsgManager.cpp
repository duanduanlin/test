/*
 * @Author: hanson
 * @Date: 2024-08-28 10:06:49
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-03 16:16:01
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\Ecar3SendMsgManager.cpp
 */
#include "vehicle/ecar3/Ecar3SendMsgManager.hpp"
#include "vehicle/ecar3/protocol/send/RDCU118.hpp"
#include "vehicle/ecar3/protocol/send/RDCU119.hpp"
#include "vehicle/ecar3/protocol/send/RDCU154.hpp"
#include "vehicle/ecar3/protocol/send/RDCU155.hpp"
#include "vehicle/ecar3/protocol/send/RDCU6F0.hpp"
#include "trace/LogTrace.hpp"

Ecar3SendMsgManager::Ecar3SendMsgManager(/* args */)
{
}

Ecar3SendMsgManager::~Ecar3SendMsgManager()
{
}

int Ecar3SendMsgManager::Setup()
{
    LOG_INFO("setup send msg manager\r\n");
    AddProtocol<RDCU118, true>();
    AddProtocol<RDCU119, true>();
    AddProtocol<RDCU154, true>();
    AddProtocol<RDCU155, true>();
    AddProtocol<RDCU6F0, true>();
    return 0;
}

std::vector<can_frame> Ecar3SendMsgManager::GetCanFrames()
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
