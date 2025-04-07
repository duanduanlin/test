/*
 * @Author: hanson
 * @Date: 2024-08-27 16:02:27
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:22:42
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\protocol\BaseProtocol.hpp
 */
#ifndef INCLUDE_PROTOCOL_BASEPROTOCOL_HPP_
#define INCLUDE_PROTOCOL_BASEPROTOCOL_HPP_

#include "stdint.h"
#include "chassis/ChassisDetail.hpp"

#include "common/can_support.hpp"

namespace auto_city
{
    namespace udepot
    {
        class BaseProtocol
        {
        protected:
            const uint8_t _data_length;
            uint64_t _data_to_update; // 更新控制命令到该变量
            uint8_t _rollcnt;         // 循环计数
            uint8_t _check_sum;       // 校验和
        private:
            /* data */
            can_frame _can_frame; // can桢

        public:
            BaseProtocol(uint32_t id) : _data_length(CANBUS_MESSAGE_LENGTH), _data_to_update(0), _rollcnt(0), _check_sum(0)
            {
                _can_frame.can_id = id;
                _can_frame.can_dlc = _data_length;
            }
            virtual ~BaseProtocol() = default;

            virtual void ParseData(const uint64_t data, ChassisDetail *chassis_detail) const
            {
                (void)data;
                (void)chassis_detail;
            }
            virtual void UpdateCmd(uint64_t *data)
            {
                (void)data;
            }
            virtual void ResetCmd()
            {
            }
            const uint8_t &GetDataLength() const
            {
                return _data_length;
            }
            uint32_t GetId() const
            {
                return _can_frame.can_id;
            }

            can_frame &GetCanFrame()
            {
                UpdateCmd((uint64_t *)_can_frame.data);
                return _can_frame;
            }

        protected:
            // 循环计数
            virtual void _update_rollcnt()
            {
                uint64_t x = _rollcnt;
                x <<= Motorola(6, 48);
                _rollcnt++;
                if (_rollcnt == 16)
                    _rollcnt = 0;
                _data_to_update |= x;
            }
            // 校验和
            virtual void _update_checksum()
            {
                uint64_t x = (CheckSum(_data_to_update) ^ 0xff);
                x <<= Motorola(7, 56);
                _data_to_update |= x;
            }
        };
    }
}
#endif // INCLUDE_PROTOCOL_BASEPROTOCOL_HPP_
