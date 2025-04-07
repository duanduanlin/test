/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 17:31:02
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\protocol\CANIO101.cpp
 */
#include "vehicle/water_depot/protocol/CANIO101.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            void CANIO101::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
            {
                parse_water_valve_status(data, &chassis_detail->GetWaterDepotChassis()->water_valve_status);
                parse_network_light_status(data, &chassis_detail->GetWaterDepotChassis()->network_light_status);
                parse_work_light_status(data, &chassis_detail->GetWaterDepotChassis()->work_light_status);
                parse_fault_light_status(data, &chassis_detail->GetWaterDepotChassis()->fault_light_status);
            }

            void CANIO101::UpdateCmd(uint64_t *data)
            {
                _data_to_update = 0;
                update_network_light_status();
                update_work_light_status();
                update_fault_light_status();
                update_water_valve_status();
                *data = ReverseByteOrder(_data_to_update);
            }

            void CANIO101::ResetCmd()
            { // Manual inspection!
                _network_light_status = 0;
                _work_light_status = 0;
                _fault_light_status = 0;
                _water_valve_status = 0;
            }

            void CANIO101::parse_water_valve_status(const uint64_t data, uint8_t *singal) const
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

            void CANIO101::parse_work_light_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 2)) & 0x1;
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

            void CANIO101::update_water_valve_status()
            {
                uint64_t x = CmdToHex(_water_valve_status, 1, 0) & 0x1;
                x <<= Motorola(0, 0);
                _data_to_update |= x;
            }

            void CANIO101::update_network_light_status()
            {
                uint64_t x = CmdToHex(_network_light_status, 1, 0) & 0x1;
                x <<= Motorola(0, 1);
                _data_to_update |= x;
            }

            void CANIO101::update_work_light_status()
            {
                uint64_t x = CmdToHex(_work_light_status, 1, 0) & 0x1;
                x <<= Motorola(0, 2);
                _data_to_update |= x;
            }

            void CANIO101::update_fault_light_status()
            {
                uint64_t x = CmdToHex(_fault_light_status, 1, 0) & 0x1;
                x <<= Motorola(0, 3);
                _data_to_update |= x;
            }
        }
    }
}
