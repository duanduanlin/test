/*
 * @Author: dding3
 * @Date: 2023-12-07 22:04:01
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 22:05:14
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/atomic_test.cpp
 */
#include <atomic>
#include <thread>

std::atomic<int> counter(0); // 原子变量

void increment()
{
    for (int i = 0; i < 1000; i++)
    {
        counter++;                                // 原子操作：递增
        printf("counter = %d\n", counter.load()); // 按顺序打印0 - 2000.
    }
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();
    return 0;
}
