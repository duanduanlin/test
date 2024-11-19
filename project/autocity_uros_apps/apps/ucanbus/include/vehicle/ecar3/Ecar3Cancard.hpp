/*
 * @Author: hanson
 * @Date: 2024-08-27 11:26:37
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-02 17:30:46
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\Ecar3Cancard.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_ECAR3CANCARD_HPP_
#define INCLUDE_VEHICLE_ECAR3_ECAR3CANCARD_HPP_

#include "cancard/BaseCancard.hpp"

class Ecar3Cancard : public BaseCancard
{
private:
    /* data */
public:
    Ecar3Cancard(const std::string name);
    virtual ~Ecar3Cancard();

    int CanSend(std::vector<can_frame> &frames) override;
    int CanSend(can_frame &frame) override;

    int CanRecv(can_frame &aframe) override;
};

#endif // INCLUDE_VEHICLE_ECAR3_ECAR3CANCARD_HPP_
