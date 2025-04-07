/*
 * @Author: hanson
 * @Date: 2024-12-05 15:52:22
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-05 16:09:04
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\sensor\FlowSensor.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_SENSOR_FLOWSENSOR_HPP_
#define APPS_UDEPOT_INCLUDE_SENSOR_FLOWSENSOR_HPP_

#include <string>
#include "flow_sensor.h"
namespace auto_city
{
    namespace udepot
    {
        class FlowSensor
        {
        private:
            /* data */
            bool _is_setup;

        public:
            FlowSensor(/* args */) = default;
            ~FlowSensor() = default;

            int SetUp(const std::string &dev_name, int bitrates);

            float ReadInsFlowValue();

            float ReadTotalFlowValue();
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_SENSOR_FLOWSENSOR_HPP_
