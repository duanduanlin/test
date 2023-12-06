/*
 * @Author: dding3
 * @Date: 2023-12-05 22:47:54
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-05 22:51:32
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/socket/src/socket_test_client.cpp
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define UNIX_DOMAIN "/home/dding3/work/test/socket.test" // PC本地实际路径
int main()
{
    int connect_fd;
    int ret;
    char send_buff[1024];
    int i;
    static struct sockaddr_un srv_addr;
    // creat unix socket
    connect_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (connect_fd < 0)
    {
        perror("cannot creat socket");
        return -1;
    }
    srv_addr.sun_family = AF_UNIX;
    strcpy(srv_addr.sun_path, UNIX_DOMAIN);
    // connect server
    ret = connect(connect_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (ret < 0)
    {
        perror("cannot connect server");
        close(connect_fd);
        return -1;
    }
    memset(send_buff, 0, 1024);
    strcpy(send_buff, "I'm client data.");
    // send info server
    // write(connect_fd,send_buff,sizeof(send_buff));
    send(connect_fd, send_buff, sizeof(send_buff), 0);

    close(connect_fd);
    return 0;
}
