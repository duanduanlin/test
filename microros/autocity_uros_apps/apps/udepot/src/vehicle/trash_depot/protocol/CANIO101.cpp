/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 14:59:42
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\protocol\CANIO101.cpp
 */
#include "vehicle/trash_depot/protocol/CANIO101.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            void CANIO101::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
            {
                parse_network_light_status(data, &chassis_detail->GetTrashDepotChassis()->network_light_status);
                parse_fault_light_status(data, &chassis_detail->GetTrashDepotChassis()->fault_light_status);
                parse_audio_play_status(data, &chassis_detail->GetTrashDepotChassis()->audio_play_status);
                parse_lift_strech_out_1(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_out_1);
                parse_lift_strech_out_2(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_out_2);
                parse_lift_strech_in_1(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_in_1);
                parse_lift_strech_in_2(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_in_2);
            }

            void CANIO101::UpdateCmd(uint64_t *data)
            {
                _data_to_update = 0;
                update_network_light_status();
                update_fault_light_status();
                update_audio_play_status();
                update_lift_strech_out_1();
                update_lift_strech_out_2();
                update_lift_strech_in_1();
                update_lift_strech_in_2();
                *data = ReverseByteOrder(_data_to_update);
            }

            void CANIO101::ResetCmd()
            { // Manual inspection!
                _network_light_status = 0;
                _fault_light_status = 0;
                _audio_play_status = 0;
                _lift_strech_out = 0;
                _lift_strech_in = 0;
            }

            void CANIO101::parse_lift_strech_out_1(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 4)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_lift_strech_out_2(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 5)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_lift_strech_in_1(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 6)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_lift_strech_in_2(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 7)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_audio_play_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 0)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_network_light_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 1)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::parse_fault_light_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 3)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO101::update_audio_play_status()
            {
                uint64_t x = CmdToHex(_audio_play_status, 1, 0) & 0x1;
                x <<= Motorola(0, 0);
                _data_to_update |= x;
            }

            void CANIO101::update_network_light_status()
            {
                uint64_t x = CmdToHex(_network_light_status, 1, 0) & 0x1;
                x <<= Motorola(0, 1);
                _data_to_update |= x;
            }

            void CANIO101::update_fault_light_status()
            {
                uint64_t x = CmdToHex(_fault_light_status, 1, 0) & 0x1;
                x <<= Motorola(0, 3);
                _data_to_update |= x;
            }

            void CANIO101::update_lift_strech_out_1()
            {
                uint64_t x = CmdToHex(_lift_strech_out, 1, 0) & 0x1;
                x <<= Motorola(0, 4);
                _data_to_update |= x;
            }

            void CANIO101::update_lift_strech_out_2()
            {
                uint64_t x = CmdToHex(_lift_strech_out, 1, 0) & 0x1;
                x <<= Motorola(0, 5);
                _data_to_update |= x;
            }

            void CANIO101::update_lift_strech_in_1()
            {
                uint64_t x = CmdToHex(_lift_strech_in, 1, 0) & 0x1;
                x <<= Motorola(0, 6);
                _data_to_update |= x;
            }

            void CANIO101::update_lift_strech_in_2()
            {
                uint64_t x = CmdToHex(_lift_strech_in, 1, 0) & 0x1;
                x <<= Motorola(0, 7);
                _data_to_update |= x;
            }
        }
    }
}
