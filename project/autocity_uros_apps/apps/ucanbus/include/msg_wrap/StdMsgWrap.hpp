/*
 * @Author: hanson
 * @Date: 2024-09-05 14:03:44
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-05 18:21:32
 * @Description:
 * @FilePath: \ucanbus\include\msg_wrap\StdMsgWrap.hpp
 */
#ifndef INCLUDE_MSG_WRAP_STDMSGWRAP_HPP_
#define INCLUDE_MSG_WRAP_STDMSGWRAP_HPP_

#include <std_msgs/msg/header.h>
#include "msg_wrap/BaseMsgWrap.hpp"

#define StdMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Header))

using StdMsg = std_msgs__msg__Header;

class StdMsgWrap : public BaseMsgWrap<StdMsg>
{
private:
    /* data */
    char _data_buffer[50];

public:
    StdMsgWrap(/* args */) : BaseMsgWrap(StdMsgType)
    {
        Setup();
        memset(_data_buffer, 0, 50);
    }
    ~StdMsgWrap() = default;
    void Setup() override
    {
        StdMsg *msgs = GetMsg();
        msgs->frame_id.data = _data_buffer;
        msgs->frame_id.capacity = 50;
    }
    void Update() override
    {
        struct timespec ts;
        StdMsg *msgs = GetMsg();
        Lock();
        // for (int i = 0; i < 100; i++)
        // {
        //     msgs->frame_id.data[i] = 'i';
        // }
        clock_gettime(CLOCK_REALTIME, &ts);
        msgs->stamp.sec = ts.tv_sec;
        msgs->stamp.nanosec = ts.tv_nsec;
        Unlock();
    }
    void Reset() override
    {

    }

    std::string GetPrintableStr() override { return "none"; }
};

#endif // INCLUDE_MSG_WRAP_STDMSGWRAP_HPP_
