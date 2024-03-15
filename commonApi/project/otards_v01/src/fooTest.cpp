/*
 * @Author: dding3
 * @Date: 2024-03-14 01:41:39
 * @LastEditors: dding3
 * @LastEditTime: 2024-03-14 01:43:18
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_v01/src/fooTest.cpp
 */
#include "foo.hpp"

int main() {
    Foo* foo = new Foo();
    foo->foo();
    foo->bar();
    delete foo;

    return 0;
}
