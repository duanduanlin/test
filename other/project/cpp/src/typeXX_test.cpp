/*
 * @Author: dding3
 * @Date: 2023-12-13 18:53:21
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 18:55:50
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/typeXX_test.cpp
 */
#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    int num = 10;
    int result = num; // 使用typeof获取num的类型并声明result变量

    cout << "结果的类型是： " << typeid(result).name() << endl;

    return 0;
}
