/*
 * @Author: hanson
 * @Date: 2024-10-14 11:08:30
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:23:01
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\trace\LogTrace.hpp
 */
#ifndef APPS_UCANBUS_INCLUDE_TRACE_LOGTRACE_HPP_
#define APPS_UCANBUS_INCLUDE_TRACE_LOGTRACE_HPP_

#include "trace/BaseLogTrace.hpp"

namespace auto_city
{
    namespace udepot
    {
        class LogTrace : public BaseLogTrace
        {
        public:
            LogTrace();
            ~LogTrace() = default;
        };

        using SingleTonLogTrace = Singleton<LogTrace>;

#define LOG_INFO(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__))
#define LOG_DEBG(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_DEBG, __FILE__, __LINE__, __VA_ARGS__))
#define LOG_WARN(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__))
#define LOG_ERRO(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_ERRO, __FILE__, __LINE__, __VA_ARGS__))
#define LOG_FATAL(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__))

#define LOG_INFO_EVERY_SECOND(...) (SingleTonLogTrace::Instance().Trace(LogTrace::LogLevel::LOG_LEVEL_INFO, __FILE__, __LINE__, 1000, __VA_ARGS__))

#define LOG_SYNC() (SingleTonLogTrace::Instance().Sync())

    }
}
#endif // APPS_UCANBUS_INCLUDE_TRACE_LOGTRACE_HPP_
