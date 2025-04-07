/*
 * @Author: hanson
 * @Date: 2024-08-22 13:44:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-02 16:17:54
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\BaseTransportHandler.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_BASETRANSPORTHANDLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_BASETRANSPORTHANDLER_HPP_

#include "vehicle/BaseDepotNode.hpp"
#include "cancard/BaseCancard.hpp"
#include "msg_manager/RecvMsgManager.hpp"
#include "msg_manager/SendMsgManager.hpp"

namespace auto_city
{
    namespace udepot
    {
        class BaseTransportHandler
        {
        protected:
            bool _is_setup;
            std::shared_ptr<BaseCancard> _cancard;
            std::shared_ptr<SendMsgManager> _send_msg_manager;

        public:
            BaseTransportHandler() = default;
            virtual ~BaseTransportHandler() = default;

            bool IsSetup()
            {
                return _is_setup;
            }

            virtual void Spin() = 0;

            virtual int Setup() = 0;

            virtual int HandleRecvData() = 0;

            virtual int HandleSendData() = 0;

            virtual int HandlePubMsg() = 0;
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_BASETRANSPORTHANDLER_HPP_
