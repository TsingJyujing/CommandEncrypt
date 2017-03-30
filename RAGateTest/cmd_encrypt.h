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
	// 注意dataSize不能超过124byte即992bit

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
		bigInteger key, bigInteger modulus, 
		byteArray rawData, uint8 dataSize, 
		byteArray outputData);

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
		bigInteger key, bigInteger modulus, 
		byteArray encryptedData, 
		byteArray outputData, uint8 * outDataSize);

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
		byteArray document, uint32 docSize,
		bigInteger privateKey, bigInteger modulus,
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
		byteArray document, uint32 docSize,
		bigInteger publicKey, bigInteger modulus,
		byteArray fingerPrint
		);

#ifdef __cplusplus
}
#endif
#endif