/*
 * @Author: dding3
 * @Date: 2024-03-14 01:41:39
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-03-24 23:54:20
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_j02/src/fooTest.cpp
 */
#include <stdio.h>
#include "foo.hpp"
#include "foo_proxy.hpp"
#include "libota.hpp"

void test01()
{
    printf("test01\r\n");
    Foo* foo = new Foo();
    foo->foo();
    foo->bar();
    delete foo;
}

void test02()
{
    printf("test02\r\n");
    foo_proxy foo;
    foo.call_foo();
    foo.call_bar();
}

void test03()
{
    printf("test03\r\n");
    call_foo_api();
    call_bar_api();
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}
