/*
 * @Author: hanson
 * @Date: 2024-10-15 14:03:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 14:03:57
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_manager\SendMsgManager.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_

#include "msg_manager/BaseMsgManager.hpp"

class SendMsgManager : public BaseMsgManager
{
private:
    /* data */
public:
    SendMsgManager(/* args */) = default;
    virtual ~SendMsgManager() = default;

    virtual int Setup() = 0;

    virtual std::vector<can_frame> GetCanFrames() = 0;
};

#endif // APPS_UDEPOT_INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_
