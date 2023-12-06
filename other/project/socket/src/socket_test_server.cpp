/*
 * @Author: dding3
 * @Date: 2023-12-05 22:46:20
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-05 22:51:24
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/socket/src/socket_test_server.cpp
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#define UNIX_DOMAIN "/home/dding3/work/test/socket.test" // PC本地实际路径

int main()
{
    socklen_t clt_addr_len;
    int listen_fd, fd, ret, i, len;
    fd_set read_set;
    struct timeval timeout;
    static char rcv_buff[1024];
    struct sockaddr_un clt_addr;
    struct sockaddr_un srv_addr;
    listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        perror("connect creat communication socket");
    }
    // set srv_addr param
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, UNIX_DOMAIN, sizeof(srv_addr.sun_path) - 1);
    unlink(UNIX_DOMAIN);
    // bind sockfd&addr
    ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (ret < 0)
    {
        perror("cannot bind server socket");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return -1;
    }
    // listen sockfd
    ret = listen(listen_fd, 1);
    if (ret < 0)
    {
        perror("cannot listen sockfd");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return -1;
    }
    // have connect requst use accept
    len = sizeof(clt_addr);
    fd = accept(listen_fd, (struct sockaddr *)&clt_addr, (socklen_t*)&len);
    if (fd < 0)
    {
        perror("cannot accept requst");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return -1;
    }

    // read and printf client send info
    printf("\n******info********\n");
    memset(rcv_buff, 0, 1024);
    // read(fd,rcv_buff,sizeof(rcv_buff));
    recv(fd, rcv_buff, sizeof(rcv_buff), 0);
    printf("xxx---->%s, %s(), line = %d, data = '%s'\n", __FILE__, __FUNCTION__, __LINE__, rcv_buff);

    close(fd);
    close(listen_fd);
    unlink(UNIX_DOMAIN);
    return 0;
}
