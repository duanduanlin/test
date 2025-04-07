/*
 * @Author: hanson
 * @Date: 2024-09-02 10:59:02
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-27 10:58:14
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\native\ufile\include\ufile.h
 */
#ifndef APPS_UCANBUS_NATIVE_UFILE_INCLUDE_UFILE_H_
#define APPS_UCANBUS_NATIVE_UFILE_INCLUDE_UFILE_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    FILE *ufile_open(const char *file_path, const char *mode);

    int ufile_close(FILE *fp);

    int ufile_write(FILE *fp, const char *buff, int len);

    int ufile_read(FILE *fp, char *buff, int len);

    void ufile_sync(FILE *fp);
#ifdef __cplusplus
}
#endif

#endif // APPS_UCANBUS_NATIVE_UFILE_INCLUDE_UFILE_H_
