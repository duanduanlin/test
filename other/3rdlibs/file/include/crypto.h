/*
 * Copyright 2022-2036 JiangLing Motor Co.Ltd. All Rights Reserved.
 *
 * @Author: zjiang4 zjiang4@jmc.com.cn
 * @Date: 2022-12-13 09:02
 * @Description: aes加密/解密
 */

#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>

namespace file_operation
{
class Encrypt
{
public:
    Encrypt();
    virtual ~Encrypt();
    int init(const unsigned char *aesKey, const unsigned char *aesIv);
    int update(unsigned char *out, int *outLen, const unsigned char *in, int inLen);
    int final(unsigned char *out, int *outLen);

private:
    EVP_CIPHER_CTX *aesContext;
};

class Decrypt
{
public:
    Decrypt();
    virtual ~Decrypt();
    int init(const unsigned char *aesKey, const unsigned char *aesIv);
    int update(unsigned char *out, int *outLen, const unsigned char *in, int inLen);
    int final(unsigned char *out, int *outLen);

private:
    EVP_CIPHER_CTX *aesContext;
};

}
using namespace file_operation;

#endif
