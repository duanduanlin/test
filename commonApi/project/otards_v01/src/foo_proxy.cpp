/*
 * @Author: dding3
 * @Date: 2024-03-24 20:27:12
 * @LastEditors: dding3
 * @LastEditTime: 2024-03-24 23:08:56
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_v01/src/foo_proxy.cpp
 */
#include "foo_proxy.hpp"

 void foo_proxy::call_foo()
{
    foo.foo();
}

 void foo_proxy::call_bar()
{
    foo.bar();
}

foo_proxy::foo_proxy(/* args */)
{
}

foo_proxy::~foo_proxy()
{
}
