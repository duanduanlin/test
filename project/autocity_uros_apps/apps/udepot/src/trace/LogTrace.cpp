/*
 * @Author: hanson
 * @Date: 2024-10-11 18:30:04
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 13:39:29
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\trace\LogTrace.cpp
 */
#include "trace/LogTrace.hpp"

static void _log_thread_handler()
{
    while (1)
    {
        SingleTonLogTrace::Instance().HandleLog();
    }
}

LogTrace::LogTrace() : BaseLogTrace("udepot")
{
    std::thread log_handle_thread(_log_thread_handler);

    log_handle_thread.detach();
}
