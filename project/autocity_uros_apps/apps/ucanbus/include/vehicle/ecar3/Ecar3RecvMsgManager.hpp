#ifndef INCLUDE_VEHICLE_ECAR3_ECAR3RECVMSGMANAGER_HPP_
#define INCLUDE_VEHICLE_ECAR3_ECAR3RECVMSGMANAGER_HPP_

#include "msg_manager/RecvMsgManager.hpp"

class Ecar3RecvMsgManager : public RecvMsgManager
{
private:
    /* data */
public:
    Ecar3RecvMsgManager(/* args */) = default;
    virtual ~Ecar3RecvMsgManager() = default;

    int Setup() override;

    void UpdateChassis() override;
    void UpdateSweeperStatus() override;
};

#endif // INCLUDE_VEHICLE_ECAR3_ECAR3RECVMSGMANAGER_HPP_
