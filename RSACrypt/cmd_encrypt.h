#ifndef __CMD_ENCRYPT_HEADFILE__
#define __CMD_ENCRYPT_HEADFILE__

/**
 * @file cmd_encrypt.h
 * @author 袁逸凡
 * @function 指令加密系统和数字签名系统
 */
 
#include <string.h>
#include <stdlib.h>
#include "rsa_common.h"
#include "md5.h"

#define ASSERT(x) (x?0x00:0xFF)
#define ASSERT_OR(x,y) (y|ASSERT(x))

#ifdef USE_GMP_LIBRARY
    #include "mini-gmp.h"
    #define ENDIAN 0
    #define NAILS 0
    #define ORDER 1
    #define SIZE_UNIT 1
#else
    #error "TODO: HAVEN'T REALISTIC FUNCTION WITHOUT GMP LIBRARY."
#endif

typedef enum {
    NO_ERROR = 0,
    TO_MUCH_DATA = 1,
    DATA_SIZE_OVERFLOW = 2,
    VERIFY_FAILED = 3
} RSAErrorType;

#define MAX_ENCRYPT_SIZE 120
typedef unsigned char * byteArray;
typedef unsigned char byte;

#ifdef __cplusplus
extern "C" {
#endif
    #ifdef USE_GMP_LIBRARY
    /**
     * @function 数组转大数的函数，其实完全可以私有的
     * @param key 私钥/公钥(和解密的时候正好相反)
     * @param modulus 模数
     */
    void byteBuffer2bigInteger(bytesBuffer bf, mpz_t bigInteger);
    #endif
    
    // RSA对byteBuffer的加密和解密
    // 注意dataSize不能超过120byte即960bit
    /**
     * @function 数据写入校验加密
     * @param key 私钥/公钥(和解密的时候正好相反)
     * @param modulus 模数
     * @param rawData 原始数据（请不要大于124字节）
     * @param dataSize 数据大小
     * @param outputData 输出的加密后的数据
            是一个大小为PASSWORD_BYTES的数组
            详细定义请见RSA.H文件
     * @return RSA执行中的错误状态
     */
    RSAErrorType RSAEncrypt(
            RSAPassword key,
            byteArray rawData, unsigned char dataSize,
            byte outputData[ENCRYPT_BLOCK_BYTE_SIZE]);

    /**
     * @function 解密并且校验检查
     * @param key 公钥/私钥(和加密的时候正好相反)
     * @param modulus 模数
     * @param encryptedData 加密后的数据，是一个大小为PASSWORD_BYTES的数组
     * @param outputData 输出的解密后的数据
     * @param outDataSize 解密出的数据的大小 
     * @return RSA执行中的错误状态
     */
    RSAErrorType RSADecrypt(
            RSAPassword key,
            byte encryptedData[ENCRYPT_BLOCK_BYTE_SIZE],
            byteArray outputData, unsigned char * outDataSize);

    /**
     * @function 使用私钥对文档生成数字签名
     * @param document 需要签名的信息
     * @param docSize 文档大小
     * @param privateKey 私钥
     * @param modulus 模数
     * @param fingerPrint 签名指纹，是一个大小为PASSWORD_BYTES的数组
     * @return 执行中的错误状态
     */
    RSAErrorType digitalFingerPrintGenerate(
            byteArray document, unsigned int docSize,
            RSAPassword privateKey,
            byteArray fingerPrint
            );

    /**
     * @function 使用公钥检查数字签名
     * @param document 需要核验签名的信息
     * @param docSize 文档大小
     * @param privateKey 公钥
     * @param modulus 模数
     * @param fingerPrint 签名指纹，是一个大小为PASSWORD_BYTES的数组
     * @return 执行中的错误状态
     */
    RSAErrorType digitalFingerPrintCheck(
            byteArray document, unsigned int docSize,
            RSAPassword publicKey,
            byteArray fingerPrint
            );

#ifdef __cplusplus
}
#endif
#endif

