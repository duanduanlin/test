/*
 * @Author: hanson
 * @Date: 2024-10-15 10:52:46
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-16 15:37:54
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\chassis\TrashDepotDetail.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_CHASSIS_TRASHDEPOTDETAIL_HPP_
#define APPS_UDEPOT_INCLUDE_CHASSIS_TRASHDEPOTDETAIL_HPP_

namespace auto_city
{
    namespace udepot
    {
        class TrashDepotDetail
        {
        public:
            /* data */
            /// 网络指示灯
            uint8_t network_light_status;
            /// 故障指示灯
            uint8_t fault_light_status;
            /// 语音播报状态
            uint8_t audio_play_status;
            /// 开盖按钮状态
            uint8_t trash_open_button_status;
            /// 急停按钮
            uint8_t estop_button_status;
            /// 满溢状态
            uint8_t trash_full_status;
            /// 垃圾桶状态
            uint8_t trash_status;
            /// 举升杆伸出1
            uint8_t _lift_strech_out_1;
            /// 举升杆伸出2
            uint8_t _lift_strech_out_2;
            /// 举升杆缩回1
            uint8_t _lift_strech_in_1;
            /// 举升杆缩回2
            uint8_t _lift_strech_in_2;
            /// 举升推杆推出到位
            uint8_t _lift_strech_out_done;
            /// 举升推杆缩回到位
            uint8_t _lift_strech_in_done;
            //垃圾箱传感器距离
            uint16_t trash_can_sensor_value;
            //垃圾量距离
            uint16_t garbage_sensor_value;

        public:
            TrashDepotDetail(/* args */) = default;
            ~TrashDepotDetail() = default;
        };
    }
}

#endif // APPS_UDEPOT_INCLUDE_CHASSIS_TRASHDEPOTDETAIL_HPP_
