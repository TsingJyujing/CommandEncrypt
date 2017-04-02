#ifndef _MD5_ALGORITHM_HEADFILE_
#define _MD5_ALGORITHM_HEADFILE_

#ifdef __cplusplus
extern "C" {
#endif

#define MD5_HASH_SIZE 16

/* MD5 context. */
typedef struct {
	unsigned int state[4]; /* state (ABCD) */
	unsigned int count[2]; /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64]; /* input buffer */
} MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen);
void MD5Final(unsigned char digest[MD5_HASH_SIZE], MD5_CTX *context);
void MD5(unsigned char *document, unsigned int docSize, unsigned char digest[MD5_HASH_SIZE]);

#ifdef __cplusplus
}
#endif

#endif
