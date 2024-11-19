#ifndef APPS_UCANBUS_INCLUDE_TRACE_BACKTRACE_HPP_
#define APPS_UCANBUS_INCLUDE_TRACE_BACKTRACE_HPP_

class BackTrace
{
private:
    /* data */
public:
    BackTrace(/* args */);
    virtual ~BackTrace();
    static void SetUp();
private:
    static void _backtrace_callback(const char **trace, int size);
};

#endif // APPS_UCANBUS_INCLUDE_TRACE_BACKTRACE_HPP_
