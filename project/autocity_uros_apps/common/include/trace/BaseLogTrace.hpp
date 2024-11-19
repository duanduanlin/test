#ifndef COMMON_INCLUDE_TRACE_LOGTRACE_HPP_
#define COMMON_INCLUDE_TRACE_LOGTRACE_HPP_

#include <chrono>
#include <iostream>
#include <libgen.h>
#include <memory>
#include <cstring>
#include <semaphore.h>
#include <thread>
#include "common/Singleton.hpp"
#include "common/RingBuffer.hpp"
#include "trace/BaseTrace.hpp"

#define LOG_LEN_MAX (512)
#define LOG_QUEUE_MAX (1024)
#define LOG_BUFFER_LEN_MAX (32 * 1024)
class BaseLogTrace : public BaseTrace
{
public:
    enum LogLevel
    {
        LOG_LEVEL_FATAL = 0,
        LOG_LEVEL_ERRO = 1,
        LOG_LEVEL_WARN = 2,
        LOG_LEVEL_INFO = 3,
        LOG_LEVEL_DEBG = 4,
    };

private:
    /* data */
    LogLevel _file_level; // file log
    LogLevel _level;      // printf log
    RingBuffer<char> _log_buffer;
    sem_t _log_sem;

public:
    BaseLogTrace(std::string file_name) : BaseTrace(file_name), _file_level(LOG_LEVEL_DEBG), _level(LOG_LEVEL_INFO)
    {
        _log_buffer.SetUp(LOG_BUFFER_LEN_MAX);
        sem_init(&_log_sem, 0, LOG_QUEUE_MAX);
    }
    virtual ~BaseLogTrace() = default;

    void SetLogLevelFile(LogLevel lvl)
    {
        _file_level = lvl;
    }

    LogLevel GetLogLevelFile()
    {
        return _file_level;
    }

    void SetLogLevel(LogLevel lvl)
    {
        _level = lvl;
    }

    LogLevel GetLogLevel()
    {
        return _level;
    }

    template <typename... Args>
    void Trace(LogLevel lvl, const std::string &file, const int line, const std::string &format, Args... args)
    {
        std::string msg;
        if (lvl > _file_level && lvl > _level)
        {
            return;
        }

        if (_log_buffer.IsFull())
        {
            printf("log quque full\r\n");
            return;
        }
        msg = _get_time_stamps() + _format("[ %s ] [ %s:%d ] ", _get_lvl_str().c_str(), basename((char *)file.c_str()), line) + _format(format, args...);
        _log_buffer.Push(msg.c_str(), msg.length());
        sem_post(&_log_sem);
    }

    template <typename... Args>
    void Trace(LogLevel lvl, const std::string &file, const int line, const int duration_ms, const std::string &format, Args... args)
    {
        static std::chrono::steady_clock::time_point time_exe = std::chrono::steady_clock::now();
        auto duration = std::chrono::steady_clock::now() - time_exe;
        // printf("duration:%d ms\r\n", duration.count() / (1000 * 1000));
        auto interval = duration.count() / (1000 * 1000);
        if (interval > duration_ms)
        {
            // trace for 50 ms
            if ((interval - duration_ms) > 20)
            {
                // reset
                time_exe = std::chrono::steady_clock::now();
            }
            Trace(lvl, file, line, format, args...);
        }
    }

    void HandleLog()
    {
        sem_wait(&_log_sem);
        if (!_log_buffer.IsEmpty())
        {
            char log[LOG_LEN_MAX + 1] = {0};
            int len = _log_buffer.Pop(log, LOG_LEN_MAX);
            printf("%s", log);
            SaveData(log, len);
        }
    }

private:
    template <typename... Args>
    std::string _format(const std::string &format, Args... args)
    {
        char buff[LOG_LEN_MAX] = {0};

        std::snprintf(buff, LOG_LEN_MAX, format.c_str(), args...);
        return std::string(buff, buff + strlen(buff));
    }

    std::string _get_lvl_str()
    {
        std::string lvl = "none";
        switch (_level)
        {
        case LOG_LEVEL_FATAL:
            lvl = "FATAL";
            break;
        case LOG_LEVEL_ERRO:
            lvl = "ERRO";
            break;
        case LOG_LEVEL_WARN:
            lvl = "WARN";
            break;
        case LOG_LEVEL_INFO:
            lvl = "INFO";
            break;
        case LOG_LEVEL_DEBG:
            lvl = "DEBG";
            break;
        default:
            break;
        }

        return lvl;
    }
};

#endif // COMMON_INCLUDE_TRACE_LOGTRACE_HPP_
