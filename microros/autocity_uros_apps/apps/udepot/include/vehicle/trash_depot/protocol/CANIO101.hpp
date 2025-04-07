/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 14:50:45
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\protocol\CANIO101.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO101_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO101_HPP_

#include "protocol/BaseProtocol.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class CANIO101 : public BaseProtocol
            {
            private:
                /// 网络指示灯
                uint8_t _network_light_status;
                /// 故障指示灯
                uint8_t _fault_light_status;
                /// 语音播报状态
                uint8_t _audio_play_status;
                /// 举升杆伸出
                uint8_t _lift_strech_out;
                /// 举升杆缩回
                uint8_t _lift_strech_in;

            public:
                CANIO101(/* args */) : BaseProtocol(0x101)
                {
                }
                ~CANIO101() = default;

                void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

                void UpdateCmd(uint64_t *data) override;
                void ResetCmd() override;

                void SetNetLight(const uint8_t val)
                {
                    _network_light_status = val;
                }

                void SetFaultLight(const uint8_t val)
                {
                    _fault_light_status = val;
                }

                void SetAudioPlay(const uint8_t val)
                {
                    _audio_play_status = val;
                }

                void SetLiftStrechOut(const uint8_t val)
                {
                    _lift_strech_out = val;
                }

                void SetLiftStrechIn(const uint8_t val)
                {
                    _lift_strech_in = val;
                }

            private:
                void parse_network_light_status(const uint64_t data, uint8_t *singal) const;
                void parse_fault_light_status(const uint64_t data, uint8_t *singal) const;
                void parse_audio_play_status(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_out_1(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_out_2(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_in_1(const uint64_t data, uint8_t *singal) const;
                void parse_lift_strech_in_2(const uint64_t data, uint8_t *singal) const;

                void update_network_light_status();
                void update_fault_light_status();
                void update_audio_play_status();
                void update_lift_strech_out_1();
                void update_lift_strech_out_2();
                void update_lift_strech_in_1();
                void update_lift_strech_in_2();
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_PROTOCOL_CANIO101_HPP_
