/*
 * @Author: dding3
 * @Date: 2023-12-14 17:48:26
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 17:50:06
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/offsetof_test.cpp
 */
#include <iostream>
#include <stdio.h>
#include <cstddef>
using namespace std;

// 禁用系统函数offsetof,使用自己定义的.
// #undef offsetof
// #define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

struct Test
{
    char a;
    int b;
    short c;
};

int main(void)
{
    struct Test s1;
    s1.a = '1';
    s1.b = 20;
    s1.c = 30;

    // 1.打印每个元素的长度
    printf("sizeof(s1.a) = %ld\n", sizeof(s1.a));
    printf("sizeof(s1.b) = %ld\n", sizeof(s1.b));
    printf("sizeof(s1.c) = %ld\n\n", sizeof(s1.c));

    // 2.使用int*指针来访问结构体元素
    printf("s1.a = %c\n", *((int *)&s1));
    printf("s1.b = %d\n", *((int *)&s1 + 1));   // 偏移单位为：一个int类型,即4个byte.
    printf("s1.c = %d\n\n", *((int *)&s1 + 2)); // 2个int类型大小,即8个byte,以此类推...

    // 3.使用char*指针来访问结构体元素
    printf("s1 = %c\n", *((char *)&s1));
    printf("s1 = %d\n", *((char *)&s1 + 4));   // 偏移单位为：一个char类型,即1个byte.
    printf("s1 = %d\n\n", *((char *)&s1 + 8)); // 4个char类型大小,即4个byte,以此类推...

    // 4.函数offsetof()计算每个成员变量的位移.
    printf("a在结构体中的偏移位置： %ld\n", offsetof(Test, a));
    printf("b在结构体中的偏移位置： %ld\n", offsetof(Test, b)); // offsetof的偏移单位为：一个char类型,即1个byte.
    printf("c在结构体中的偏移位置： %ld\n", offsetof(Test, c)); // h4个int类型,即4个byte,以此类推...

    return 0;
}
