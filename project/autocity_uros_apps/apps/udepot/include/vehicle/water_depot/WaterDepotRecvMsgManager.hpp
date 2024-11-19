#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_

#include "msg_manager/RecvMsgManager.hpp"

class WaterDepotRecvMsgManager : public RecvMsgManager
{
private:
    /* data */
public:
    WaterDepotRecvMsgManager(/* args */) = default;
    virtual ~WaterDepotRecvMsgManager() = default;

    int Setup() override;

    void UpdateChassis() override;
};


#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_
