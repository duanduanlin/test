/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-08-15 14:46:56
 * @Description:
 * @FilePath: \test\commonApi\project\mutex_test\src\main.cpp
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

int main(int argc, const char *argv [])
{
    int fd, ret;
    fd = open("/tmp/data.dat", O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd <0)
    {
         fprintf(stderr, "errmsg: [%d %s!\n", errno, strerror(errno));
         return -1;
    }

    ret = lockf(fd, F_LOCK, 0); /* F_LOCK Or F_TLOCK Or F_TEST */
    if (ret < 0)
    {
         fprintf(stderr, "errmsg: [%d %s!\n", errno, strerror(errno));
         close(fd);
         return -1;
    }

     /* Do Something ...*/
     fprintf(stdout, "Lock success! \n");
     sleep(30);
     lockf(fd, F_ULOCK, 0);
     close(fd);
     return 0;
}
