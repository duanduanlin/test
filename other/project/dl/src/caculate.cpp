/*
 * @Author: dding3
 * @Date: 2023-12-06 18:42:45
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-06 18:52:41
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/dl/src/caculate.cpp
 */

extern "C"
{
    int add(int a, int b)
    {
        return (a + b);
    }

    int sub(int a, int b)
    {
        return (a - b);
    }

    int mul(int a, int b)
    {
        return (a * b);
    }

    int div(int a, int b)
    {
        return (a / b);
    }
}
