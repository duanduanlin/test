/*
 * @Author: hanson
 * @Date: 2024-08-29 15:58:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-29 15:59:54
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\protocol\recv\CCU219.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU219_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU219_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU219 : public BaseProtocol
{
private:
    /* data */
public:
    CCU219(/* args */) : BaseProtocol(0x219)
    {
    }
    ~CCU219() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_acostoptic_work_mode(const uint64_t data, uint8_t *singal) const;
    void parse_head_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_double_flash(const uint64_t data, uint8_t *singal) const;
    void parse_left_turn_light(const uint64_t data, uint8_t *singal) const;
    void parse_right_turn_light(const uint64_t data, uint8_t *singal) const;
    void parse_back_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_buzzer(const uint64_t data, uint8_t *singal) const;
    void parse_horn(const uint64_t data, uint8_t *singal) const;
    void parse_run_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_brake_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_fog_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_width_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_wiper(const uint64_t data, uint8_t *singal) const;
    void parse_warn_lamp(const uint64_t data, uint8_t *singal) const;
    void parse_flood_light(const uint64_t data, uint8_t *singal) const;
    void parse_siren(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU219_HPP_
