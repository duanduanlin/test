/*
 * @Author: hanson
 * @Date: 2024-08-28 15:55:50
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:25:19
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotController.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTCONTROLLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTCONTROLLER_HPP_

#include "vehicle/BaseVehicleController.hpp"
#include "common/TimeTools.hpp"
#include "vehicle/trash_depot/protocol/CANIO101.hpp"
#include "vehicle/trash_depot/protocol/CANIO201.hpp"
#include "msg_wrap/TrashDepotCmdMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotController : public BaseVehicleController<TrashDepotCmdMsgWrap>
            {
            private:
                /* data */
                /*chassis cmd */
                CANIO101 *_writeIO_101 = nullptr;
                CANIO201 *_readIO_201 = nullptr;
                /*task time*/

            public:
                TrashDepotController(/* args */) = default;
                virtual ~TrashDepotController() = default;

                int Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, TrashDepotCmdMsgWrap *msg, ChassisDetail *chassis) override;
                int UpdateControlCmd() override;

            private:
            };
        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTCONTROLLER_HPP_
