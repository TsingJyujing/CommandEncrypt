#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hex_utility.h"

int main( void ) {

    //在这里输入你的密钥，可以是128bit，192bit或者256bit
    uint8_t key[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f
    };

    uint8_t raw[] = {
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xdd, 0xee, 0xff
    };

    uint8_t encrypted[16];
    uint8_t decrypted[16];

    aes_encrypt(raw, encrypted, key, sizeof(key));
    aes_decrypt(encrypted, decrypted, key, sizeof(key));
    
    printByteArrayComment(key,sizeof(key),8,"key");
    printByteArrayComment(raw,sizeof(raw),8,"raw");
    printByteArrayComment(encrypted,sizeof(encrypted),8,"encrypted");
    printByteArrayComment(decrypted,sizeof(decrypted),8,"decrypted");
    
}

