/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 16:40:39
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\protocol\CANIO301.cpp
 */
#include "vehicle/water_depot/protocol/CANIO301.hpp"

void CANIO301::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
{
    parse_water_button_status(data, &chassis_detail->GetWaterDepotChassis()->water_button_status);
    parse_estop_button_status(data, &chassis_detail->GetWaterDepotChassis()->estop_button_status);
}

void CANIO301::parse_water_button_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 0)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}

void CANIO301::parse_estop_button_status(const uint64_t data, uint8_t *singal) const
{
    uint8_t x = (data >> Motorola(0, 1)) & 0x1;
    uint8_t m = 0;
    HexToDecimal(x, 1, 0, &m);
    *singal = m;
}
