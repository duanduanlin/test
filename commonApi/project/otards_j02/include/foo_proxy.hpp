/*
 * @Author: dding3
 * @Date: 2024-03-24 20:23:38
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-03-25 00:30:13
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_v01/include/foo_proxy.hpp
 */
#ifndef TEST_COMMONAPI_PROJECT_OTARDS_V01_INCLUDE_FOO_PROXY_HPP_
#define TEST_COMMONAPI_PROJECT_OTARDS_V01_INCLUDE_FOO_PROXY_HPP_
#include "foo.hpp"

class foo_proxy
{
private:
    Foo foo ;
    /* data */
public:
    foo_proxy(/* args */);
    ~foo_proxy();

    void call_foo();
    void call_bar();
};

#endif // TEST_COMMONAPI_PROJECT_OTARDS_V01_INCLUDE_FOO_PROXY_HPP_
