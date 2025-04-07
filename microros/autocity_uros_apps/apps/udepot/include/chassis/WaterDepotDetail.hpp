/*
 * @Author: hanson
 * @Date: 2024-10-15 10:52:46
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:12:51
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\chassis\WaterDepotDetail.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_CHASSIS_WATERDEPOTDETAIL_HPP_
#define APPS_UDEPOT_INCLUDE_CHASSIS_WATERDEPOTDETAIL_HPP_

namespace auto_city
{
    namespace udepot
    {
        class WaterDepotDetail
        {
        public:
            /* data */
            /// 网络指示灯
            uint8_t network_light_status;
            /// 加水作业指示灯
            uint8_t work_light_status;
            /// 故障指示灯
            uint8_t fault_light_status;
            /// 瞬时流量
            float instantaneous_flow;
            /// 总流量
            float total_flow;
            /// 水阀开关
            uint8_t water_valve_status;
            /// 急停按钮
            uint8_t estop_button_status;
            /// 加水按钮
            uint8_t water_button_status;

        public:
            WaterDepotDetail(/* args */) = default;
            ~WaterDepotDetail() = default;
        };
    }
}

#endif // APPS_UDEPOT_INCLUDE_CHASSIS_WATERDEPOTDETAIL_HPP_
