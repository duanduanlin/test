#ifndef INCLUDE_VEHICLE_ECAR3_ECAR3SENDMSGMANAGER_HPP_
#define INCLUDE_VEHICLE_ECAR3_ECAR3SENDMSGMANAGER_HPP_

#include "msg_manager/SendMsgManager.hpp"

class Ecar3SendMsgManager : public SendMsgManager
{
private:
    /* data */
public:
    Ecar3SendMsgManager(/* args */);
    virtual ~Ecar3SendMsgManager();

    int Setup() override;

    std::vector<can_frame> GetCanFrames() override;
};

#endif // INCLUDE_VEHICLE_ECAR3_ECAR3SENDMSGMANAGER_HPP_
