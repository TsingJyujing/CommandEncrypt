#include <stdio.h>
#include <conio.h>
#include "RAEncrypt.h"
#include "rsa.h"
#include "sha2.h"
#include <string.h>

#define FUCK_VISUAL_STUDIO

int main(int argc, char **argv) {
	// TODO Verify modules here

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

	// Verify RSA Module
	byteint sk, pk, r;
	printf("Generate result:%d\n", RsaPrepare(sk, pk, r));
	printf("Write result:%d\n", WriteRsaFile(r, pk, sk));
	printf("Read result:%d\n", ReadRsaFile(r, pk, sk));
	printf("Key press any key to continue...\n");
#ifdef FUCK_VISUAL_STUDIO
	_getch();
#else
	getch();
#endif
	return 0;
}