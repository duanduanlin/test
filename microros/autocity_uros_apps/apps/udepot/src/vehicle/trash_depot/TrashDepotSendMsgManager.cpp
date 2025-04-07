/*
 * @Author: hanson
 * @Date: 2024-08-28 10:06:49
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 11:23:52
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\TrashDepotSendMsgManager.cpp
 */
#include "vehicle/trash_depot/TrashDepotSendMsgManager.hpp"
#include "vehicle/trash_depot/protocol/CANIO101.hpp"
#include "vehicle/trash_depot/protocol/CANIO201.hpp"
#include "trace/LogTrace.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            TrashDepotSendMsgManager::TrashDepotSendMsgManager(/* args */)
            {
            }

            TrashDepotSendMsgManager::~TrashDepotSendMsgManager()
            {
            }

            int TrashDepotSendMsgManager::Setup()
            {
                LOG_INFO("setup send msg manager\r\n");
                AddProtocol<CANIO101, true>();
                AddProtocol<CANIO201, true>();
                return 0;
            }

            std::vector<can_frame> TrashDepotSendMsgManager::GetCanFrames()
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
        }
    }
}
