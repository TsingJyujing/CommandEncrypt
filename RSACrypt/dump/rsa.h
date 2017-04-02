#ifndef	RSA_H
#define RSA_H

#define MRSA_C

#ifndef	uint8
typedef unsigned char uint8;
#endif

#ifndef	uint16	
typedef unsigned short uint16;
#endif

#ifndef	uint32
typedef unsigned int uint32;
#endif

#ifndef	uint64
typedef unsigned long uint64;
#endif

#ifndef	int8
typedef signed char int8;
#endif

#ifndef	int16	
typedef signed short int16;
#endif

#ifndef	int32
typedef signed int int32;
#endif

#ifndef	int64
typedef signed long int64;
#endif

#define UNIT_BITS 16	/* unit bits */
#define PASSWORD_BYTES 128

#if !defined(RSA_ONLY) || defined(MRSA_C)
#if UNIT_BITS==8 // If mcu/pc is 16bit machine
#define UNIT_TYPE uint8
#define SIGN_BIT (1<<7)	/* top bit of unit */
#ifndef BIG_INTEGER_SIZE
#define BIG_INTEGER_SIZE PASSWORD_BYTES*2
#endif
#elif UNIT_BITS==16 // If mcu/pc is 32bit machine and above
#define UNIT_TYPE uint16
#define SIGN_BIT (1<<15)	/* top bit of unit */
#ifndef BIG_INTEGER_SIZE
#define BIG_INTEGER_SIZE PASSWORD_BYTES
#endif
#else 
#error "Undefined integer type"
#endif
#define PRIMES 50		/* number of primes in prime table */



typedef UNIT_TYPE *extInteger;
typedef UNIT_TYPE  bigInteger[BIG_INTEGER_SIZE];

typedef struct rsa_key {
	uint32 b;
	bigInteger pq, e, d, p, q, dp, dq, qp;
} rsa_key;

#ifdef __cplusplus
extern "C" {
#endif

	int	ts(extInteger a);		/* test signed, returns -1, 0 or 1 */
	uint32	ng(extInteger a);		/* negate, return carry*/
	void	cl(extInteger a);		/* clear */
	void	cp(extInteger a, extInteger b);		/* copy, a = b */
	int	cu(extInteger a, extInteger b);		/* compare unsigned, returns, -1 0 or 1 */
	uint32	ad(extInteger a, extInteger b);		/* add, a += b */
	uint32	sb(extInteger a, extInteger b);		/* substract, a -= b */
	uint32	sr(extInteger a);		/* shift right, a >>= 1, return carry */
	uint32	sl(extInteger a);		/* shift left, a <<= 1, return carry */
	void	dm(extInteger a, extInteger b, extInteger c);	/* div-mod unsigned, a /= b, c = a % b */
	void	mu(extInteger a, extInteger b);		/* multiply unsigned, a *= b */
	void	mm(extInteger a, extInteger b, extInteger m);	/* modular multiply, a = a * b mod m */
	void	em(extInteger a, extInteger e, extInteger m);	/* modular exponentiation, a = a^e mod m */
	void	gd(extInteger a, extInteger b);		/* greatst common divisor, a = gcd(a,b) */
	void	iv(extInteger a, extInteger b);		/* multiplicative inverse, a = a^{-1} mod p */
	void	nh(char *a, extInteger b);	/* convert number to hex string */
	void	hn(extInteger a, char *b);	/* convert lowercase hex string to number */

#if	defined(AMIGA) && defined(MRSA_C)
	__stdargs pmm(extInteger aa, extInteger b, extInteger m, uint32 p); /* assembler modmul (SAS 6.2) */
#endif

#endif /* RSA_C */

	//void copyhash(extInteger a);
	uint32	sieve_prime(extInteger);
	int		prob_prime(extInteger);
	void	next_prime(extInteger);
	uint32 	rsa_gen(rsa_key *);
	void 	rsa_enc(extInteger, rsa_key *);
	void 	rsa_dec(extInteger, rsa_key *);
	uint32 	n_to_b(unsigned char *, extInteger);
	void 	b_to_n(extInteger, unsigned char *, uint32);
#ifdef __cplusplus
}
#endif
#endif /* MRSA_H */
