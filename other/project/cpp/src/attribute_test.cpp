/*
 * @Author: dding3
 * @Date: 2023-12-13 19:15:54
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 19:17:29
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/attribute_test.cpp
 */
#include <iostream>
using namespace std;

// 1.test()在main函数之前调用,它是被系统调用,并非main函数调用.
__attribute__((constructor)) static void test()
{
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
}

// 2.test_01()在main函数之前调用,它是被系统调用,并非main函数调用.
__attribute__((constructor(103))) static void test_01()
{ // 设置优先级为103
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
}

// 3.test_02()在main函数之前调用,它是被系统调用,并非main函数调用.
__attribute__((constructor(101))) static void test_02()
{ // 设置优先级为101
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
}

// 4.test_03()被未调用,因为没有__attribute__((constructor))修饰.
void test_03()
{
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
}

// 4.__attribute__((destructor))修饰析构函数,在析构函数以后执行.
__attribute__((destructor)) void test_04()
{
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
}

class A
{
public:
    A()
    {
        printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
    }
    ~A()
    {
        printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
    }
};

int main()
{
    A a;
    printf("xxx--------->%s, line = %d\n", __FUNCTION__, __LINE__);
    return 0;
}
