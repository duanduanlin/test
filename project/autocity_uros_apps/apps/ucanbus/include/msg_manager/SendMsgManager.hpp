#ifndef INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_
#define INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_

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

#endif // INCLUDE_MSG_MANAGER_SENDMSGMANAGER_HPP_
