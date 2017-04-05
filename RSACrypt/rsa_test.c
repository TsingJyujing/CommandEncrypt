#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mini-gmp.h"
#include "rsa_common.h"
#include "cmd_encrypt.h"
#include "hex_utility.h"


#define USE_BUFFER_SIZE 512

int main(void) {

    unsigned char *Str = "My love was a red red rose.";
    RSAPassword publicKey;
    RSAPassword privateKey;

    byte buffer[USE_BUFFER_SIZE];
    byte outputData[ENCRYPT_BLOCK_BYTE_SIZE] = {0};
    unsigned int sizeWritten;

    unsigned char sizeBuffer = 0;
    
    RSAErrorType E1, E2;
    
    //加载密钥
    loadHex("key/private_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(privateKey.key), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of private key" );
        
    loadHex("key/public_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(publicKey.key), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of public key" );
        
    loadHex("key/modulus.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    loadKey(&(publicKey.modulus), buffer, sizeWritten);
    loadKey(&(privateKey.modulus), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of modulus" );
        
    

    //加密和解密
    E1 = RSAEncrypt(privateKey, (byteArray) Str, (unsigned char) (strlen((const char *)Str) + 1), outputData);
    printByteArrayComment(outputData, ENCRYPT_BLOCK_BYTE_SIZE, 16, "Encrypted file");
    
    E2 = RSADecrypt(publicKey, outputData, (byteArray) buffer, &sizeBuffer);
    printf( "Size buffer:%d\n" , sizeBuffer );
    //printByteArrayComment(buffer, sizeBuffer, 16, "Decrypted file");
    
    printf("Status:(%d,%d)\nDecrypt result: %s\n", E1, E2, buffer);
    
    freeKey(&(publicKey.modulus));
    freeKey(&(publicKey.key));
    freeKey(&(privateKey.modulus));
    freeKey(&(privateKey.key));
}


