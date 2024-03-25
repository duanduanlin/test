/*
 * @Author: dding3
 * @Date: 2024-03-24 22:54:28
 * @LastEditors: dding3
 * @LastEditTime: 2024-03-24 23:38:39
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_j02/src/libota.cpp
 */
#include "libota.hpp"
#include "foo_proxy.hpp"

foo_proxy *foo = nullptr;
void init()
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
