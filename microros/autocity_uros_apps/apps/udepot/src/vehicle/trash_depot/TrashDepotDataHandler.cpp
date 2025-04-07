#include "vehicle/trash_depot/TrashDepotTransportHandler.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            void TrashDepotTransportHandler::Spin()
            {
                _node->Spin();
            }

            int TrashDepotTransportHandler::Setup()
            {
                if (_is_setup)
                {
                    LOG_WARN("TrashDepotTransportHandler is already Setup\r\n");
                    return -1;
                }

                LOG_INFO("Setup TrashDepotTransportHandler\r\n");

                // auto task_request_status_bridge = std::make_shared<TaskRequestStatusBridge>();

                _node = std::make_shared<TrashDepotNode>("udepot");
                if (_node->Setup("/udepot/trash_depot_cmd", "/udepot/trash_depot_status") != 0)
                {
                    LOG_ERRO("depot node setup failed\r\n");
                    return -1;
                }

                _recv_msg_manager = std::make_shared<TrashDepotRecvMsgManager>();
                if (_recv_msg_manager->Setup() != 0)
                {
                    LOG_ERRO("recv msg manager setup failed\r\n");
                    return -1;
                }
                // _recv_msg_manager->SetTaskRequestStatusBridge(task_request_status_bridge);

                _send_msg_manager = std::make_shared<TrashDepotSendMsgManager>();
                if (_send_msg_manager->Setup() != 0)
                {
                    LOG_ERRO("send msg manager setup failed\r\n");
                    return -1;
                }

                _vehicle_controller = std::make_shared<TrashDepotController>();
                if (_vehicle_controller->Setup(_send_msg_manager->GetProtocolMap(), _node->GetDepotCmdMsg(), _recv_msg_manager->GetChassisDetail()) < 0)
                {
                    LOG_ERRO("vehicle controller setup failed\r\n");
                    return -1;
                }
                // _vehicle_controller->SetTaskRequestStatusBridge(task_request_status_bridge);

                _cancard = std::make_shared<TrashDepotCancard>(GetParamWithDefault<std::string>("can_interfaces", "can1"));
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

            int TrashDepotTransportHandler::HandleRecvData()
            {
                if (!IsSetup())
                {
                    sleep(1);
                    return -1;
                }

                if (_cancard != nullptr && _recv_msg_manager != nullptr)
                {
                    while (1)
                    {
                        can_frame frame;
                        if (_cancard->CanRecv(frame) == sizeof(can_frame))
                        {
                            // LOG_DEBG("got some data:0x%04x\r\n", frame.can_id);
                            _recv_msg_manager->ParseData(frame.can_id, frame.data);
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
                    LOG_WARN("_cancard == nullptr\r\n");
                }

                return 0;
            }

            int TrashDepotTransportHandler::HandleSendData()
            {
                if (!IsSetup())
                {
                    sleep(1);
                    return -1;
                }

                if (_cancard != nullptr && _vehicle_controller != nullptr)
                {
                    _vehicle_controller->UpdateControlCmd();
                    auto can_frames = _send_msg_manager->GetCanFrames();

                    _cancard->CanSend(can_frames);
                }
                else
                {
                    LOG_WARN("_cancard == nullptr\r\n");
                }

                return 0;
            }

            int TrashDepotTransportHandler::HandlePubMsg()
            {
                if (!IsSetup())
                {
                    sleep(1);
                    return -1;
                }

                if (_node != nullptr && _recv_msg_manager != nullptr)
                {
                    _recv_msg_manager->UpdateSensor();
                    // LOG_INFO("ins_clow:%f,total_flow:%f\r\n",flow_sensor_read_flow_value(),flow_sensor_read_total_flow_value());
                    _node->PublishDepotStatus(_recv_msg_manager->GetChassisMsg());
                }
                else
                {
                    LOG_WARN("_node == nullptr\r\n");
                }

                return 0;
            }
        }
    }
}
