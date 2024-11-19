/*
 * @Author: hanson
 * @Date: 2024-09-02 13:36:37
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-11 17:54:05
 * @Description:
 * @FilePath: \autocity_uros_apps\common\include\trace\BaseTrace.hpp
 */
#ifndef APPS_UCANBUS_INCLUDE_TRACE_BASETRACE_HPP_
#define APPS_UCANBUS_INCLUDE_TRACE_BASETRACE_HPP_

#include <chrono>
#include <string>
#include <mutex>
#include "ufile.h"
class BaseTrace
{
protected:
    std::mutex _mux;

private:
    /* data */
    FILE *_fp;

public:
    BaseTrace() = default;
    BaseTrace(std::string file_name);
    virtual ~BaseTrace();

    int SaveData(const char *data, int len);

    void Sync()
    {
        ufile_sync(_fp);
    }

protected:
    std::string _get_time_stamps();

private:
    static void _sync_thread_handler(FILE *fp);
};

#endif // APPS_UCANBUS_INCLUDE_TRACE_BASETRACE_HPP_
