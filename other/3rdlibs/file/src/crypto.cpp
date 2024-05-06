#include "log.hpp"
#include "crypto.h"

using namespace std;
namespace file_operation
{
Encrypt::Encrypt()
{
    aesContext = nullptr;
}

Encrypt::~Encrypt()
{
    if (nullptr != aesContext)
    {
        EVP_CIPHER_CTX_free(aesContext);
    }
}

int Encrypt::init(const unsigned char *aesKey, const unsigned char *aesIv)
{
    // Initalize contexts
    aesContext = EVP_CIPHER_CTX_new();
    if (nullptr == aesContext)
    {
      return 0;
    }

    /* Don't set key or IV right away; we want to set lengths */
    EVP_CIPHER_CTX_init(aesContext);

    EVP_CipherInit_ex(aesContext, EVP_aes_256_cbc(), nullptr, nullptr, nullptr, 1);

    return EVP_EncryptInit_ex(aesContext, EVP_aes_256_cbc(), nullptr, aesKey, aesIv);
}

int Encrypt::update(unsigned char *out, int *outLen, const unsigned char *in, int inLen)
{
    return EVP_EncryptUpdate(aesContext, out, outLen, in, inLen);
}

int Encrypt::final(unsigned char *out, int *outLen)
{
    return EVP_EncryptFinal_ex(aesContext, out, outLen);
}

Decrypt::Decrypt()
{
    aesContext = nullptr;
}

Decrypt::~Decrypt()
{
    EVP_CIPHER_CTX_free(aesContext);
}

int Decrypt::init(const unsigned char *aesKey, const unsigned char *aesIv)
{
    // Initalize contexts
    aesContext = EVP_CIPHER_CTX_new();
    if (aesContext == nullptr)
    {
        loge("aesContext nullptr.\n");
        return 0;
    }

    /* Don't set key or IV right away; we want to set lengths */
    EVP_CIPHER_CTX_init(aesContext);

    return EVP_DecryptInit_ex(aesContext, EVP_aes_256_cbc(), nullptr, aesKey, aesIv);
}

int Decrypt::update(unsigned char *out, int *outLen, const unsigned char *in, int inLen)
{
    return EVP_DecryptUpdate(aesContext, out, outLen, in, inLen);
}
int Decrypt::final(unsigned char *out, int *outLen)
{
    return EVP_DecryptFinal_ex(aesContext, out, outLen);
}

}// namespace