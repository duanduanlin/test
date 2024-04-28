/*
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-04-27 19:46:58
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-04-27 19:52:27
 * @FilePath: /test/test/other/project/section/src/section_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>

static void before(void) __attribute__((constructor));//main函数前调用
static void after(void) __attribute__((destructor));//main函数后调用

static void before()
{
    printf("before main\n");
}

static void after(void)
{
    printf("after main\n");
}

int main()
{

    printf("main\n");
    return 0;
}