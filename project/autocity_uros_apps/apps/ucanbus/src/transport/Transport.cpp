/*
 * @Author: hanson
 * @Date: 2024-08-23 16:19:50
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-29 11:40:19
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\transport\Transport.cpp
 */
#include <thread>
#include "transport/Transport.hpp"
#include "common/TaskRequestStatusBridge.hpp"
#include "trace/LogTrace.hpp"

static void _recv_thread_handler()
{
    while (1)
    {
        if (!SingleTonTransport::Instance().IsSetup())
        {
            sleep(1);
            continue;
        }
        auto cancard = SingleTonTransport::Instance().GetCancard();
        auto recv_manager = SingleTonTransport::Instance().GetRecvMsgManager();
        if (cancard != nullptr && recv_manager != nullptr)
        {
            while (1)
            {
                can_frame frame;
                if (cancard->CanRecv(frame) == sizeof(can_frame))
                {
                    // LOG_DEBG("got some data:0x%04x\r\n", frame.can_id);
                    recv_manager->ParseData(frame.can_id, frame.data);
                }
                else
                {
                    // LOG_ERRO("can recv failed\r\n");
                    break;
                }
                // usleep(1 * 1000);
            }
        }
        else
        {
            LOG_WARN("cancard == nullptr\r\n");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

static void _send_thread_handler()
{
    while (1)
    {
        if (!SingleTonTransport::Instance().IsSetup())
        {
            sleep(1);
            continue;
        }
        auto cancard = SingleTonTransport::Instance().GetCancard();
        auto vehicle = SingleTonTransport::Instance().GetVehicleController();

        if (cancard != nullptr && vehicle != nullptr)
        {
            vehicle->UpdateControlCmd();
            auto can_frames = SingleTonTransport::Instance().GetSendMsgManager()->GetCanFrames();

            cancard->CanSend(can_frames);
        }
        else
        {
            LOG_WARN("cancard == nullptr\r\n");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

static void _pub_thread_handler()
{
    while (1)
    {
        if (!SingleTonTransport::Instance().IsSetup())
        {
            sleep(1);
            continue;
        }
        auto recv_manager = SingleTonTransport::Instance().GetRecvMsgManager();
        auto node = SingleTonTransport::Instance().GetNode();
        if (node != nullptr)
        {
            node->PublishChassis(recv_manager->GetChassisMsg());
            // node->PublishStdMsg(recv_manager->GetStdMsg());
        }
        else
        {
            LOG_WARN("recv_manager == nullptr\r\n");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

Transport::Transport() : _node(nullptr), _is_setup(false), _vehicle_factory(nullptr), _cancard(nullptr), _recv_msg_manager(nullptr), _send_msg_manager(nullptr), _vehicle_controller(nullptr)
{
    std::thread recv_thread(_recv_thread_handler);
    std::thread send_thread(_send_thread_handler);
    std::thread pub_thread(_pub_thread_handler);

    recv_thread.detach();
    send_thread.detach();
    pub_thread.detach();
}

Transport::~Transport()
{
}

int Transport::Setup(std::shared_ptr<UcanbusNode> node, std::shared_ptr<BaseVehicleFactory> vehicle_factory)
{
    if (_is_setup)
    {
        LOG_WARN("Transport is already Setup\r\n");
        return -1;
    }

    if (node == nullptr || vehicle_factory == nullptr)
    {
        LOG_ERRO("invalid param\r\n");
        return -1;
    }
    LOG_INFO("Setup Transport\r\n");
    _node = node;
    _vehicle_factory = vehicle_factory;

    auto task_request_status_bridge = std::make_shared<TaskRequestStatusBridge>();

    _recv_msg_manager = vehicle_factory->CreateRecvMsgManager();
    if (_recv_msg_manager->Setup() != 0)
    {
        LOG_ERRO("recv msg manager setup failed\r\n");
        return -1;
    }
    _recv_msg_manager->SetTaskRequestStatusBridge(task_request_status_bridge);

    _send_msg_manager = vehicle_factory->CreateSendMsgManager();
    if (_send_msg_manager->Setup() != 0)
    {
        LOG_ERRO("send msg manager setup failed\r\n");
        return -1;
    }

    _vehicle_controller = vehicle_factory->CreateVehicleController();
    if (_vehicle_controller->Setup(_send_msg_manager->GetProtocolMap(), _node->GetControlCmdMsg(), _recv_msg_manager->GetChassisDetail()) < 0)
    {
        LOG_ERRO("vehicle controller setup failed\r\n");
        return -1;
    }
    _vehicle_controller->SetTaskRequestStatusBridge(task_request_status_bridge);

    _cancard = vehicle_factory->CreateCancard();
    if (_cancard->CanOpen() < 0)
    {
        LOG_ERRO("cancard open failed\r\n");
        return -1;
    }

    auto can_ids = _recv_msg_manager->GetIDs();

    if (_cancard->SetFilter(can_ids) < 0)
    {
        LOG_ERRO("cancard set filter failed\r\n");
        return -1;
    }

    _is_setup = true;
    return 0;
}
