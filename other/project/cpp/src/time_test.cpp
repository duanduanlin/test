/*
 * @Author: dding3
 * @Date: 2023-12-13 22:23:24
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 22:23:38
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/time_test.cpp
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval tv;
unsigned long us_start, us_end;
void start_time()
{
    gettimeofday(&tv, NULL);
    us_start = tv.tv_sec * 1000000 + tv.tv_usec; // us
}

void end_time(char *func, int line)
{
    gettimeofday(&tv, NULL);
    us_end = tv.tv_sec * 1000000 + tv.tv_usec; // us
    printf("%s, line = %d, us_delta = %ld us \n", func, line, us_end - us_start);
}

int main()
{
    start_time();
    sleep(2);
    end_time("start_preview()", __LINE__);
}
