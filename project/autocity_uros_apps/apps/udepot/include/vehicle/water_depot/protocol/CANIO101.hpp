/*
 * @Author: hanson
 * @Date: 2024-08-29 18:30:21
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 17:12:04
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\protocol\CANIO101.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_CANIO101_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_CANIO101_HPP_

#include "protocol/BaseProtocol.hpp"

class CANIO101 : public BaseProtocol
{
private:
    /// 网络指示灯
    uint8_t _network_light_status;
    /// 加水作业指示灯
    uint8_t _work_light_status;
    /// 故障指示灯
    uint8_t _fault_light_status;
    /// 水阀开关
    uint8_t _water_valve_status;

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

    void SetWorkLight(const uint8_t val)
    {
        _work_light_status = val;
    }

    void SetFaultLight(const uint8_t val)
    {
        _fault_light_status = val;
    }

    void SetWaterValve(const uint8_t val)
    {
        _water_valve_status = val;
    }

private:
    void parse_water_valve_status(const uint64_t data, uint8_t *singal) const;
    void parse_network_light_status(const uint64_t data, uint8_t *singal) const;
    void parse_work_light_status(const uint64_t data, uint8_t *singal) const;
    void parse_fault_light_status(const uint64_t data, uint8_t *singal) const;

    void update_network_light_status();
    void update_work_light_status();
    void update_fault_light_status();
    void update_water_valve_status();
};

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_PROTOCOL_CANIO101_HPP_
