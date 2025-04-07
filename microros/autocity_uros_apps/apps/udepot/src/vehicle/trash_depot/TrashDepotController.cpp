/*
 * @Author: hanson
 * @Date: 2024-08-28 15:59:38
 * @LastEditors: hanson
 * @LastEditTime: 2025-01-17 11:24:04
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\TrashDepotController.cpp
 */
#include "vehicle/trash_depot/TrashDepotController.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            int TrashDepotController::Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, TrashDepotCmdMsgWrap *msg, ChassisDetail *chassis)
            {
                LOG_INFO("setup vehicle controller\r\n");
                if (msg == nullptr || chassis == nullptr)
                {
                    LOG_ERRO("invalid param\r\n");
                    return -1;
                }
                _control_cmd_msg = msg;
                _chassis_detail = chassis;

                _writeIO_101 = static_cast<CANIO101 *>(protocol_map[0x101]);
                _readIO_201 = static_cast<CANIO201 *>(protocol_map[0x201]);

                if (!_writeIO_101 || !_readIO_201)
                {
                    LOG_ERRO("setup vehicle controller failed\r\n");
                    return -1;
                }

                return 0;
            }

            int TrashDepotController::UpdateControlCmd()
            {
                _control_cmd_msg->Update();
                auto chassis_detail = _chassis_detail->GetTrashDepotChassis();
                auto chassis_cmd = _control_cmd_msg->GetTrashDepotCmd();

                LOG_INFO_EVERY_SECOND("_lift_strech_out_done:%d,_lift_strech_in_done:%d\r\n", chassis_detail->_lift_strech_out_done, chassis_detail->_lift_strech_in_done);
                LOG_INFO_EVERY_SECOND("trash_open_button_status:%d,estop_button_status:%d,trash_open_cmd:%d,fault_light:%d,audio_play_cmd:%d,network_light:%d\r\n", chassis_detail->trash_open_button_status, chassis_detail->estop_button_status, chassis_cmd.trash_open_cmd, chassis_cmd.fault_light_cmd, chassis_cmd.audio_play_cmd, chassis_cmd.network_light_cmd);

                if (chassis_detail->trash_open_button_status || chassis_cmd.trash_open_cmd)
                {
                    _writeIO_101->SetLiftStrechOut(0);
                    _writeIO_101->SetLiftStrechIn(1);
                    // 提示音
                    if (!chassis_detail->_lift_strech_in_done)
                    {
                        LOG_INFO_EVERY_SECOND("Trash opening\r\n");
                        _writeIO_101->SetAudioPlay(1);
                    }
                    else
                    {
                        LOG_INFO_EVERY_SECOND("Trash open done\r\n");
                        _writeIO_101->SetAudioPlay(0);
                    }
                }
                else
                {
                    _writeIO_101->SetLiftStrechOut(1);
                    _writeIO_101->SetLiftStrechIn(0);
                    // 提示音
                    if (!chassis_detail->_lift_strech_out_done)
                    {
                        LOG_INFO_EVERY_SECOND("Trash closing\r\n");
                        _writeIO_101->SetAudioPlay(1);
                    }
                    else
                    {
                        LOG_INFO_EVERY_SECOND("Trash close done\r\n");
                        _writeIO_101->SetAudioPlay(0);
                    }
                }

                // if (chassis_cmd.audio_play_cmd)
                // {
                //     _writeIO_101->SetAudioPlay(1);
                // }
                // else
                // {
                //     _writeIO_101->SetAudioPlay(0);
                // }

                if (!chassis_detail->estop_button_status || chassis_cmd.fault_light_cmd)
                {
                    _writeIO_101->SetFaultLight(1);
                }
                else
                {
                    _writeIO_101->SetFaultLight(0);
                }

                _writeIO_101->SetNetLight(chassis_cmd.network_light_cmd);
                return 0;
            }
        }
    }
}
