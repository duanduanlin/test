/*
 * @Author: hanson
 * @Date: 2024-08-29 18:31:36
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-13 15:58:51
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\trash_depot\protocol\CANIO301.cpp
 */
#include "vehicle/trash_depot/protocol/CANIO301.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            void CANIO301::ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
            {
                parse_estop_button_status(data, &chassis_detail->GetTrashDepotChassis()->estop_button_status);
                parse_trash_open_button_status(data, &chassis_detail->GetTrashDepotChassis()->trash_open_button_status);
                parse_lift_strech_out_done(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_out_done);
                parse_lift_strech_in_done(data, &chassis_detail->GetTrashDepotChassis()->_lift_strech_in_done);
            }

            void CANIO301::parse_estop_button_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 1)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO301::parse_trash_open_button_status(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 0)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO301::parse_lift_strech_out_done(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 3)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }

            void CANIO301::parse_lift_strech_in_done(const uint64_t data, uint8_t *singal) const
            {
                uint8_t x = (data >> Motorola(0, 2)) & 0x1;
                uint8_t m = 0;
                HexToDecimal(x, 1, 0, &m);
                *singal = m;
            }
        }
    }
}
