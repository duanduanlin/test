#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A6_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A6_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU2A6 : public BaseProtocol
{
private:
    /* data */
public:
    CCU2A6(/* args */) : BaseProtocol(0x2a6)
    {
    }
    ~CCU2A6() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_ccu_vehvin_c8(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c9(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c10(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_c11(const uint64_t data, uint8_t *singal) const;
    void parse_ccu_vehvin_d12_17(const uint64_t data, double *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU2A6_HPP_
