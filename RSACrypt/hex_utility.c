#include "hex_utility.h"
#include <stdio.h>

signed char isHexChar(unsigned char inChar){
	if (inChar >= 'a' && inChar <= 'f') {
		inChar -= 'a';
		inChar += 'A';
	}
	if ((inChar >= '0' && inChar <= '9') || (inChar >= 'A' && inChar <= 'F')){
		if ((inChar >= 'A' && inChar <= 'F')) {
			inChar -= 'A';
			inChar += 10;
		}
		else{
			inChar -= '0';
		}
		return inChar;
	}
	else{
		return -1;
	}
}

void loadHex(char * fileName, unsigned char * bytes, int arrayLen, int *readLen){
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL){
		printf("Failed to open file %s.\n", fileName);
		return;
	}
	int nowRead = fgetc(fp);
	unsigned char byteFixed = 0;
	*readLen = 0;
	bytes[*readLen] = 0;
	while (nowRead != EOF){
		char hexVal = isHexChar(nowRead);
		if (*readLen >= arrayLen){
			break; 
		}
		if (hexVal >= 0x0 && hexVal <= 0xF){
			bytes[*readLen] = (bytes[*readLen] << 4) | hexVal;
			byteFixed = 1;
		}
		else{// Not hex chars
			if (byteFixed == 1){
				(*readLen)++;
			}
			byteFixed = 0;
		}
		nowRead = fgetc(fp);
	}
	if (byteFixed == 1) {
		(*readLen)++;
	}
}

void printByteArray(unsigned char *bytearray, unsigned int len) {
	printf("OFFSET: ");
	for (int i = 0; i < len; ++i){
		printf("%02X ", i);
	}
	printf("\nDATA:   ");
	for (int i = 0; i < len; ++i){
		printf("%02X ", bytearray[i]);
	}
	printf("\n\n");
}

void printByteArrayFixWidth(unsigned char *bytearray, unsigned int len, unsigned int lineChange){
    unsigned int i = 0;
    printf("    ");
    if (len < lineChange) {
        for(i = 0; i<len; ++i) {
            printf("%02X ", i);
        }
    }else{
        for( i = 0; i<lineChange; ++i) {
            printf("%02X ", i);
        }
    }
    printf("\n");
    unsigned int printLines = (len-1)/lineChange + 1;
    for (i = 0; i<printLines; ++i){
        int indexStart = i*lineChange;
        int indexEnd = ((i+1)*lineChange<len)?(i+1)*lineChange:len;
        printf("%03X ", i);
        for (int j = indexStart; j<indexEnd; j++) {
            printf("%02X ", bytearray[j]);
        }
        printf("\n");
    }
}