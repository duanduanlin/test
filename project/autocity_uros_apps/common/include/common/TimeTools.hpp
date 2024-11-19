/*
 * @Author: hanson
 * @Date: 2024-08-30 16:37:22
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-12 16:36:06
 * @Description:
 * @FilePath: \ucanbus\include\common\TimeTools.hpp
 */
#ifndef INCLUDE_COMMON_TIMINGUTIL_HPP_
#define INCLUDE_COMMON_TIMINGUTIL_HPP_

#include <chrono>

class TimeTools
{
private:
    /* data */
    std::chrono::steady_clock::time_point _time;
    bool _active;

public:
    TimeTools(/* args */) = default;
    virtual ~TimeTools() = default;

    void Set()
    {
        _active = true;
        _time = std::chrono::steady_clock::now();
    }

    void Reset()
    {
        _active = false;
    }

    bool IsActive()
    {
        return _active;
    }

    double Duration()
    {
        return DurationMs() / 1000;
    }

    double DurationMs()
    {
        return _active ? std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - _time).count() : 0.0;
    }
};

#endif // INCLUDE_COMMON_TIMINGUTIL_HPP_
