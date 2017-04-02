#ifndef	__HEX_UTILITY_H__
#define __HEX_UTILITY_H__
// HEX油条
#ifdef __cplusplus
extern "C" {
#endif
	//加载HEX文件
	/**
	* @param fileName 文件名
	* @param bytes 存取数据的数组
	* @param arrayLen 数组的极限长度
	* @param readLen 实际读取到的数据数量
	*/
	void loadHex(char * fileName, unsigned char * bytes, int arrayLen, int *readLen);
        /*
         * @param bytearray byte数组
         * @param len byte数组大小
         */
        void printByteArray(unsigned char *bytearray, unsigned int len);
        void printByteArrayFixWidth(unsigned char *bytearray, unsigned int len, unsigned int lineChange);
#ifdef __cplusplus
}
#endif
#endif

