#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "cmd_encrypt.h"
#include "sha2.h"
#include "rsa.h"
#include "hex_utility.h"

#define FUCK_VISUAL_STUDIO

void testLoadIntegerFromFile(){
	byte Data[255] = { 0 };
	int dSize = 0;
	loadHex("key/private_key.hex", Data, 255, &dSize);
	printf("Public key hex size: %d bytes\n", dSize);
}

void testSHA(){
	// Verify SHA Module
	char *TestData = "My love is a red rose.";
	unsigned char SHADigest[SHA224_DIGEST_SIZE];

	int i = 0;
	sha224_ctx shactx;
	sha224_init(&shactx);
	sha224_update(&shactx, (const unsigned char *)TestData, strlen(TestData));
	sha224_final(&shactx, SHADigest);
	printf("SHA224 of %s\n", TestData);
	for (i = 0; i<SHA224_DIGEST_SIZE; ++i) {
		printf("%02X ", SHADigest[i]);
	}
	printf("\n");
}

void testBigIntegerLibrary(){
	bigInteger a = { 0 }, b = { 0 }, c = { 0 };
	a[0] = 123;
	b[0] = 115;
	c[0] = 1717;
	em(a, b, c);
	printf("%x_%x", a[0], a[1]);
}

void testEncodeDecode(){
	int writtenSize = 0;
	byte dataBuffer[2048] = { 0 };
	char * dataEncode = "My love is a red red rose.";

	bigInteger privateKey = { 0 };
	loadHex("key/private_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS/8, &writtenSize);
	printf("Private key size: %d\n", writtenSize);
	loadKey(privateKey, dataBuffer, writtenSize);

	bigInteger publicKey = { 0 };
	loadHex("key/public_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Public key size: %d\n", writtenSize);
	loadKey(publicKey, dataBuffer, writtenSize);

	bigInteger M = { 0 };
	loadHex("key/modulus.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Modulus size: %d\n", writtenSize);
	loadKey(M, dataBuffer, writtenSize);
	
	bigInteger bigIntData = { 0 };
	
	loadKey(bigIntData, (unsigned char *)dataEncode, strlen(dataEncode) + 1);

	em(bigIntData, privateKey, M);
	printf("Encoded.\n");
	em(bigIntData, publicKey, M);

	writeKey(bigIntData, dataBuffer);
	printf("Out:%s\n", dataBuffer);

}

void testEncryptModule(){
	int writtenSize = 0;
	byte dataBuffer[256] = { 0 };
	char * dataEncode = "My love is a red red rose.";
	byte decodeBuffer[256] = { 0 };
	bigInteger privateKey = { 0 };
	
	loadHex("key/private_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Private key size: %d\n", writtenSize);
	loadKey(privateKey, dataBuffer, writtenSize);

	bigInteger publicKey = { 0 };
	loadHex("key/public_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Public key size: %d\n", writtenSize);
	loadKey(publicKey, dataBuffer, writtenSize);

	bigInteger M = { 0 };
	loadHex("key/modulus.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Modulus size: %d\n", writtenSize);
	loadKey(M, dataBuffer, writtenSize);

	uint8 decodeSize = 0;
	int encRes = RSAEncrypt(privateKey, M, (unsigned char *)dataEncode, strlen(dataEncode) + 1, dataBuffer);
	int decRes = RSADecrypt(publicKey, M, dataBuffer, decodeBuffer, &decodeSize);
	printf("Size:%d Data:%s\n", decodeSize, decodeBuffer);
}

void fpTest(){
	int writtenSize = 0;
	byte dataBuffer[256] = { 0 };
	char * document = "O, my love is like a red , red rose, That is newly sprung in June. O, my love is like the melody.";
	char * documentFake = "O, my love is like a red , red rose, That is newly sprung in June. 0, my love is like the melody.";
	byte fpbuf[256] = { 0 };
	bigInteger privateKey = { 0 };

	loadHex("key/private_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Private key size: %d\n", writtenSize);
	loadKey(privateKey, dataBuffer, writtenSize);

	bigInteger publicKey = { 0 };
	loadHex("key/public_key.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Public key size: %d\n", writtenSize);
	loadKey(publicKey, dataBuffer, writtenSize);

	bigInteger M = { 0 };
	loadHex("key/modulus.hex", dataBuffer, BIG_INTEGER_SIZE*UNIT_BITS / 8, &writtenSize);
	printf("Modulus size: %d\n", writtenSize);
	loadKey(M, dataBuffer, writtenSize);

	int resGen = digitalFingerPrintGenerate((byteArray)document, strlen(document), privateKey, M, fpbuf);
	int resVal = digitalFingerPrintCheck((byteArray)document, strlen(document), publicKey, M, fpbuf);
	int resValFix = digitalFingerPrintCheck((byteArray)documentFake, strlen(document), publicKey, M, fpbuf);
	printf("Generate finger print result:%d\n", resGen);
	printf("Finger print check (no fix):%d\n", resVal);
	printf("Finger print check (fixed):%d\n", resValFix);
}
	
int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	// TODO Verify modules here
	fpTest();
#ifdef FUCK_VISUAL_STUDIO
	#pragma warning(suppress: 6031)
 	_getch();
#else
	getch();
#endif
	return 0;
}