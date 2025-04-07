/*
 * @Author: hanson
 * @Date: 2024-08-23 16:19:50
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-03 14:42:21
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\transport\Transport.cpp
 */
#include <thread>
#include "transport/Transport.hpp"
// #include "common/TaskRequestStatusBridge.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        static void _recv_thread_handler()
        {
            while (1)
            {
                auto handler = SingleTonTransport::Instance().GetTransportHandler();
                if (handler != nullptr)
                {
                    handler->HandleRecvData();
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        static void _send_thread_handler()
        {
            while (1)
            {
                auto handler = SingleTonTransport::Instance().GetTransportHandler();
                if (handler != nullptr)
                {
                    handler->HandleSendData();
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        static void _pub_thread_handler()
        {
            while (1)
            {
                auto handler = SingleTonTransport::Instance().GetTransportHandler();
                if (handler != nullptr)
                {
                    handler->HandlePubMsg();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        Transport::Transport() : _handler(nullptr) /*, _send_msg_manager(nullptr), _vehicle_controller(nullptr)*/
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

        int Transport::Setup(std::shared_ptr<BaseTransportHandler> handler)
        {
            if (handler == nullptr)
            {
                LOG_ERRO("invalid param\r\n");
                return -1;
            }
            LOG_INFO("Setup Transport\r\n");

            _handler = handler;

            return 0;
        }
    }
}
