/*
 * @Author: dding3
 * @Date: 2023-12-05 22:06:00
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-05 22:06:29
 * @Description:
 * @FilePath: /test/commonapi/test/rpc/project/env/src/env_test.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *val;
    const char *name = "ABC";

    // 获取ABC环境变量的值
    val = getenv(name);
    printf("No.1  %s=%s\n", name, val);

    // 覆盖写入环境变量
    setenv(name, "I amsure of that I will get it", 1);
    printf("No.2%s=%s\n", name, val);

    val = getenv(name);
    printf("No.3%s=%s\n", name, val);

    // 删除一个环境变量
    int ret = unsetenv("ABC");
    printf("ret =%d\n", ret);

    val = getenv(name);
    printf("No.3 %s=%s\n", name, val);

    return 0;
}
