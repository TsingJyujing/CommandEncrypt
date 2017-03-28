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
	// ��Կ�����л��ͷ����л���byteBuffer<-->bigInteger��
	void loadKey(bigInteger key, unsigned char *keyData, int dataSize);
	void writeKey(bigInteger key, unsigned char *keyData);

	// RSA��byteBuffer�ļ��ܺͽ���
	// ע��dataSize���ܳ���124byte=992bit

	// ����д��У�����
	RSAErrorType RSAEncrypt(
		bigInteger key, bigInteger modulus, 
		byteArray rawData, uint8 dataSize, 
		byteArray outputData);

	// ���ܲ���У����
	RSAErrorType RSADecrypt(
		bigInteger key, bigInteger modulus, 
		byteArray encryptedData, 
		byteArray outputData, uint8 * outDataSize);

	//ʹ��˽Կ���ĵ���������ǩ��
	RSAErrorType digitalFingerPrintGenerate(
		byteArray document, uint32 docSize,
		bigInteger privateKey, bigInteger modulus,
		byteArray fingerPrint
		);//Finger Print Size: PASSWORD_BYTES

	//ʹ�ù�Կ�������ǩ��
	RSAErrorType digitalFingerPrintCheck(
		byteArray document, uint32 docSize,
		bigInteger publicKey, bigInteger modulus,
		byteArray fingerPrint
		);

#ifdef __cplusplus
}
#endif
#endif