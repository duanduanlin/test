/*
 * @Author: hanson
 * @Date: 2024-08-27 16:12:31
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-27 16:15:53
 * @Description:
 * @FilePath: \ucanbus\include\chassis\ChassisDetail.hpp
 */
#ifndef INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
#define INCLUDE_CHASSIS_CHASSISDETAIL_HPP_

#include <memory>
#include "chassis/ECar3Chassis.hpp"

class ChassisDetail
{
private:
    /* data */
    std::shared_ptr<ECar3Chassis> ecar3_chassis_ = std::make_shared<ECar3Chassis>();

public:
    ChassisDetail(/* args */) = default;
    ~ChassisDetail() = default;

    std::shared_ptr<ECar3Chassis> GetEcar3Chassis() const
    {
        return ecar3_chassis_;
    }
};

#endif // INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
