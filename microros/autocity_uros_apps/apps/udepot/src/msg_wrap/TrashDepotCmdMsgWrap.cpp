/*
 * @Author: hanson
 * @Date: 2024-08-23 17:27:19
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-28 18:34:01
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\msg_wrap\TrashDepotCmdMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/TrashDepotCmdMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        TrashDepotCmdMsgWrap::TrashDepotCmdMsgWrap(/* args */) : BaseMsgWrap(TrashDepotCmdMsgType)
        {
            Setup();
        }

        TrashDepotCmdMsgWrap::~TrashDepotCmdMsgWrap()
        {
        }

        void TrashDepotCmdMsgWrap::Setup()
        {
            memset(&_trash_depot_cmd, 0, sizeof(TrashDepotCmdMsg));
        }

        void TrashDepotCmdMsgWrap::Update()
        {
            TrashDepotCmdMsg *msgs = GetMsg();
            memcpy(&_trash_depot_cmd, msgs, sizeof(TrashDepotCmdMsg));
        }

        void TrashDepotCmdMsgWrap::Reset()
        {
            TrashDepotCmdMsg *msgs = GetMsg();
            Lock();
            memset(&_trash_depot_cmd, 0, sizeof(TrashDepotCmdMsg));
            Unlock();
        }

        std::string TrashDepotCmdMsgWrap::GetPrintableStr()
        {
            std::stringstream ss;
            TrashDepotCmdMsg *msgs = GetMsg();
            ss << "net_light:" << msgs->network_light_cmd << " ";
            ss << "fault_light:" << msgs->fault_light_cmd << " ";

            return ss.str();
        }
    }
}
