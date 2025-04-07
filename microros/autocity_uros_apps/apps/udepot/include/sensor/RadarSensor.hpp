/*
 * @Author: hanson
 * @Date: 2024-12-10 19:02:59
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-11 14:02:24
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\sensor\RadarSensor.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_SENSOR_RADARSENSOR_HPP_
#define APPS_UDEPOT_INCLUDE_SENSOR_RADARSENSOR_HPP_

#include <string>
#include "modbus_dev.h"

namespace auto_city
{
    namespace udepot
    {
        class RadarSensor
        {
        private:
            /* data */
            bool _is_setup;
            std::string _dev_name;
            int _bitrates;

        public:
            RadarSensor(/* args */);
            ~RadarSensor();

            int SetUp(const std::string &dev_name, int bitrates);

            int ReadGabageValue();

            int ReadTrashCanValue();
        };
    }
}

#endif // APPS_UDEPOT_INCLUDE_SENSOR_RADARSENSOR_HPP_
