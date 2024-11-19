/*
 * @Author: hanson
 * @Date: 2024-09-02 16:57:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:40:35
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\trace\TopicTrace.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_
#define APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_

#include "common/Singleton.hpp"
#include "trace/BaseTopicTrace.hpp"
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"

class TopicTraceWaterDepotStatus : public BaseTopicTrace<WaterDepotStatusMsgWrap>
{
private:
    /* data */
public:
    TopicTraceWaterDepotStatus(/* args */) : BaseTopicTrace("publish_water_depot_status") {}
    ~TopicTraceWaterDepotStatus() = default;
};

class TopicTraceWaterDepotCmd : public BaseTopicTrace<WaterDepotCmdMsgWrap>
{
private:
    /* data */
public:
    TopicTraceWaterDepotCmd(/* args */) : BaseTopicTrace("subscribe_water_depot_cmd") {}
    ~TopicTraceWaterDepotCmd() = default;
};

using SingleTonTopicWaterDepotStatusTrace = Singleton<TopicTraceWaterDepotStatus>;
using SingleTonTopicWaterDepotCmdTrace = Singleton<TopicTraceWaterDepotCmd>;

#define TraceWaterDepotStatusTopic(a) (SingleTonTopicWaterDepotStatusTrace::Instance().Trace(a))
#define TraceWaterDepotCmdTopic(a) (SingleTonTopicWaterDepotCmdTrace::Instance().Trace(a))

#endif // APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_
