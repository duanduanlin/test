/*
 * @Author: dding3
 * @Date: 2023-12-14 18:43:56
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 18:45:16
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/file_test.cpp
 */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("01.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);

    if (unlink("01.txt") < 0)
        printf("unlink errpr!\n");

    char buf[128] = {0};
    write(fd, "1234567", 7);

    if (lseek(fd, 0, SEEK_SET) == -1)
        printf("lseek error!\n");

    read(fd, buf, 7);
    printf("%s\n", buf);

    return 0;
}
