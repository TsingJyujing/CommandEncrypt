#ifndef	__HEX_UTILITY_H__
#define __HEX_UTILITY_H__
// HEXÓÍÌõ
typedef unsigned char * byteArray;
typedef unsigned char byte;
#ifdef __cplusplus
extern "C" {
#endif
	void loadHex(char * fileName, byteArray bytes, int arrayLen, int *readLen);
#ifdef __cplusplus
}
#endif
#endif