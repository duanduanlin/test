/*
 * @Author: dding3
 * @Date: 2023-12-18 17:58:20
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-18 19:21:27
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/thread_test.cpp
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 5
void *thread_printf(void *arg)
{
    printf("xxx-------->line = %d, data = %d,pthread_self() = %#x\n", __LINE__, *(int *)arg, pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    // 1.数据已经乱掉
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&(thread[i]), NULL, thread_printf, &i);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(thread[i], NULL);
    // 测试线程与主进程竞争顺序
    for (int i = 0; i < NUM_THREADS; i++)
        printf("xxx-------->line = %d, i = %d,getpid() = %#x\n", __LINE__, i, getpid());

    // 2.数据征程顺序,pthread_join()调用顺序问题
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&(thread[i]), NULL, thread_printf, &i);
        pthread_join(thread[i], NULL);
    }
    // 测试线程与主进程竞争顺序
    for (int i = 0; i < NUM_THREADS; i++)
        printf("xxx-------->line = %d, i = %d\n", __LINE__, i);

    // 3. detach
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&(thread[i]), NULL, thread_printf, &i);
        pthread_detach(thread[i]);
    }
    // 子线程压根就来不及执行
    for (int i = 0; i < NUM_THREADS; i++)
        printf("xxx-------->line = %d, i = %d\n", __LINE__, i);

    return 0;
}
