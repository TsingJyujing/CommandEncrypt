/* 
 * File:   rsa_common.h
 * Author: Yuan Yifan
 *
 * Created on 2017年4月2日, 下午12:03
 */

#ifndef RSA_COMMON_H
#define RSA_COMMON_H

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

    void freeKey( bytesBuffer *bf );
    
    void loadKey(bytesBuffer *bf, unsigned char *data, unsigned int dataSize);

#ifdef __cplusplus
}
#endif

#endif /* RSA_COMMON_H */

