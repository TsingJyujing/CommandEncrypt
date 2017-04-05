#ifndef RSA_COMMON_H
#define RSA_COMMON_H

/**
 * @file rsa_common.h
 * @author 袁逸凡
 * @function RSA通用设置文件，用来规范Key的形式，加载/释放key的工具集
 */
 
#define USE_GMP_LIBRARY

#define NULL_PTR ((void *)0)
#define ENCRYPT_BLOCK_BYTE_SIZE 128

typedef struct {
    unsigned char *data;
    unsigned int size;
} bytesBuffer;

typedef struct {
    bytesBuffer modulus;
    bytesBuffer key;
} RSAPassword;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @function 释放bytesBuffer占用的内存防止泄漏
     * @param bf 指向该bytesBuffer的指针
     */
    void deleteByteBuffer( bytesBuffer *bf );
    /**
     * @function 按需申请bytesBuffer需要的内存
     * @param bf 指向该bytesBuffer的指针
     * @param data 数据源
     * @param dataSize 数据大小
     */
    void newByteBuffer(bytesBuffer *bf, unsigned char *data, unsigned int dataSize);

#ifdef __cplusplus
}
#endif

#endif /* RSA_COMMON_H */

