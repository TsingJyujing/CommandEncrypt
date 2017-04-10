#include "hex_utility.h"
#include <stdio.h>

//判断是否HexChar（[0..9 a..f A..F]），大小写不敏感，私有函数
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

void loadHex(char * fileName, unsigned char * bytes, unsigned int arrayLen, unsigned int *readLen){
	FILE *fp = fopen(fileName, "r");
    int nowRead;
	unsigned char byteFixed = 0;
    
	if (fp == NULL){
		printf("Failed to open file %s.\n", fileName);
		return;
	}
    
	nowRead = fgetc(fp);
    
	*readLen = 0;
	bytes[*readLen] = 0;
	while (nowRead != EOF){
		signed char hexVal = isHexChar(nowRead);
		if (*readLen >= arrayLen){
			break; 
		}
		if (hexVal >= 0 && hexVal <= 15){
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
    int i;
	printf("\nOFFSET: ");
	for (i = 0; i < len; ++i){
		printf("%02X ", i);
	}
	printf("\nDATA:   ");
	for (i = 0; i < len; ++i){
		printf("%02X ", bytearray[i]);
	}
	printf("\n\n");
}

void printByteArrayFixWidth(unsigned char *bytearray, unsigned int len, unsigned int lineChange){
    unsigned int i = 0, j = 0;
    unsigned int printLines;
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
    printLines = (len-1)/lineChange + 1;
    for (i = 0; i<printLines; ++i){
        int indexStart = i*lineChange;
        int indexEnd = ((i+1)*lineChange<len)?(i+1)*lineChange:len;
        printf("%03X ", i);
        for (j = indexStart; j<indexEnd; j++) {
            printf("%02X ", bytearray[j]);
        }
        printf("\n");
    }
}

void printByteArrayComment(
    unsigned char *bytearray, 
    unsigned int len, 
    unsigned int lineChange, 
    char *comment
    ){
    printf("\n%s\n", comment);
    printByteArrayFixWidth(bytearray, len, lineChange);
}

