#ifndef COMMON_ERROR_CODE_H_
#define COMMON_ERROR_CODE_H_

typedef enum error_code
{
    VCU_OK = 0,      // 无异常
    VCU_FAILED = -1, // 失败
    VCU_CRC_CHECK_FAILED = -2, // 校验失败
} ErrorCode;

#endif // COMMON_ERROR_CODE_H_
