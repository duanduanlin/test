/*
 * @Author: hanson
 * @Date: 2024-09-02 11:06:31
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-27 10:58:00
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\native\ufile\src\ufile.c
 */

#include "ufile.h"

FILE *ufile_open(const char *file_path, const char *mode)
{
    if (file_path == NULL)
    {
        return NULL;
    }
    return fopen(file_path, mode);
}

int ufile_close(FILE *fp)
{
    if (fp == NULL)
    {
        return -1;
    }
    return fclose(fp);
}

int ufile_write(FILE *fp, const char *buff, int len)
{
    if (fp == NULL)
    {
        return -1;
    }
    // printf("ufile_write:%s\r\n", buff);
    int ret = fwrite(buff, 1, len, fp);
    if (ret <= 0)
    {
        printf("write failed\r\n");
        return -1;
    }
    // fflush(fp); // 可能有fwrite没写完的部分， flush 内存缓存 到 fp 缓存
    // fdatasync(fileno(fp));

    return ret;
}

int ufile_read(FILE *fp, char *buff, int len)
{
    if (fp == NULL)
    {
        return -1;
    }
    return fread(buff, 1, len, fp);
}

void ufile_sync(FILE *fp)
{
    if (fp != NULL)
    {
        fflush(fp); // 可能有fwrite没写完的部分， flush 内存缓存 到 fp 缓存
        fdatasync(fileno(fp));
    }
}
