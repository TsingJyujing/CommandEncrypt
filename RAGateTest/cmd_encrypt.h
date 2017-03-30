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
	// ע��dataSize���ܳ���124byte��992bit

	/**
	* @function ����д��У�����
	* @param key ˽Կ/��Կ(�ͽ��ܵ�ʱ�������෴)
	* @param modulus ģ��
	* @param rawData ԭʼ���ݣ��벻Ҫ����124�ֽڣ�
	* @param dataSize ���ݴ�С
	* @param outputData ����ļ��ܺ������
		��һ����СΪPASSWORD_BYTES������
		��ϸ�������RSA.H�ļ�
	* @return RSAִ���еĴ���״̬
	*/
	RSAErrorType RSAEncrypt(
		bigInteger key, bigInteger modulus, 
		byteArray rawData, uint8 dataSize, 
		byteArray outputData);

	/**
	* @function ���ܲ���У����
	* @param key ��Կ/˽Կ(�ͼ��ܵ�ʱ�������෴)
	* @param modulus ģ��
	* @param encryptedData ���ܺ�����ݣ���һ����СΪPASSWORD_BYTES������
	* @param outputData ����Ľ��ܺ������
	* @param outDataSize ���ܳ������ݵĴ�С 
	* @return RSAִ���еĴ���״̬
	*/
	RSAErrorType RSADecrypt(
		bigInteger key, bigInteger modulus, 
		byteArray encryptedData, 
		byteArray outputData, uint8 * outDataSize);

	/**
	* @function ʹ��˽Կ���ĵ���������ǩ��
	* @param document ��Ҫǩ������Ϣ
	* @param docSize �ĵ���С
	* @param privateKey ˽Կ
	* @param modulus ģ��
	* @param fingerPrint ǩ��ָ�ƣ���һ����СΪPASSWORD_BYTES������
	* @return ִ���еĴ���״̬
	*/
	RSAErrorType digitalFingerPrintGenerate(
		byteArray document, uint32 docSize,
		bigInteger privateKey, bigInteger modulus,
		byteArray fingerPrint
		);

	/**
	* @function ʹ�ù�Կ�������ǩ��
	* @param document ��Ҫ����ǩ������Ϣ
	* @param docSize �ĵ���С
	* @param privateKey ��Կ
	* @param modulus ģ��
	* @param fingerPrint ǩ��ָ�ƣ���һ����СΪPASSWORD_BYTES������
	* @return ִ���еĴ���״̬
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