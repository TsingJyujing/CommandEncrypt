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

    unsigned char *str =        "My love was a red red rose.";
    unsigned char *strSame =    "My love was a red red rose.";
    unsigned char *strDiff =    "My love was a red red rose~";
    
    RSAPassword publicKey;
    RSAPassword privateKey;

    byte buffer[USE_BUFFER_SIZE];
    byte outputData[ENCRYPT_BLOCK_BYTE_SIZE] = {0};
    byte fingerprint[ENCRYPT_BLOCK_BYTE_SIZE];
    unsigned int sizeWritten;

    unsigned char sizeBuffer = 0;
    
    RSAErrorType E1, E2;
    
    //从文件加载密钥
    loadHex("key/private_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    newByteBuffer(&(privateKey.key), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of private key" );
        
    loadHex("key/public_key.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    newByteBuffer(&(publicKey.key), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of public key" );
        
    loadHex("key/modulus.hex", buffer, USE_BUFFER_SIZE, &sizeWritten);
    newByteBuffer(&(publicKey.modulus), buffer, sizeWritten);
    newByteBuffer(&(privateKey.modulus), buffer, sizeWritten);
    printByteArrayComment( buffer, sizeWritten, 16, "Hex file of modulus" );
        
    

    //加密和解密
    E1 = RSAEncrypt(privateKey, (byteArray) str, (unsigned char) (strlen((const char *)str) + 1), outputData);
    printByteArrayComment(outputData, ENCRYPT_BLOCK_BYTE_SIZE, 16, "Encrypted file");
    
    E2 = RSADecrypt(publicKey, outputData, (byteArray) buffer, &sizeBuffer);
    printf( "Size buffer:%d\n" , sizeBuffer );
    printByteArrayComment(buffer, sizeBuffer, 16, "Decrypted file");
    
    printf("Status:(%d,%d)\nDecrypt result: %s\n", E1, E2, buffer);
    
    //签名和校验
    digitalFingerPrintGenerate(
            str, strlen((const char *)str),
            privateKey,
            fingerprint
            );
    printByteArrayComment(fingerprint, ENCRYPT_BLOCK_BYTE_SIZE, 16, "Document Finger Print");       
    printf("Same Check:%d\n", digitalFingerPrintCheck( strSame, strlen((const char *)strSame), publicKey, fingerprint ));
    printf("Difference Check:%d\n", digitalFingerPrintCheck( strDiff, strlen((const char *)strDiff), publicKey, fingerprint ));
    
    //释放内存
    deleteByteBuffer(&(publicKey.modulus));
    deleteByteBuffer(&(publicKey.key));
    deleteByteBuffer(&(privateKey.modulus));
    deleteByteBuffer(&(privateKey.key));
}


