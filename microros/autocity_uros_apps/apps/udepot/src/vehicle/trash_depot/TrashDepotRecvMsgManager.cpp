/*
 * @Author: hanson
 * @Date: 2024-08-27 17:49:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-16 16:56:23
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\TrashDepotRecvMsgManager.cpp
 */
#include "vehicle/trash_depot/TrashDepotRecvMsgManager.hpp"
#include "vehicle/trash_depot/protocol/CANIO101.hpp"
#include "vehicle/trash_depot/protocol/CANIO201.hpp"
#include "vehicle/trash_depot/protocol/CANIO301.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            int TrashDepotRecvMsgManager::Setup()
            {
                LOG_INFO("recv manager setup\r\n");
                AddProtocol<CANIO101, true>();
                AddProtocol<CANIO201, true>();
                AddProtocol<CANIO301, true>();

                if (_radar_sensor.SetUp(GetParamWithDefault<std::string>("modbus_interfaces", "/dev/ttyS9").c_str(), GetParamWithDefault<int>("modbus_bitrate", 115200)) < 0)
                {
                    LOG_ERRO("sensor radar init failed\r\n");
                    // return -1;
                }

                return 0;
            }

            void TrashDepotRecvMsgManager::UpdateChassis()
            {
                auto chassis_detail = _chassis_detail.GetTrashDepotChassis();
                TrashDepotStatusMsg *chassis_msgs = _chassis_msg_wrap.GetMsg();
                _chassis_msg_wrap.Lock();
                chassis_msgs->network_light_status = chassis_detail->network_light_status;
                chassis_msgs->audio_play_status = chassis_detail->audio_play_status;
                chassis_msgs->fault_light_status = chassis_detail->fault_light_status;

                if (chassis_detail->_lift_strech_out_done)
                {
                    chassis_msgs->trash_open_status = udepot_status_msgs__msg__TrashDepotStatus__TRASH_CLOSE;
                }
                else if (chassis_detail->_lift_strech_in_done)
                {
                    chassis_msgs->trash_open_status = udepot_status_msgs__msg__TrashDepotStatus__TRASH_OPEN;
                }
                else
                {
                    chassis_msgs->trash_open_status = udepot_status_msgs__msg__TrashDepotStatus__TRASH_OPENING;
                }

                chassis_msgs->estop_button_status = chassis_detail->estop_button_status;
                chassis_msgs->trash_open_button_status = chassis_detail->trash_open_button_status;

                if (chassis_detail->trash_can_sensor_value < 300 && chassis_detail->trash_can_sensor_value > 200)
                {
                    chassis_msgs->trash_status = 1;
                }
                else
                {
                    chassis_msgs->trash_status = 0;
                }

                if (chassis_msgs->trash_status == 1 && chassis_msgs->trash_open_status == udepot_status_msgs__msg__TrashDepotStatus__TRASH_CLOSE)
                {
                    // 垃圾箱存在，并且垃圾盖关闭
                    if (chassis_detail->garbage_sensor_value != 0 && chassis_detail->garbage_sensor_value < 950)
                    {
                        // 数值正常
                        chassis_msgs->trash_full_status = (uint8_t)((950 - chassis_detail->garbage_sensor_value) / 950.0 * 100);
                    }
                    else
                    {
                        chassis_msgs->trash_full_status = 0xff;
                    }
                }

                _chassis_msg_wrap.Unlock();
            }

            void TrashDepotRecvMsgManager::UpdateSensor()
            {
                auto chassis_detail = _chassis_detail.GetTrashDepotChassis();
                chassis_detail->trash_can_sensor_value = _radar_sensor.ReadTrashCanValue();
                chassis_detail->garbage_sensor_value = _radar_sensor.ReadGabageValue();
                LOG_INFO("trash_can_sensor_value value:%d\r\n", chassis_detail->trash_can_sensor_value);
                LOG_INFO("garbage_sensor_value value:%d\r\n", chassis_detail->garbage_sensor_value);
            }

        }
    }
}
