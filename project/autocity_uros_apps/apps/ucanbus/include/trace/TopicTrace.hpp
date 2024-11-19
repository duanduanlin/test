/*
 * @Author: hanson
 * @Date: 2024-09-02 16:57:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-20 16:59:10
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\trace\TopicTrace.hpp
 */
#ifndef INCLUDE_TRACE_TOPICTRACE_HPP_
#define INCLUDE_TRACE_TOPICTRACE_HPP_

#include "common/Singleton.hpp"
#include "trace/BaseTrace.hpp"
#include "msg_wrap/ChassisMsgWrap.hpp"
#include "msg_wrap/ControlMsgWrap.hpp"

template <typename MessageT>
class TopicTrace : public BaseTrace
{
private:
    /* data */
public:
    TopicTrace(std::string file) : BaseTrace(file) {}
    virtual ~TopicTrace() = default;

    int Trace(MessageT &msg)
    {
        std::lock_guard<std::mutex> lock(_mux);
        auto str = _get_time_stamps() + msg.GetPrintableStr();

        return SaveData(str.c_str(), str.length());
    }
};

class TopicTraceChassis : public TopicTrace<ChassisMsgWrap>
{
private:
    /* data */
public:
    TopicTraceChassis(/* args */) : TopicTrace("publish_chassis") {}
    ~TopicTraceChassis() = default;
};

class TopicTraceControl : public TopicTrace<ControlMsgWrap>
{
private:
    /* data */
public:
    TopicTraceControl(/* args */) : TopicTrace("subscribe_control") {}
    ~TopicTraceControl() = default;
};

using SingleTonTopicChassisTrace = Singleton<TopicTraceChassis>;
using SingleTonTopicControlTrace = Singleton<TopicTraceControl>;

#define TraceChassisTopic(a) (SingleTonTopicChassisTrace::Instance().Trace(a))
#define TraceControlTopic(a) (SingleTonTopicControlTrace::Instance().Trace(a))

#endif // INCLUDE_TRACE_TOPICTRACE_HPP_
