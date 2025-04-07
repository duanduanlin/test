/*
 * @Author: hanson
 * @Date: 2024-09-02 14:13:35
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-09 14:04:58
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\trace\CanTrace.hpp
 */
#ifndef APPS_UCANBUS_INCLUDE_TRACE_CANTRACE_HPP_
#define APPS_UCANBUS_INCLUDE_TRACE_CANTRACE_HPP_

#include "common/Singleton.hpp"
#include "trace/BaseTrace.hpp"
#include "common/can_support.hpp"

namespace auto_city
{
    class CanTrace : public BaseTrace
    {
    private:
        /* data */

    public:
        CanTrace(std::string file) : BaseTrace(file)
        {
        }
        virtual ~CanTrace() = default;

        int Trace(can_frame &frame)
        {
            std::lock_guard<std::mutex> lock(_mux);
            char buff[100] = {0};
            auto now = std::chrono::system_clock::now();
            // 通过不同精度获取相差的毫秒数
            uint64_t dis_millseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() * 1000;
            time_t tt = std::chrono::system_clock::to_time_t(now);
            tm *nowtime = localtime(&tt);
            auto len = snprintf(buff, 100,
                                "[%04d-%02d-%02d %02d:%02d:%02d.%03d] [%03x] [%02x %02x %02x %02x %02x %02x %02x %02x]\n",
                                1900 + nowtime->tm_year,
                                1 + nowtime->tm_mon,
                                nowtime->tm_mday,
                                nowtime->tm_hour,
                                nowtime->tm_min,
                                nowtime->tm_sec,
                                (int)dis_millseconds,
                                frame.can_id,
                                frame.data[0],
                                frame.data[1],
                                frame.data[2],
                                frame.data[3],
                                frame.data[4],
                                frame.data[5],
                                frame.data[6],
                                frame.data[7]);

            return SaveData(buff, len);
        }
    };

    class CanSendTrace : public CanTrace
    {
    private:
        /* data */
    public:
        CanSendTrace(/* args */) : CanTrace("can_send_data") {}
        ~CanSendTrace() = default;
    };

    class CanRecvTrace : public CanTrace
    {
    private:
        /* data */
    public:
        CanRecvTrace(/* args */) : CanTrace("can_recv_data") {}
        ~CanRecvTrace() = default;
    };

    using SingleTonCanSendTrace = Singleton<CanSendTrace>;
    using SingleTonCanRecvTrace = Singleton<CanRecvTrace>;

#define TraceCanSendFrame(a) (SingleTonCanSendTrace::Instance().Trace(a))
#define TraceCanRecvFrame(a) (SingleTonCanRecvTrace::Instance().Trace(a))

#define TraceCanSendSync() (SingleTonCanSendTrace::Instance().Sync())
#define TraceCanRecvSync() (SingleTonCanRecvTrace::Instance().Sync())

}
#endif // APPS_UCANBUS_INCLUDE_TRACE_CANTRACE_HPP_
