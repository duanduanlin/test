/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 15:16:24
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\protocol\CANIO201.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_RECV_CANIO201_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_RECV_CANIO201_HPP_

#include "protocol/BaseProtocol.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class CANIO201 : public BaseProtocol
            {
            private:
            public:
                CANIO201(/* args */) : BaseProtocol(0x201)
                {
                }
                ~CANIO201() = default;

                void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

                void UpdateCmd(uint64_t *data) override;
                void ResetCmd() override;

            private:
                void parse_network_light_status(const uint64_t data, uint8_t *singal) const;
                void parse_fault_light_status(const uint64_t data, uint8_t *singal) const;
                void parse_audio_play_status(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_out_1(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_out_2(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_in_1(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_in_2(const uint64_t data, uint8_t *singal) const;
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_RECV_CANIO201_HPP_
