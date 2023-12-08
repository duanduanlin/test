/*
 * @Author: dding3
 * @Date: 2023-12-07 18:34:53
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 19:36:41
 * @Description:lambda一种匿名函数：[capture list] (parameters) -> return_type { function_body }
 * @FilePath: /test/commonapi/test/other/project/cpp/src/lambda_test.cpp
 */
#include <iostream>
#include <algorithm>
#include <vector>

// 重载
void test_case_3()
{
    int num1 = 5;
    double num2 = 2.5;
    // Lambda 函数重载
    auto lambda1 = [](int x) -> int
    {
        return x * x;
    };

    auto lambda2 = [](double x) -> double
    {
        return x * x;
    };
    std::cout << "lambda1 ret:" << lambda1(num1) << std::endl;
    std::cout << "lambda2 ret:" << lambda2(num2) << std::endl;
}

// 类型推导
void test_case_2()
{
    // 自动类型推断的 Lambda 函数
    auto lambda1 = [](int x, int y)
    {
        return x + y;
    };

    // 显式指定返回类型的 Lambda 函数
    auto lambda2 = [](int x) -> int
    {
        return x * x;
    };

    // 使用 Lambda 函数进行计算并输出结果
    std::cout << "自动类型推断的结果：" << lambda1(3, 4) << std::endl;
    std::cout << "显式指定返回类型的结果：" << lambda2(5) << std::endl;
}

// 捕获外部变量
void test_case_1()
{
    int a = 5;
    int b = 3;
    std::vector<int> nums = {2, 5, 1, 7, 3};

    // 捕获变量 a 和引用捕获变量 b，并按照特定规则排序
    std::sort(nums.begin(), nums.end(), [a, &b](int x, int y)
              { return a * x < b * y; });

    // 输出排序后的结果
    for (int num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}
