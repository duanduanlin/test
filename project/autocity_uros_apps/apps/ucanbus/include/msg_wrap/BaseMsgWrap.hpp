/*
 * @Author: hanson
 * @Date: 2024-08-23 10:06:04
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-20 18:52:55
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\msg_wrap\BaseMsgWrap.hpp
 */
#ifndef INCLUDE_MSG_WRAP_BASEMSGWRAP_HPP_
#define INCLUDE_MSG_WRAP_BASEMSGWRAP_HPP_

#include <rclc/rclc.h>
#include <mutex>

#include "common/TimeTools.hpp"

#define ROS_HEAD_BUFFER_LEN (64)

#define ROS_MODE_NAME_LEN (64)
#define ROS_MODE_NAME ("ucanbus")

#define ROS_VERSION_LEN (8)
#define ROS_VERSION ("1.0.0")

#define ROS_MSG_LEN (64)
#define ROS_MSG_DEFAULT ("")

#define ROS_VIN_LEN (20)
#define ROS_VIN_DEFAULT ("")

#define ROS_PLATE_LEN (20)
#define ROS_PLATE_DEFAULT ("")

#define ROS_UUID_LEN (20)
#define ROS_UUID_DEFAULT ("")

template <typename MessageT>
class BaseMsgWrap
{
private:
    /* data */
    const rosidl_message_type_support_t *_type;
    MessageT _msg;
    int _len;
    std::mutex _mutx;
    TimeTools _time;

public:
    BaseMsgWrap(const rosidl_message_type_support_t *type) : _type(type)
    {
        _len = sizeof(MessageT);
        memset(&_msg, 0, _len);
    }
    virtual ~BaseMsgWrap()
    {
    }

    virtual void Setup() = 0;

    virtual void Update() = 0;

    virtual void Reset() = 0;

    virtual std::string GetPrintableStr()
    {
        return "none";
    }

    MessageT *GetMsg()
    {
        return &_msg;
    }

    void SetMsg(MessageT *msg)
    {
        Lock();
        memcpy(msg, &_msg, sizeof(MessageT));
        Unlock();
    }

    void Lock()
    {
        _mutx.lock();
    }

    void Unlock()
    {
        _mutx.unlock();
    }

    int GetMsgLen()
    {
        return _len;
    }

    void SetTime()
    {
        _time.Set();
    }

    double Elapsed()
    {
        return _time.DurationMs();
    }

    const rosidl_message_type_support_t *GetType()
    {
        return _type;
    }
};

#endif // INCLUDE_MSG_WRAP_BASEMSGWRAP_HPP_
