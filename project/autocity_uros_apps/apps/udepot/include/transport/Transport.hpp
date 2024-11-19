/*
 * @Author: hanson
 * @Date: 2024-08-22 13:44:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-18 16:03:53
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\transport\Transport.hpp
 */
#ifndef __UCANBUS_INCLUDE_TRANSPORT__H_
#define __UCANBUS_INCLUDE_TRANSPORT__H_

#include "common/Singleton.hpp"
#include "node/UdepotNode.hpp"
#include "vehicle/BaseVehicleFactory.hpp"
#include "msg_manager/RecvMsgManager.hpp"
#include "msg_manager/SendMsgManager.hpp"
#include "vehicle/BaseVehicleController.hpp"
class Transport
{
private:
    bool _is_setup;
    std::shared_ptr<UdepotNode> _node;
    std::shared_ptr<BaseVehicleFactory> _vehicle_factory;
    std::shared_ptr<BaseCancard> _cancard;
    std::shared_ptr<RecvMsgManager> _recv_msg_manager;
    std::shared_ptr<SendMsgManager> _send_msg_manager;
    std::shared_ptr<BaseVehicleController> _vehicle_controller;

public:
    Transport();
    virtual ~Transport();

    int Setup(std::shared_ptr<UdepotNode> node, std::shared_ptr<BaseVehicleFactory> vehicle_factory);

    bool IsSetup()
    {
        return _is_setup;
    }

    std::shared_ptr<UdepotNode> GetNode()
    {
        return _node;
    }
    std::shared_ptr<BaseCancard> GetCancard()
    {
        return _cancard;
    }
    std::shared_ptr<RecvMsgManager> GetRecvMsgManager()
    {
        return _recv_msg_manager;
    }
    std::shared_ptr<SendMsgManager> GetSendMsgManager()
    {
        return _send_msg_manager;
    }
    std::shared_ptr<BaseVehicleController> GetVehicleController()
    {
        return _vehicle_controller;
    }
};

using SingleTonTransport = Singleton<Transport>;
#endif //__UCANBUS_INCLUDE_TRANSPORT__H_
