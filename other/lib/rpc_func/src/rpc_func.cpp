/*
 * @Author: dding3
 * @Date: 2023-09-19 23:28:51
 * @LastEditors: dding3
 * @LastEditTime: 2023-09-19 23:53:07
 * @Description:
 * @FilePath: /test/commonapi/test/rpc/lib/rpc_func/src/rpc_func.cpp
 */
#include <iostream>

extern "C"
{
    int func_add(int a, int b)
    {
        return a + b;
    }
}
