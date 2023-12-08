/*
 * @Author: dding3
 * @Date: 2023-12-07 18:34:53
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 18:42:04
 * @Description:lambda一种匿名函数：[capture list] (parameters) -> return_type { function_body }
 * @FilePath: /test/commonapi/test/other/project/cpp/src/lambda_test.cpp
 */
#include <iostream>
#include <string>
#include <functional>

typedef std::function<int(int x, int y)> Callback;
using UCallback = std::function<int(int x, int y)>;

// v1.0
int call_add(std::function<int(int x, int y)> call)
{
    int a = 100, b = 500;
    call(a, b); // 传值a,b给调用者.
    return a + b;
}

// v2.0: 与以上等同:使用typedef定义Callback类型别名定义
int call_add_01(Callback call)
{
    int a = 100, b = 500;
    call(a, b); // 传值a,b给调用者.
    return a + b;
}

// v3.0: 与以上等同:使用using定义UCallback类型别名定义
int call_add_02(UCallback call)
{
    int a = 100, b = 500;
    call(a, b); // 传值a,b给调用者.
    return a + b;
}

int main()
{
    // v1.0:匿名lambda函数,无参数,无返回值.
    []()
    {
        printf("xxx----->%s(), line = %d\n", __FUNCTION__, __LINE__);
    }();

    // v2.0:匿名lambda函数,带string参数,无返回值.
    [](std::string content)
    {
        printf("xxx----->%s(), line = %d, content = %s\n", __FUNCTION__, __LINE__, content.c_str());
    }("Hello Wolrd.");

    // v3.0:匿名lambda函数,带string和int类型参数,无返回值.
    std::string buf = "Hello, C++!";
    int year = 2023;
    [](std::string buf, int years)
    {
        printf("xxx----->%s(), line = %d, buf = %s, years = %d\n", __FUNCTION__, __LINE__, buf.c_str(), years);
    }(buf, year);

    // v3.1: lambda带返回值
    int moth = [](std::string buf, int years)
    {
        printf("xxx----->%s(), line = %d, buf = %s, years = %d\n", __FUNCTION__, __LINE__, buf.c_str(), years);
        int month = 10;
        return month;
    }(buf, year);
    printf("xxx----->%s(), line = %d, moth = %d\n", __FUNCTION__, __LINE__, moth);

    // 4.0: 使用typedef创建别名类型Callback,然后调用回调函数.
    Callback add = [](int a, int b) -> int
    {
        printf("xxx---------->%s(), line = %d, a = %d, b = %d\n", __FUNCTION__, __LINE__, a, b);
        return a + b;
    };
    printf("xxx----->%s(), line = %d, add = %d\n", __FUNCTION__, __LINE__, add(2, 3));

    // v5.0: 使用typedef定义回调函数类型别名
    int ret1 = call_add(add);
    printf("xxx----->%s(), line = %d, ret1 = %d\n", __FUNCTION__, __LINE__, ret1);

    // v6.0: 直接使用lambda匿名回调函数
    int ret2 = call_add([](int x, int y) -> int
                        { return x + y; });
    printf("xxx----->%s(), line = %d, ret2 = %d\n", __FUNCTION__, __LINE__, ret2);

    // v7.0: 使用typedef定义回调函数类型别名
    int ret3 = call_add_01(add);
    printf("xxx----->%s(), line = %d, ret3 = %d\n", __FUNCTION__, __LINE__, ret3);

    // v8.0: 使用using定义回调函数类型别名
    int ret4 = call_add_02(add);
    printf("xxx----->%s(), line = %d, ret4 = %d\n", __FUNCTION__, __LINE__, ret4);

    // v9.0: 直接使用lambda匿名回调函数
    int ret5 = call_add_02([](int x, int y) -> int
                           { return x + y; });
    printf("xxx----->%s(), line = %d, ret5 = %d\n", __FUNCTION__, __LINE__, ret5);

    return 0;
}
