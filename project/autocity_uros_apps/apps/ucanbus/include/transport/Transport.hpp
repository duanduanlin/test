/*
 * @Author: hanson
 * @Date: 2024-08-22 13:44:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 16:05:42
 * @Description:
 * @FilePath: \ucanbus\include\transport\Transport.hpp
 */
#ifndef __UCANBUS_INCLUDE_TRANSPORT__H_
#define __UCANBUS_INCLUDE_TRANSPORT__H_

#include "common/Singleton.hpp"
#include "node/UcanbusNode.hpp"
#include "vehicle/BaseVehicleFactory.hpp"

class Transport
{
private:
    bool _is_setup;
    std::shared_ptr<UcanbusNode> _node;
    std::shared_ptr<BaseVehicleFactory> _vehicle_factory;
    std::shared_ptr<BaseCancard> _cancard;
    std::shared_ptr<RecvMsgManager> _recv_msg_manager;
    std::shared_ptr<SendMsgManager> _send_msg_manager;
    std::shared_ptr<BaseVehicleController> _vehicle_controller;

public:
    Transport();
    virtual ~Transport();

    int Setup(std::shared_ptr<UcanbusNode> node, std::shared_ptr<BaseVehicleFactory> vehicle_factory);

    bool IsSetup()
    {
        return _is_setup;
    }

    std::shared_ptr<UcanbusNode> GetNode()
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
