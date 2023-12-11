/*
 * @Author: dding3
 * @Date: 2023-12-10 22:43:00
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-10 22:45:49
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/hexStr_test.cpp
 */
#include <stdio.h>
#include <cstring>

void print_str2hex(unsigned char *name, unsigned char *str, size_t size)
{
    printf("%s: ", name);
    for (size_t i = 0; i < size; i++)
    {
        printf("%02x ", static_cast<unsigned char>(str[i]));
        if (i != 0 && i % 16 == 0)
            printf("\n");
    }
    printf("\n");
}

int main()
{
    char str_buf[] = "00000001";
    char hex_buf[] = "\x00\x00\x00\x01"; //\x:表示16进制,

    // 1.16进制操作
    printf("sizeof(hex_buf) = %ld\n", sizeof(hex_buf)); // sizeof最后一位是'\0',即0,即实际长度+1位.
    printf("strlen(hex_buf) = %ld\n", strlen(hex_buf)); // strlen遇到0即截止.

    printf("xxx-------> hex_buf = %s\n", hex_buf); // 表示的16进制
    printf("xxx-------> str_buf = %s\n", str_buf); // 表示的字符串

    print_str2hex((unsigned char *)"hex data", (unsigned char *)hex_buf, sizeof(hex_buf) - 1);
    print_str2hex((unsigned char *)"str data", (unsigned char *)str_buf, sizeof(str_buf) - 1);
}
