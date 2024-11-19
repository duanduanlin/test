#ifndef INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU250_HPP_
#define INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU250_HPP_

#include "protocol/BaseProtocol.hpp"

class CCU250 : public BaseProtocol
{
private:
    /* data */
public:
    CCU250(/* args */) : BaseProtocol(0x250)
    {
    }
    ~CCU250() = default;

    void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const override;

private:
    void parse_speed_kmph(const uint64_t data, double *singal) const;
    void parse_a_mpps(const uint64_t data, double *singal) const;
    void parse_motion_curvature(const uint64_t data, double *singal) const;
    void parse_run_direction(const uint64_t data, uint8_t *singal) const;
};

#endif // INCLUDE_VEHICLE_ECAR3_PROTOCOL_RECV_CCU250_HPP_
