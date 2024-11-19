/*
 * @Author: hanson
 * @Date: 2024-09-02 11:06:31
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-30 15:16:06
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\native\backtrace\src\backtrace.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>   /* for signal */
#include <execinfo.h> /* for backtrace() */
#include "backtrace.h"

#define BACKTRACE_SIZE 16

static backtrace_callback s_trace_callback = NULL;

static void dump_stack(void)
{
    int nptrs;
    void *buffer[BACKTRACE_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BACKTRACE_SIZE);
    strings = backtrace_symbols(buffer, nptrs);

    printf("backtrace() returned %d addresses\r\n", nptrs);
    for (int i = 0; i < nptrs; i++)
    {
        printf("[%02d] %s\r\n", i, strings[i]);
    }

    if (s_trace_callback != NULL)
    {
        s_trace_callback(strings, nptrs);
    }

    if (strings != NULL)
        free(strings);
}

static void signal_handler(int signo)
{

#if 0
    char buff[64] = {0x00};

    sprintf(buff,"cat /proc/%d/maps", getpid());

    system((const char*) buff);
#endif

    printf("\n=========>>>catch signal %d <<<=========\n", signo);

    dump_stack();

    signal(signo, SIG_DFL); /* 恢复信号默认处理 */
    raise(signo);           /* 重新发送信号 */
}

void backtrace_init(backtrace_callback cb)
{
    s_trace_callback = cb;
    signal(SIGSEGV, signal_handler); /* 为SIGSEGV信号安装新的处理函数 */
    signal(SIGILL, signal_handler);
    signal(SIGBUS, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGSTKFLT, signal_handler);
}
