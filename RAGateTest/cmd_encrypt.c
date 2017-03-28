#include "cmd_encrypt.h"
#include <string.h>
#include <stdlib.h>
#include "sha2.h"

void loadKey(bigInteger key, unsigned char *keyData, int dataSize){
	memcpy((unsigned char *)key, keyData, dataSize>PASSWORD_BYTES ? PASSWORD_BYTES : dataSize);
}
void writeKey(bigInteger key, unsigned char *keyData){
	memcpy(keyData, (unsigned char *)key, PASSWORD_BYTES);
}

RSAErrorType RSAEncrypt(
	bigInteger key, bigInteger modulus, 
	byteArray rawData, uint8 dataSize, 
	byteArray outputData){
	bigInteger edata = { 0 };
	uint16 i;
	byte buffer[PASSWORD_BYTES] = { 0 };
	//开头第一个字节为0，写入校验值
	buffer[0] = 0x00;
	for (i = 0; i < dataSize; i++){
		buffer[0] ^= rawData[i];
	}
	//第2、3字节为随机盐，防止选择密文攻击
	buffer[1] = rand() & 0xff;
	buffer[2] = rand() & 0xff;
	//将长度写入开头的第一个字节中
	if (dataSize > 124) {
		return TO_MUCH_DATA;
	}
	else{
		buffer[3] = dataSize;
	}
	//拷贝数组
	memcpy(buffer + 4, rawData, dataSize);
	loadKey(edata, buffer, PASSWORD_BYTES);
	em(edata, key, modulus);
	writeKey(edata, outputData);
	return NO_ERROR;
}


RSAErrorType RSADecrypt(
	bigInteger key, bigInteger modulus,
	byteArray encryptedData,
	byteArray outputData, uint8 * outDataSize){

	byte buffer[PASSWORD_BYTES] = { 0 };
	bigInteger edata = { 0 };
	uint16 i;
	uint8 dataSize = 0;
	uint8 validCheck = 0;

	loadKey(edata, encryptedData, PASSWORD_BYTES);
	em(edata, key, modulus);
	writeKey(edata, buffer);
	dataSize = buffer[3];
	if (dataSize > 124) {
		return DATA_SIZE_OVERFLOW;
	}
	for (i = 0; i < dataSize; i++){
		validCheck ^= buffer[i + 4];
	}
	if (validCheck != buffer[0]){
		return VERIFY_FAILED;
	}
	memcpy(outputData, buffer + 4, dataSize);
	*outDataSize = dataSize;
	return NO_ERROR;
}

RSAErrorType digitalFingerPrintGenerate(
	byteArray document, uint32 docSize,
	bigInteger privateKey, bigInteger modulus,
	byteArray fingerPrint
	){
	byte SHADigest[SHA512_DIGEST_SIZE] = { 0 };
	sha512(document, docSize, SHADigest);
	return RSAEncrypt(
		privateKey, modulus,
		SHADigest, SHA512_DIGEST_SIZE,
		fingerPrint);
}

RSAErrorType digitalFingerPrintCheck(
	byteArray document, uint32 docSize,
	bigInteger publicKey, bigInteger modulus,
	byteArray fingerPrint
	){
	byte SHADigest[SHA512_DIGEST_SIZE] = {0};
	byte SHADigestDecrypt[SHA512_DIGEST_SIZE] = { 0 };
	uint32 decryptResult;
	uint8 decryptSize;
	sha512(document, docSize, SHADigest);

	decryptResult = RSADecrypt(
		publicKey, modulus,
		fingerPrint,
		SHADigestDecrypt, &decryptSize);
	if (decryptResult != NO_ERROR || decryptSize != SHA512_DIGEST_SIZE){
		return decryptResult;
	}
	else{
		decryptResult = memcmp(SHADigestDecrypt, SHADigest, SHA512_DIGEST_SIZE);
		return decryptResult == 0 ? NO_ERROR : VERIFY_FAILED;
	}
	
}