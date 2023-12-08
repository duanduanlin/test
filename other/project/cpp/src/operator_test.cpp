/*
 * @Author: dding3
 * @Date: 2023-12-07 23:12:04
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 23:13:44
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/operator_test.cpp
 */
#include <iostream>

// 例子1：计算平方的函数对象
class Squarer
{
public:
    int operator()(int x) const
    {
        return x * x;
    }
};

int main()
{
    Squarer squarer;

    int result = squarer(5); // 调用squarer对象，相当于squarer.operator()(5)
    std::cout << "Squared value: " << result << std::endl;

    return 0;
}
