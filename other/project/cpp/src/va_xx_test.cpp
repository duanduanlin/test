/*
 * @Author: dding3
 * @Date: 2023-12-14 18:28:54
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 18:31:39
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/va_xx_test.cpp
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// 第一个参数定义可变参数的个数
void test_01(int arg_cnt, ...)
{
    va_list p_args;
    va_start(p_args, arg_cnt);

    int idx;
    int val;

    for (idx = 1; idx <= arg_cnt; ++idx)
    {
        val = va_arg(p_args, int);
        printf("第 %d 个参数: %d\n", idx, val);
    }
    printf("---------------\n");
    va_end(p_args);
}

void test(char *fmt, ...)
{
    // 定义可变参数列表
    va_list ap;
    // 获取不定参数的首地址，首地址是从fmt开始
    va_start(ap, fmt);

    printf("数据为:");
    vprintf(fmt, ap);

    va_end(ap);
    printf("\n");
}

int main()
{
    float ff = 0.1;
    char str[] = "hello";
    int dd = 50;

    test("type = %f, %s, %d", ff, str, dd);

    test_01(4, 1, 2, 3, 4);
    test_01(4, 1, 2, 3);
    // 多余的变参被忽略
    test_01(4, 1, 2, 3, 4, 5);
}
