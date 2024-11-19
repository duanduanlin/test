/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 17:33:56
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\protocol\CANIO201.cpp
 */
#include "vehicle/water_depot/protocol/CANIO201.hpp"

void CANIO201::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_water_valve_status(data, &chassis_detail->GetWaterDepotChassis()->water_valve_status);
    parse_network_light_status(data, &chassis_detail->GetWaterDepotChassis()->network_light_status);
    parse_work_light_status(data, &chassis_detail->GetWaterDepotChassis()->work_light_status);
    parse_fault_light_status(data, &chassis_detail->GetWaterDepotChassis()->fault_light_status);
}

void CANIO201::UpdateCmd(uint64_t *data)
{
    _data_to_update = 0;
    *data = ReverseByteOrder(_data_to_update);
}

void CANIO201::ResetCmd()
{ // Manual inspection!
}

void CANIO201::parse_water_valve_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}

void CANIO201::parse_network_light_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 1)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}

void CANIO201::parse_work_light_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 2)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}

void CANIO201::parse_fault_light_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 3)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
