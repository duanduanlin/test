/*
 * @Author: dding3
 * @Date: 2023-12-14 17:36:19
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 17:37:45
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/cond_test.cpp
 */
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

#define WAIT 1

void *thread_func(void *arg)
{
    struct timeval now;
    struct timespec outtime;
    gettimeofday(&now, NULL);
    outtime.tv_sec = now.tv_sec + 3; // 超过3s后自动处理
    outtime.tv_nsec = now.tv_usec * 1000;

    cout << "Thread waiting for signal..." << endl;

    pthread_mutex_lock(&mutex);

#if WAIT
    // 1.如果不调用pthread_cond_signal(&cond)函数发信号,永远死等.
    pthread_cond_wait(&cond, &mutex);
    cout << "Thread recevie pthread_cond_signal() send signal, it's delay 1s." << endl;
#else
    // 2.可以设置超时时间,一旦超过设定时间,自动执行pthread_cond_timedwait函数后边的代码,它不受pthread_cond_signal的影响.
    pthread_cond_timedwait(&cond, &mutex, &outtime);
    cout << "Thread timed wait for 3s." << endl;
#endif

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    // 1.给pthread_cond_wait发信号(它俩是成对出现的),使其后边的代码可以执行.
#if WAIT
    sleep(1);
    pthread_cond_signal(&cond);
#endif
    pthread_join(thread, NULL);

    return 0;
}
