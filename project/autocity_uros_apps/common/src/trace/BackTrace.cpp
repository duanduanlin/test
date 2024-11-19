#include "trace/BackTrace.hpp"
#include "backtrace.h"
#include "trace/LogTrace.hpp"

BackTrace::BackTrace(/* args */)
{
}

BackTrace::~BackTrace()
{
}

void BackTrace::SetUp()
{
    backtrace_init(_backtrace_callback);
}

void BackTrace::_backtrace_callback(const char **trace, int size)
{
    if (trace != nullptr)
    {
        LOG_FATAL("backtrace() returned %d addresses\r\n", size);
        for (int i = 0; i < size; i++)
        {
            LOG_FATAL("  [%02d] %s\r\n", i, trace[i]);
        }

        //sync data and log to file
        LOG_SYNC();
    }
}
