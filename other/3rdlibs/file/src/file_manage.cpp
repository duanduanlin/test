#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "log.hpp"
#include "crc.h"
#include "crypto.h"
#include "shutil.hpp"
#include "file_manage.hpp"
namespace file_operation
{
#define FILE_CMD_MAX 256
unsigned char aesKey[32] = {
    0xbb, 0x2a, 0x0b, 0x1e, 0x9a, 0x73, 0x98, 0x5e, 0x07, 0x8d, 0x1d, 0x89, 0x13, 0x65, 0x0d, 0x89,
    0x1a, 0x41, 0x12, 0x43, 0xfe, 0x3d, 0x52, 0x71, 0x4c, 0xf2, 0xad, 0x93, 0x48, 0x0b, 0x3b, 0x72};

unsigned char aesIv[16] = {0x4f, 0x12, 0x86, 0x09, 0xfa, 0x94, 0x5f, 0x40, 0x92, 0x0a, 0x33, 0x21, 0x91, 0x45, 0xc6, 0x8a};

File::File()
{
    fd = -1; // open系统调用出错时返回-1
}

File::~File()
{
    this->close();
}

int File::open(const std::string &fileName, int flag)
{
    if (name != fileName)
    {
        this->close();
        name.clear();
    }

    name.assign(fileName);
    errno = 0;
    fd = ::open(name.c_str(), flag, S_IRWXU | S_IRWXG | S_IRWXO);// 0777
    if (-1 == fd)
    {
        loge("open fail. errno[%s]\n", strerror(errno));
        return -1;
    }
    return 0;
}

int File::close()
{
    if (-1 != fd)
    {
        fsync(fd);
        ::close(fd); // 调用系统close
        fd = -1;
    }
    return 0;
}

/**
 * @description: 偏移处理
 * @param {offset} 偏移量（可以为负数）
 * @param {fromwhere} 起始偏移位置： SEEK_SET/SEEK_CUR/SEEK_END
 * @return 成功：较起始位置偏移量  失败：-1 errno
 */
ssize_t File::seek(int offset, int fromwhere)
{
    if (-1 == fd)
    {
        loge("seek fail. errno[%s]\n", strerror(errno));
        return -1;
    }
    return ::lseek(fd, offset, fromwhere);
}

size_t File::getFileSize()
{
    struct stat fileStat;
    errno = 0;
    if (0 != stat(name.c_str(), &fileStat))
    {
        loge("getFileSize stat:%ld, errno[%s]\n", fileStat.st_size, strerror(errno));
        return 0;
    }

    return fileStat.st_size;
}

ssize_t File::read(char *data, size_t length)
{
    if ((nullptr == data) || (length == 0))
    {
        loge("read fail, buffer[nullptr] length[%ld]\n", length);
        return -1;
    }

    return ::read(fd, data, length);
}

ssize_t File::write(const char *data, size_t length)
{
    if (nullptr == data)
    {
        loge("write fail, length[%ld]\n", length);
        return -1;
    }

    ssize_t ret = -1;
    if (length == 0)
    {
        errno = 0;
        ret = ::write(fd, data, length);
        if (-1 == ret)
        {
            loge("write file fail[%s], length[%ld].\n", strerror(errno), length);
            return -1;
        }
        fsync(fd);
        return ret;
    }

    size_t cntWrite = 0;
    while (cntWrite < length)
    {
        errno = 0;
        ret = ::write(fd, data + cntWrite, length - cntWrite);
        if (-1 == ret)
        {
            loge("write file fail[%s].\n", strerror(errno));
            break;
        }
        cntWrite += ret;
    }
    fsync(fd);
    return (cntWrite > 0) ? cntWrite : ret;
}

ssize_t FileUtility::readFile(const std::string &fileName, char *data, size_t length)
{
    if ((nullptr == data) || (length == 0))
    {
        loge("readFile fail, length[%ld]\n", length);
        return -1;
    }

    File file;
    int ret = file.open(fileName, O_RDONLY);
    if (-1 == ret)
    {
        return -1;
    }

    ssize_t readSize = file.read(data, length);
    if (readSize < 0)
    {
        loge("read fail. readSize[%ld] != fileSize[%lu]\n", readSize, file.getFileSize());
        return -1;
    }

    return readSize;
}

bool FileUtility::readFile(const std::string &fileName, std::vector<char> &data)
{
    data.clear();
    File file;
    int ret = file.open(fileName, O_RDONLY);
    if (-1 == ret)
    {
        return false;
    }

    ssize_t size = file.getFileSize();
    if (size < 0)
    {
        return false;
    }
    if (size > 0) // 0 == size，不读
    {
        data.resize(size);
        ssize_t readSize = file.read(&data[0], size);
        if (size != readSize)
        {
            loge("readFile fail. readSize[%ld] != fileSize[%ld]\n", readSize, size);
            return false;
        }
    }

    return true;
}

int FileUtility::writeFile(const std::string &fileName, const char *data, size_t length)
{
    if (nullptr == data)
    {
        loge("writeFile fail, length[%ld]\n", length);
        return -1;
    }

    File file;
    int ret = file.open(fileName, O_CREAT | O_TRUNC | O_RDWR);
    if (-1 == ret)
    {
        return -1;
    }

    ssize_t writeSize = file.write(data, length);
    if (writeSize != static_cast<ssize_t>(length))
    {
        loge("write fail. writeSize[%ld] != size[%ld]\n", writeSize, length);
        return -1;
    }

    return writeSize;
}

ssize_t FileUtility::readEncryptFile(const std::string &fileName, char *data, size_t length)
{
    if ((nullptr == data) || (length == 0))
    {
        loge("readEncryptFile fail, length[%ld]\n", length);
        return -1;
    }

    ssize_t readSize = readFile(fileName, data, length);
    if (readSize <= 0)
    {
        return -1;
    }

    // Decrypt the encrypted file
    unsigned char *decryptedFile;
    int decryptedFileLength = aesDecrypt(reinterpret_cast<unsigned char *>(data), readSize, &decryptedFile);
    if (-1 == decryptedFileLength)
    {
        loge("Decryption failed\n");
        return -1;
    }

    memcpy(data, decryptedFile, decryptedFileLength);

    if (nullptr != decryptedFile)
    {
        free(decryptedFile);
    }
    return decryptedFileLength;
}

int FileUtility::writeEncryptFile(const std::string &fileName, const char *data, size_t length)
{
    if ((nullptr == data) || (length == 0))
    {
        loge("writeEncryptFile fail, length[%ld]\n", length);
        return -1;
    }

    File file;
    int ret = file.open(fileName, O_CREAT | O_TRUNC | O_RDWR);
    if (-1 == ret)
    {
        return -1;
    }

    unsigned char *encryptedFile;
    int encryptedFileLength = aesEncrypt(reinterpret_cast<const unsigned char *>(data), length, &encryptedFile);
    if (-1 == encryptedFileLength)
    {
        loge("Encryption failed\n");
        return -1;
    }

    // Write the encrypted file to its own file
    file.write(reinterpret_cast<char *>(encryptedFile), encryptedFileLength);
    if (nullptr != encryptedFile)
    {
        free(encryptedFile);
    }

    return 0;
}

int FileUtility::readDecryptAndHashFile(const std::string &fileName, std::vector<uint8_t> &data)
{
    if (fileName.size() == 0)
    {
        loge("readDecryptAndHashFile fail, fileName:%s\n", fileName.c_str());
        return -1;
    }

    uint32_t len = 0;
    uint32_t crc32 = 0;
    std::vector<uint8_t> readData;
    ssize_t fileSize = FileUtility::getFileSize(fileName);
    readData.resize(fileSize);

    // encrypted readData = data len + data + crc32
    ssize_t readSize = readFile(fileName, reinterpret_cast<char *>(readData.data()), fileSize);
    if (readSize <= 4 + 4 || readSize != fileSize)
    {
        loge("readDecryptAndHashFile fail, readSize:%ld, fileSize:%ld\n", readSize, fileSize);
        return -1;
    }

    // Decrypt the encrypted file
    uint8_t *decryptedFile = nullptr;
    int decryptedFileLength = aesDecrypt(static_cast<uint8_t *>(readData.data()), readSize, &decryptedFile);
    if (decryptedFileLength <= 4 + 4)
    {
        loge("readDecryptAndHashFile aesDecrypt failed\n");
        return -1;
    }

    readData.assign(static_cast<uint8_t *>(decryptedFile), static_cast<uint8_t *>(decryptedFile) + decryptedFileLength);
    if (nullptr != decryptedFile)
    {
        free(decryptedFile);
    }

    // parse readData: data len + data + crc32
    if (readData.size() < sizeof(len))
    {
        loge("readDecryptAndHashFile failed, readData too short\n");
        return -1;
    }
    std::copy(readData.begin(), readData.begin() + sizeof(len), reinterpret_cast<uint8_t *>(&len));

    if (readData.size() < sizeof(len) + len + sizeof(crc32) || len <= 0)
    {
        loge("readDecryptAndHashFile fail, readData.size:%u, data len:%u\n", readData.size(), len);
        return -1;
    }
    std::copy(readData.begin() + sizeof(len), readData.begin() + sizeof(len) + len, std::back_inserter(data));
    std::copy(readData.begin() + sizeof(len) + len, readData.begin() + sizeof(len) + len + sizeof(crc32), reinterpret_cast<uint8_t *>(&crc32));

    // check crc32
    uint32_t calCRC = crc_32(static_cast<const unsigned char *>(data.data()), data.size());
    if (calCRC != crc32)
    {
        loge("[readDecryptAndHashFile]crc failed, expected crc32=0x%x, actual crc32=0x%x\r\n", crc32, calCRC);
        return -1;
    }

    return 0;
}

int FileUtility::writeEncryptAndHashFile(const std::string &fileName, const std::vector<uint8_t> &data)
{
    if (fileName.size() == 0 || data.size() <= 0)
    {
        loge("writeEncryptAndHashFile fail, fileName:%s, data size:%lu\n", fileName.c_str(), data.size());
        return -1;
    }

    std::vector<uint8_t> writeData;
    writeData.clear();
    uint32_t len = data.size();
    uint32_t crc32 = crc_32(static_cast<const unsigned char *>(data.data()), data.size());

    // writeData = len + data + crc32
    std::copy(reinterpret_cast<uint8_t *>(&len), (reinterpret_cast<uint8_t *>(&len)) + sizeof(len), std::back_inserter(writeData));
    writeData.insert(writeData.end(), data.begin(), data.begin() + len);
    std::copy(reinterpret_cast<uint8_t *>(&crc32), (reinterpret_cast<uint8_t *>(&crc32)) + sizeof(crc32), std::back_inserter(writeData));

    File file;
    int ret = file.open(fileName, O_CREAT | O_TRUNC | O_RDWR);
    if (-1 == ret)
    {
        loge("writeEncryptAndHashFile open file failed\n");
        return -1;
    }

    uint8_t *encryptedFile = nullptr;
    int encryptedFileLength = aesEncrypt(static_cast<const unsigned char *>(writeData.data()), writeData.size(), &encryptedFile);
    if (encryptedFileLength == -1)
    {
        loge("writeEncryptAndHashFile aesEncrypt failed\n");
        return -1;
    }

    // Write the encrypted file to its own file
    file.write(reinterpret_cast<const char *>(encryptedFile), encryptedFileLength);
    if (nullptr != encryptedFile)
    {
        free(encryptedFile);
    }

    return 0;
}

int FileUtility::aesEncrypt(const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage)
{
    Encrypt encrypt;
    // Allocate memory for everything
    size_t blockLength = 0;
    size_t encryptedMessageLength = 0;

    *encryptedMessage = static_cast<unsigned char *>(malloc(messageLength + AES_BLOCK_SIZE));
    if (encryptedMessage == nullptr)
    {
        return -1;
    }

    if (!encrypt.init(static_cast<unsigned char*>(aesKey), static_cast<unsigned char*>(aesIv)))
    {
        loge("encrypt init fail.\n");
        return -1;
    }

    if (!encrypt.update(*encryptedMessage, reinterpret_cast<int *>(&blockLength), static_cast<const unsigned char *>(message), messageLength))
    {
        loge("encrypt update fail.\n");
        return -1;
    }

    encryptedMessageLength += blockLength;
    if (!encrypt.final(*encryptedMessage + encryptedMessageLength, reinterpret_cast<int *>(&blockLength)))
    {
        loge("encrypt final fail.\n");
        return -1;
    }

    return encryptedMessageLength + blockLength;
}

int FileUtility::aesDecrypt(unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char **decryptedMessage)
{
    Decrypt decrypt;
    // Allocate memory for everything
    size_t decryptedMessageLength = 0;
    size_t blockLength = 0;

    *decryptedMessage = static_cast<unsigned char *>(malloc(encryptedMessageLength));
    if (*decryptedMessage == nullptr)
    {
        return -1;
    }

    if (!decrypt.init(reinterpret_cast<const unsigned char *>(aesKey), reinterpret_cast<const unsigned char *>(aesIv)))
    {
        loge("decrypt init fail.\n");
        return -1;
    }

    if (!decrypt.update(static_cast<unsigned char *>(*decryptedMessage), reinterpret_cast<int *>(&blockLength), encryptedMessage, static_cast<int>(encryptedMessageLength)))
    {
        loge("decrypt update fail.\n");
        return -1;
    }
    decryptedMessageLength += blockLength;

    if (!decrypt.final(static_cast<unsigned char *>(*decryptedMessage) + decryptedMessageLength, reinterpret_cast<int *>(&blockLength)))
    {
        loge("decrypt final fail.\n");
        return -1;
    }
    decryptedMessageLength += blockLength;

    return static_cast<int>(decryptedMessageLength);
}

// 支持查询目录及文件是否存在
bool FileUtility::exist(const std::string &fileName)
{
    return (::access(fileName.c_str(), 0) == 0);
}

int FileUtility::rmFile(const std::string &fileName)
{
    if (!exist(fileName))
    {
        logw("rmFile[no file]\n");
        return -1;
    }
    char cmd[FILE_CMD_MAX] = {0};
    snprintf(static_cast<char*>(cmd), sizeof(cmd) - 1, "rm -f %s", fileName.c_str());
    doSystemCall(static_cast<char*>(cmd));
    return 0;
}

int FileUtility::rmDir(const std::string &fileName)
{
    if (!exist(fileName))
    {
        logw("rmDir[no file dir]\n");
        return -1;
    }

    char cmd[FILE_CMD_MAX] = {0};
    snprintf(static_cast<char*>(cmd), sizeof(cmd) - 1, "rm -rf %s", fileName.c_str());
    doSystemCall(static_cast<char*>(cmd));
    return 0;
}

int FileUtility::mkDir(const std::string &fileName)
{
    if (exist(fileName))
    {
        logw("mkDir[file is exist]\n");
        return -1;
    }

    char cmd[FILE_CMD_MAX] = {0};
    snprintf(static_cast<char*>(cmd), sizeof(cmd) - 1, "mkdir -p %s", fileName.c_str());
    doSystemCall(static_cast<char*>(cmd));
    return 0;
}

// 支持目录及文件重命名
int FileUtility::rename(const std::string &fileOldName, const std::string &fileNewName)
{
    if (!exist(fileOldName))
    {
        logw("rename[no file]\n");
        return -1;
    }

    return ::rename(fileOldName.c_str(), fileNewName.c_str());
}

// 支持目录及文件拷贝
int FileUtility::copy(const std::string &fileOldName, const std::string &fileNewName)
{
    if (!exist(fileOldName))
    {
        logw("copy[no file]\n");
        return -1;
    }

    char cmd[FILE_CMD_MAX] = {0};
    snprintf(static_cast<char*>(cmd), sizeof(cmd) - 1, "cp -rf %s %s", fileOldName.c_str(), fileNewName.c_str());
    doSystemCall(static_cast<char*>(cmd));
    return 0;
}

// 获取文件大小
int FileUtility::getFileSize(const std::string &fileName)
{
    if (!exist(fileName))
    {
        loge("[no file]\n");
        return -1;
    }

    struct stat info;
    stat(fileName.c_str(), &info);

    return info.st_size;
}

}// namespace