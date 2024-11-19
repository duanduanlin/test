/*
 * @Author: hanson
 * @Date: 2024-09-19 11:24:51
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-09 11:37:42
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\trace\LogTrace.cpp
 */
#include "trace/LogTrace.hpp"

static void _log_thread_handler()
{
    while (1)
    {
        SingleTonLogTrace::Instance().HandleLog();
    }
}

LogTrace::LogTrace() : BaseTrace("ucanbus"), _file_level(LOG_LEVEL_DEBG), _level(LOG_LEVEL_INFO)
{
    _log_buffer.SetUp(LOG_BUFFER_LEN_MAX);
    sem_init(&_log_sem, 0, LOG_QUEUE_MAX);
    std::thread log_handle_thread(_log_thread_handler);

    log_handle_thread.detach();
}
