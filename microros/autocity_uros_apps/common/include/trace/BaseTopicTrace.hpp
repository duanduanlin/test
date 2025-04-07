/*
 * @Author: hanson
 * @Date: 2024-09-02 16:57:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 16:30:24
 * @Description:
 * @FilePath: \autocity_uros_apps\common\include\trace\BaseTopicTrace.hpp
 */

#ifndef COMMON_INCLUDE_TRACE_TOPICTRACE_HPP_
#define COMMON_INCLUDE_TRACE_TOPICTRACE_HPP_

#include "trace/BaseTrace.hpp"

namespace auto_city
{
    template <typename MessageT>
    class BaseTopicTrace : public BaseTrace
    {
    private:
        /* data */
    public:
        BaseTopicTrace(std::string file) : BaseTrace(file) {}
        virtual ~BaseTopicTrace() = default;

        int Trace(MessageT &msg)
        {
            std::lock_guard<std::mutex> lock(_mux);
            auto str = _get_time_stamps() + msg.GetPrintableStr() + "\r\n";

            return SaveData(str.c_str(), str.length());
        }
    };
}

#endif // COMMON_INCLUDE_TRACE_TOPICTRACE_HPP_
