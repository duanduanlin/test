/*
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-04-27 19:46:58
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-04-27 20:18:25
 * @FilePath: /test/test/other/project/section/src/section_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//参考文档：https://blog.csdn.net/zhizhengguan/article/details/111151773
static void before(void) __attribute__((constructor)); // main函数前调用
static void after(void) __attribute__((destructor));   // main函数后调用

//参考：https://blog.csdn.net/nyist327/article/details/59481809
typedef void (*myown_call)(void);

extern myown_call _myown_start;
extern myown_call _myown_end;

#define _init __attribute__((unused, section(".myown")))
#define func_init(func) myown_call _fn_##func _init = func

static void mspec1(void)
{
    printf("mspec1\r\n");
}

static void mspec2(void)
{
    printf("mspec2\r\n");
}

static void mspec3(void)
{
    printf("mspec3\r\n");
}

func_init(mspec1);
func_init(mspec2);
func_init(mspec3);

/* exactly like below:
static myown_call mc1  __attribute__((unused, section(".myown"))) = mspec1;
static myown_call mc2  __attribute__((unused, section(".myown"))) = mspec2;
static myown_call mc3  __attribute__((unused, section(".myown"))) = mspec3;
*/

static void before()
{
    printf("before main\n");
}

static void after(void)
{
    printf("after main\n");
}

void do_initcalls(void)
{
    myown_call *call_ptr = &_myown_start;
    do
    {
        fprintf(stderr, "call_ptr: %p\n", call_ptr);
        (*call_ptr)();
        ++call_ptr;
    } while (call_ptr < &_myown_end);
}

int main()
{
    printf("main\n");
    do_initcalls();
    return 0;
}