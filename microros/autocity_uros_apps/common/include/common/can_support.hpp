/*
 * @Author: hanson
 * @Date: 2024-08-27 19:12:51
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-14 15:24:38
 * @Description:
 * @FilePath: \ucanbus\include\common\can_support.hpp
 */
#ifndef INCLUDE_COMMON_CAN_SUPPORT_HPP_
#define INCLUDE_COMMON_CAN_SUPPORT_HPP_

#include "socket_can.h"

namespace auto_city
{
#define CANBUS_MESSAGE_LENGTH 8
#define ONE_BYTE_SIZE 8

    typedef struct a_can_frame can_frame;
    typedef struct a_can_filter can_filter;

    static inline uint64_t ReverseByteOrder(uint64_t x)
    {
        x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
        x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
        x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
        return x;
    }

    static inline uint64_t SplicingData(const uint8_t *const data)
    {
        uint64_t spliced_data = 0;
        for (int i = 0; i < CANBUS_MESSAGE_LENGTH; i++)
        {
            spliced_data |= (uint64_t)data[i] << (7 - i) * 8;
        }
        return spliced_data;
    }

    static inline int64_t CmdToHex(const double cmd, const double precision, const double offset)
    {
        int64_t hex = (cmd - offset) / precision;
        return hex;
    }

    static inline uint64_t Motorola(const int start_byte, const int start_bit)
    {
        return start_bit % ONE_BYTE_SIZE + (7 - start_byte) * ONE_BYTE_SIZE;
    }

    static inline uint8_t CheckSum(uint64_t data)
    {
        uint8_t check_sum = 0;
        data >>= 8;
        for (int i = 0; i < 7; i++)
        {
            check_sum += (data & 0xff);
            data >>= 8;
        }
        return check_sum;
    }

    template <typename T>
    static inline T BoundedValue(const T value, T lower, T upper)
    {
        if (lower > upper)
        {
            std::swap(lower, upper);
        }
        if (value < lower)
        {
            return lower;
        }
        else if (value > upper)
        {
            return upper;
        }
        return value;
    }

    template <typename A, typename B>
    static inline void HexToDecimal(const A hex, const double precision, const double offset, B *tgt)
    {
        B x = (B)hex;
        x = x * precision + offset;
        *tgt = x;
    }
}
#endif // INCLUDE_COMMON_CAN_SUPPORT_HPP_
