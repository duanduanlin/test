/*
 * @Author: dding3
 * @Date: 2023-12-06 19:38:21
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-06 19:39:42
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/dns/src/dns_test.cpp
 */
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DOMAIN "www.baidu.com"

int main(int argc, char *argv[])
{
    struct hostent *p = gethostbyname(DOMAIN);
    printf("hostname %s\n", p->h_name);
    printf("address ");

    int i;
    for (i = 0; p->h_addr_list[i]; i++)
    {
        // inet_ntoa: 将网络地址转换成“.”点隔的字符串格(点分十进制)
        printf("%s ", inet_ntoa(*(struct in_addr *)p->h_addr_list[i]));
    }
    printf("\n");

    return 0;
}
