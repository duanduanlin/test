/*
 * @Author: hanson
 * @Date: 2024-08-23 17:26:10
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-28 18:36:19
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\msg_wrap\TrashDepotStatusMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/TrashDepotStatusMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        TrashDepotStatusMsgWrap::TrashDepotStatusMsgWrap(/* args */) : BaseMsgWrap(TrashDepotStatusMsgType)
        {
            Setup();
        }

        TrashDepotStatusMsgWrap::~TrashDepotStatusMsgWrap()
        {
        }

        void TrashDepotStatusMsgWrap::Setup()
        {
        }

        void TrashDepotStatusMsgWrap::Update()
        {
        }

        void TrashDepotStatusMsgWrap::Reset()
        {
        }

        std::string TrashDepotStatusMsgWrap::GetPrintableStr()
        {
            std::stringstream ss;
            TrashDepotStatusMsg *msgs = GetMsg();
            ss << "net_light:" << msgs->network_light_status << " ";
            ss << "fault_light:" << msgs->fault_light_status << " ";
            ss << "estop_bt:" << msgs->estop_button_status << " ";

            return ss.str();
        }
    }
}
