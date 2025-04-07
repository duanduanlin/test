/*
 * @Author: hanson
 * @Date: 2024-09-04 15:04:42
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:15:09
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_manager\RecvMsgManager.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_

#include "msg_manager/BaseMsgManager.hpp"
// #include "common/TaskRequestStatusBridge.hpp"

namespace auto_city
{
    namespace udepot
    {
        template <typename MessageStatus>
        class RecvMsgManager : public BaseMsgManager
        {
        private:
            // std::shared_ptr<TaskRequestStatusBridge> _task_request_status_bridge;

        protected:
            /* data */
            ChassisDetail _chassis_detail;
            MessageStatus _chassis_msg_wrap;

        public:
            RecvMsgManager(/* args */) = default;
            virtual ~RecvMsgManager() = default;

            virtual int Setup() = 0;

            virtual void UpdateChassis() = 0;

            virtual void UpdateSensor() = 0;

            void ParseData(const uint32_t message_id, const uint8_t *const data)
            {
                BaseProtocol *protocol = GetProtocolById(message_id);
                if (protocol == nullptr)
                    return;

                {
                    protocol->ParseData(SplicingData(data), &_chassis_detail);
                }
                UpdateChassis();
            }

            MessageStatus &GetChassisMsg()
            {
                return _chassis_msg_wrap;
            }

            // StdMsgWrap &GetStdMsg()
            // {
            //     return _std_msg_wrap;
            // }

            // std::shared_ptr<TaskRequestStatusBridge> GetTaskRequestStatusBridge() const
            // {
            //     return _task_request_status_bridge;
            // }

            // void SetTaskRequestStatusBridge(std::shared_ptr<TaskRequestStatusBridge> task_request_status_bridge)
            // {
            //     _task_request_status_bridge = task_request_status_bridge;
            // }

            ChassisDetail *GetChassisDetail()
            {
                return &_chassis_detail;
            }
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_
