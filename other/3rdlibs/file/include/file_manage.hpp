/*
 * Copyright 2022-2036 JiangLing Motor Co.Ltd. All Rights Reserved.
 *
 * @Author: zjiang4 zjiang4@jmc.com.cn
 * @Date: 2022-11-29 17:02:13
 * @Description: 文件操作接口
 */

#ifndef __FILE_MANAGE_H__
#define __FILE_MANAGE_H__

#include <stdint.h>
#include <vector>
#include <string>
#include "crypto.h"
namespace file_operation
{
class File
{
public:
    File();
    virtual ~File();
    int open(const std::string &fileName, int flag);
    int close();
    size_t getFileSize();
    ssize_t read(char *data, size_t length);
    ssize_t write(const char *data, size_t length);
    ssize_t seek(int offset, int fromwhere);

private:
    int fd;
    std::string name;
};

class FileUtility
{
public:
    static int mkDir(const std::string &fileName);
    static bool exist(const std::string &fileName);
    static int rmDir(const std::string &fileName);
    static int rmFile(const std::string &fileName);
    static int getFileSize(const std::string &fileName);
    static int rename(const std::string &fileOldName, const std::string &fileNewName);
    static int copy(const std::string &fileOldName, const std::string &fileNewName);
    static ssize_t readFile(const std::string &fileName, char *data, size_t length);
    static bool readFile(const std::string &fileName, std::vector<char> &data);
    static int writeFile(const std::string &fileName, const char *data, size_t length);
    static ssize_t readEncryptFile(const std::string &fileName, char *data, size_t length);
    static int writeEncryptFile(const std::string &fileName, const char *data, size_t length);
    static int readDecryptAndHashFile(const std::string &fileName, std::vector<uint8_t> &data);
    static int writeEncryptAndHashFile(const std::string &fileName, const std::vector<uint8_t> &data);

private:
    static int aesEncrypt(const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage);
    static int aesDecrypt(unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char **decryptedMessage);
};

}
using namespace file_operation;


#endif