#ifndef _MD5_ALGORITHM_HEADFILE_
#define _MD5_ALGORITHM_HEADFILE_
/**
 * @file md5.h
 * @author 我也不知道，我整理了一下。
 * @function MD5散列算法
 */
#ifdef __cplusplus
extern "C" {
#endif

#define MD5_HASH_SIZE 16

/**
 * @function MD5散列算法
 * @param document 需要求散列的数据/文档
 * @param docSize 文档大小
 * @param digest 散列计算结果
 */
void MD5(unsigned char *document, unsigned int docSize, unsigned char digest[MD5_HASH_SIZE]);

#ifdef __cplusplus
}
#endif

#endif
