/*
 * @Author: hanson
 * @Date: 2024-09-29 15:48:13
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-14 13:42:38
 * @Description:
 * @FilePath: \autocity_uros_apps\common\src\trace\BaseTrace.cpp
 */
#include <thread>
#include <ctime>
#include <random>
#include "trace/BaseTrace.hpp"

BaseTrace::BaseTrace(std::string file_name)
{
    std::string ROS_LOG_DIR;
    if (std::getenv("ROS_LOG_DIR") == NULL)
    {
        ROS_LOG_DIR = std::string("/autocity/data/logs/latest/");
    }
    else
    {
        ROS_LOG_DIR = std::string(std::getenv("ROS_LOG_DIR"));
    }
    std::string RUN_TIME;
    if (std::getenv("RUN_TIME") != NULL)
    {
        RUN_TIME = std::string(std::getenv("RUN_TIME"));
    }

    file_name = ROS_LOG_DIR + std::string("/") + file_name + std::string("_") + RUN_TIME;
    _fp = ufile_open(file_name.c_str(), "w");
    if (_fp == nullptr)
    {
        printf("[ ERRO ]Open file failed: %s\r\n", file_name.c_str());
        return;
    }
    printf("[ INFO ]Open file:%s success.\r\n", file_name.c_str());
    std::thread sync_thread(_sync_thread_handler, _fp);

    sync_thread.detach();
}

BaseTrace::~BaseTrace()
{
    ufile_close(_fp);
}

int BaseTrace::SaveData(const char *data, int len)
{
    if (_fp == nullptr)
    {
        return -1;
    }
    return ufile_write(_fp, data, len);
}

void BaseTrace::_sync_thread_handler(FILE *fp)
{
    while (fp != nullptr)
    {
        std::default_random_engine e;
        std::uniform_int_distribution<int> u(1, 5); // 左闭右闭区间
        e.seed(time(0));
        std::this_thread::sleep_for(std::chrono::milliseconds(u(e) * 1000));
        ufile_sync(fp);
    }
}

std::string BaseTrace::_get_time_stamps()
{
    char _buffer[64] = {0};
    auto now = std::chrono::system_clock::now();
    // 通过不同精度获取相差的毫秒数
    uint64_t dis_millseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() * 1000;
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm *nowtime = localtime(&tt);

    snprintf(_buffer, 64, "[%04d-%02d-%02d %02d:%02d:%02d.%03d] ",
             1900 + nowtime->tm_year,
             1 + nowtime->tm_mon,
             nowtime->tm_mday,
             nowtime->tm_hour,
             nowtime->tm_min,
             nowtime->tm_sec,
             (int)dis_millseconds);

    return std::string(_buffer);
}
