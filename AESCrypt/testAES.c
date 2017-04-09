#include <stdio.h>

int main(int argc, char *argv[]) {

    uint8_t i;
    
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

    uint8_t in[] = {
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xdd, 0xee, 0xff
    };

    uint8_t out[16]; // 128

    uint8_t *w; // expanded key

    switch (sizeof (key)) {
        case 16: 
            Nk = 4;
            Nr = 10;
            break;
        case 24: 
            Nk = 6;
            Nr = 12;
            break;
        case 32: 
            Nk = 8;
            Nr = 14;
            break;
        default:
            printf("Can't recongnize your password size.");
            break;//__nop__();
    }

    w = malloc(Nb * (Nr + 1)*4);

    key_expansion(key, w);

    cipher(in /* in */, out /* out */, w /* expanded key */);

    printf("out:\n");

    for (i = 0; i < 4; i++) {
        printf("%x %x %x %x ", out[4 * i + 0], out[4 * i + 1], out[4 * i + 2], out[4 * i + 3]);
    }

    printf("\n");

    inv_cipher(out, in, w);

    printf("msg:\n");
    for (i = 0; i < 4; i++) {
        printf("%x %x %x %x ", in[4 * i + 0], in[4 * i + 1], in[4 * i + 2], in[4 * i + 3]);
    }

    printf("\n");

    exit(0);

}