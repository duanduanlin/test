/*
 * @Author: dding3
 * @Date: 2024-03-24 22:54:28
 * @LastEditors: dding3
 * @LastEditTime: 2024-03-24 23:08:13
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_v01/src/libota.cpp
 */
#include "libota.hpp"
#include "foo_proxy.hpp"

foo_proxy *foo = nullptr;
static void init()
{
    if (foo == nullptr)
    {
        foo = new foo_proxy();
    }
}

void call_foo_api()
{
    init();
    foo->call_foo();
}

void call_bar_api()
{
    init();
    foo->call_bar();
}
