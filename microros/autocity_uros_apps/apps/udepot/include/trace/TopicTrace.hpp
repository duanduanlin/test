/*
 * @Author: hanson
 * @Date: 2024-09-02 16:57:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:23:29
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\trace\TopicTrace.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_
#define APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_

#include "common/Singleton.hpp"
#include "trace/BaseTopicTrace.hpp"
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"
#include "msg_wrap/TrashDepotCmdMsgWrap.hpp"
#include "msg_wrap/TrashDepotStatusMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
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

        class TopicTraceTrashDepotStatus : public BaseTopicTrace<TrashDepotStatusMsgWrap>
        {
        private:
            /* data */
        public:
            TopicTraceTrashDepotStatus(/* args */) : BaseTopicTrace("publish_trash_depot_status") {}
            ~TopicTraceTrashDepotStatus() = default;
        };

        class TopicTraceTrashDepotCmd : public BaseTopicTrace<TrashDepotCmdMsgWrap>
        {
        private:
            /* data */
        public:
            TopicTraceTrashDepotCmd(/* args */) : BaseTopicTrace("subscribe_trash_depot_cmd") {}
            ~TopicTraceTrashDepotCmd() = default;
        };

        using SingleTonTopicWaterDepotStatusTrace = Singleton<TopicTraceWaterDepotStatus>;
        using SingleTonTopicWaterDepotCmdTrace = Singleton<TopicTraceWaterDepotCmd>;
        using SingleTonTopicTrashDepotStatusTrace = Singleton<TopicTraceTrashDepotStatus>;
        using SingleTonTopicTrashDepotCmdTrace = Singleton<TopicTraceTrashDepotCmd>;

#define TraceWaterDepotStatusTopic(a) (SingleTonTopicWaterDepotStatusTrace::Instance().Trace(a))
#define TraceWaterDepotCmdTopic(a) (SingleTonTopicWaterDepotCmdTrace::Instance().Trace(a))
#define TraceTrashDepotStatusTopic(a) (SingleTonTopicTrashDepotStatusTrace::Instance().Trace(a))
#define TraceTrashDepotCmdTopic(a) (SingleTonTopicTrashDepotCmdTrace::Instance().Trace(a))
    }
}
#endif // APPS_UDEPOT_INCLUDE_TRACE_TOPICTRACE_HPP_
