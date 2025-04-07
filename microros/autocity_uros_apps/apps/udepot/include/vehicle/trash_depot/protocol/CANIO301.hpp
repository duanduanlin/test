/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 15:10:29
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\protocol\CANIO301.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO301_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO301_HPP_

#include "protocol/BaseProtocol.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class CANIO301 : public BaseProtocol
            {
            private:
            public:
                CANIO301(/* args */) : BaseProtocol(0x301)
                {
                }
                ~CANIO301() = default;

                void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

            private:
                void parse_estop_button_status(const uint64_t data, uint8_t *singal) const;
                void parse_trash_open_button_status(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_out_done(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_in_done(const uint64_t data, uint8_t *singal) const;
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO301_HPP_
