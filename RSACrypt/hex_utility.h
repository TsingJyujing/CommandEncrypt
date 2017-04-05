#ifndef	__HEX_UTILITY_H__
#define __HEX_UTILITY_H__

/**
 * @file hex_utility.h
 * @author 袁逸凡
 * @function 十六进制文件的输入和控制台的格式化输出工具集
 */
 
#ifdef __cplusplus
extern "C" {
#endif
	
	/**
     * @function 加载Hex文件
	 * @param fileName 文件名
	 * @param bytes 存取数据的数组
	 * @param arrayLen 数组的极限长度
	 * @param readLen 实际读取到的数据数量
	 */
	void loadHex(char * fileName, unsigned char * bytes, unsigned int arrayLen, unsigned int *readLen);
	
    /**
     * @function 输出ByteArray及其序号
     * @param bytearray byte数组
     * @param len byte数组大小
     */
    void printByteArray(unsigned char *bytearray, unsigned int len);
    
    /**
     * @function 输出ByteArray及其序号，并且按照输入参数lineChange折行
     * @param bytearray byte数组
     * @param len byte数组大小
     * @param lineChange 每一行显示的数据数量
     */
    void printByteArrayFixWidth(unsigned char *bytearray, unsigned int len, unsigned int lineChange);
    
    /**
     * @function 输出ByteArray及其序号，按照输入参数lineChange折行，并且在头部显示注释信息
     * @param bytearray byte数组
     * @param len byte数组大小
     * @param lineChange 每一行显示的数据数量
     * @param comment 需要显示在头部的注释
     */
    void printByteArrayComment(
        unsigned char *bytearray, 
        unsigned int len, 
        unsigned int lineChange, 
        char *comment
        );
#ifdef __cplusplus
}
#endif
#endif

