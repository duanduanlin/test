/*
 * @Author: hanson
 * @Date: 2024-09-04 15:04:42
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-06 14:48:09
 * @Description:
 * @FilePath: \ucanbus\include\msg_manager\RecvMsgManager.hpp
 */
#ifndef INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_
#define INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_

#include "msg_manager/BaseMsgManager.hpp"
#include "msg_wrap/ChassisMsgWrap.hpp"
// #include "msg_wrap/StdMsgWrap.hpp"
#include "common/TaskRequestStatusBridge.hpp"
class RecvMsgManager : public BaseMsgManager
{
private:
    std::shared_ptr<TaskRequestStatusBridge> _task_request_status_bridge;

protected:
    /* data */
    ChassisDetail _chassis_detail;
    ChassisMsgWrap _chassis_msg_wrap;
    // StdMsgWrap _std_msg_wrap;

public:
    RecvMsgManager(/* args */) = default;
    virtual ~RecvMsgManager() = default;

    virtual int Setup() = 0;

    virtual void UpdateChassis() = 0;
    virtual void UpdateSweeperStatus() = 0;

    void ParseData(const uint32_t message_id, const uint8_t *const data)
    {
        BaseProtocol *protocol = GetProtocolById(message_id);
        if (protocol == nullptr)
            return;

        {
            protocol->ParseData(SplicingData(data), &_chassis_detail);
        }
        UpdateChassis();
        UpdateSweeperStatus();
    }

    ChassisMsgWrap &GetChassisMsg()
    {
        return _chassis_msg_wrap;
    }

    // StdMsgWrap &GetStdMsg()
    // {
    //     return _std_msg_wrap;
    // }

    std::shared_ptr<TaskRequestStatusBridge> GetTaskRequestStatusBridge() const
    {
        return _task_request_status_bridge;
    }

    void SetTaskRequestStatusBridge(std::shared_ptr<TaskRequestStatusBridge> task_request_status_bridge)
    {
        _task_request_status_bridge = task_request_status_bridge;
    }

    ChassisDetail *GetChassisDetail()
    {
        return &_chassis_detail;
    }
};

#endif // INCLUDE_MSG_MANAGER_RECVMSGMANAGER_HPP_
