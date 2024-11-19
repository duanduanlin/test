/*
 * @Author: hanson
 * @Date: 2024-09-02 10:59:02
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-29 11:27:39
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\native\backtrace\include\backtrace.h
 */

#ifndef APPS_UCANBUS_NATIVE_BACKTRACE_INCLUDE_BACKTRACE_H_
#define APPS_UCANBUS_NATIVE_BACKTRACE_INCLUDE_BACKTRACE_H_

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void (*backtrace_callback)(const char **trace, int size);

    void backtrace_init(backtrace_callback cb);
#ifdef __cplusplus
}
#endif

#endif // APPS_UCANBUS_NATIVE_BACKTRACE_INCLUDE_BACKTRACE_H_
