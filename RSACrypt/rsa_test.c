#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gmp.h"
#include "hex_utility.h"
#include "rsa_common.h"
#include <malloc.h>
#include "cmd_encrypt.h"

#define USE_BUFFER_SIZE 1024

int main(void) {

    unsigned char *Str = "My love was a red red rose.";
    RSAPassword publicKey;
    RSAPassword privateKey;

    byte buffer[USE_BUFFER_SIZE];
    byte outputData[ENCRYPT_BLOCK_BYTE_SIZE] = {0};
    unsigned int sizeWritten;

    //加载密钥
    loadHex("key/private_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(privateKey.key), buffer, sizeWritten);

    loadHex("key/public_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(publicKey.key), buffer, sizeWritten);

    loadHex("key/modulus.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(publicKey.modulus), buffer, sizeWritten);
    loadKey(&(privateKey.modulus), buffer, sizeWritten);

    unsigned char sizeBuffer = 0;

    //加密和解密
    RSAErrorType E1 = RSAEncrypt(privateKey, (byteArray) Str, (unsigned char) (strlen(Str) + 1), outputData);
    printByteArrayFixWidth(outputData, ENCRYPT_BLOCK_BYTE_SIZE, 16);
    RSAErrorType E2 = RSADecrypt(publicKey, outputData, (byteArray) buffer, &sizeBuffer);
    printf("Status:(%d,%d)\nDecrypt result: %s\n", E1, E2, buffer);

    freeKey(&(publicKey.modulus));
    freeKey(&(publicKey.key));
    freeKey(&(privateKey.modulus));
    freeKey(&(privateKey.key));
}


