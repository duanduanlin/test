/*
 * @Author: dding3
 * @Date: 2023-12-18 18:30:02
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-18 18:31:06
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/mmap_test.cpp
 */
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <cstring>

using namespace std;

int main()
{
    string buf = "Hello Shared Memory!";

    int fd = open("test_shared_memory", O_CREAT | O_RDWR, 0666);

    if (unlink("test_shared_memory") < 0)
        printf("unlink errpr!\n");

    // 1.将参数fd指定的文件大小改为参数length指定的大小
    ftruncate(fd, buf.size());

    // 2.映射共享内存,传入fd和buf的size大小
    char *sm = (char *)mmap(NULL, buf.size(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // 3.将buf内容复制到共享内存地址sm.
    strcpy(sm, buf.c_str());

    printf("xxx------->line = %d, content = %s\n", __LINE__, sm);

    // 4.释放共享内存
    if (munmap(sm, buf.size()) == -1)
    {
        printf("xxx------->line = %d\n", __LINE__);
        return 0;
    }

    close(fd);

    return 0;
}
