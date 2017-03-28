#ifndef __CMD_ENCRYPT_HEADFILE__
#define __CMD_ENCRYPT_HEADFILE__
#include "rsa.h"
#include "hex_utility.h"

typedef enum {
	NO_ERROR = 0,
	TO_MUCH_DATA = 1,
	DATA_SIZE_OVERFLOW = 2,
	VERIFY_FAILED = 3
} RSAErrorType;

#ifdef __cplusplus
extern "C" {
#endif
	// 密钥的序列化和反序列化（byteBuffer<-->bigInteger）
	void loadKey(bigInteger key, unsigned char *keyData, int dataSize);
	void writeKey(bigInteger key, unsigned char *keyData);

	// RSA对byteBuffer的加密和解密
	// 注意dataSize不能超过124byte=992bit

	// 数据写入校验加密
	RSAErrorType RSAEncrypt(
		bigInteger key, bigInteger modulus, 
		byteArray rawData, uint8 dataSize, 
		byteArray outputData);

	// 解密并且校验检查
	RSAErrorType RSADecrypt(
		bigInteger key, bigInteger modulus, 
		byteArray encryptedData, 
		byteArray outputData, uint8 * outDataSize);

	//使用私钥对文档生成数字签名
	RSAErrorType digitalFingerPrintGenerate(
		byteArray document, uint32 docSize,
		bigInteger privateKey, bigInteger modulus,
		byteArray fingerPrint
		);//Finger Print Size: PASSWORD_BYTES

	//使用公钥检查数字签名
	RSAErrorType digitalFingerPrintCheck(
		byteArray document, uint32 docSize,
		bigInteger publicKey, bigInteger modulus,
		byteArray fingerPrint
		);

#ifdef __cplusplus
}
#endif
#endif