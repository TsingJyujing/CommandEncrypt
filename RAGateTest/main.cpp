#include <stdio.h>
#include <conio.h>
#include "RAEncrypt.h"
#include "sha2.h"
#include "rsa.h"
#include <string.h>

#define FUCK_VISUAL_STUDIO

void loadIntegerFromFile(extInteger I, char *fileName){

}
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

	//Verify RSA encrypt
	rsa_key key;
	bigInteger text, d;
	char verify_data[3][32];
	for (i = 0; i<30; i++){
		verify_data[1][i] = '1';
		verify_data[2][i] = '1';
	}
	verify_data[1][30] = '0';
	verify_data[2][30] = '1';
	verify_data[1][31] = '1';
	verify_data[2][31] = 'a';
	hn(key.p, verify_data[1]);
	hn(key.q, verify_data[2]);

	unsigned short r;
	for (r = 0; r<16; r++){
		text[r] = r;
	}
	
	rsa_gen(&key);
	rsa_enc(text, &key);

	cp(d, text);
	em(d, key.d, key.pq); /* slow way */
	rsa_dec(d, &key); /* faster way */

#ifdef FUCK_VISUAL_STUDIO
	_getch();
#else
	getch();
#endif
	return 0;
}