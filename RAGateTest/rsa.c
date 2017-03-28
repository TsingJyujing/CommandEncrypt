#define RSA_C 1

#include "rsa.h"

/*
* math library stuff
*/

/*
* sign = ts(extInteger a) -- test signed, returns 1, 0 or -1
*/
int ts(extInteger a)
{
	uint32 i = BIG_INTEGER_SIZE;
	if (a[BIG_INTEGER_SIZE - 1] & SIGN_BIT)
		return -1;
	while (i--)
		if (*a++)
			return 1;
	return 0;
}

/*
* carry = ng(extInteger a) -- negate, returns carry
*/
uint32 ng(extInteger a)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	while (i--) {
		c = 0 - *a - c;
		*a++ = c;
		c = (c >> UNIT_BITS) & 1;
	} return c;
}

/*
* cl(extInteger a) -- clear value, a = 0
*/
void cl(extInteger a)
{
	uint32 i = 0;
	while (i++ < BIG_INTEGER_SIZE)
		*a++ = 0;
}

/*
* cp(extInteger a, extInteger b) -- copy, a = b
*/
void cp(extInteger a, extInteger b)
{
	uint32 i = BIG_INTEGER_SIZE;
	while (i--)
		*a++ = *b++;
}

/*
* flag = cu(a, b) -- compare unsigned, returns <0 if a<b, 0 if a==b, >0 if a>b
*/
int cu(extInteger a, extInteger b)
{
	uint32 i = BIG_INTEGER_SIZE;
	a += BIG_INTEGER_SIZE;
	b += BIG_INTEGER_SIZE;
	while (i--)
		if (*--a - *--b)
			return (int)*a - (int)*b;
	return 0;
}

/*
* carry = ad(extInteger a, extInteger b) -- add, a += b
*/
uint32 ad(extInteger a, extInteger b)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	while (i--) {
		c = *b++ + *a + c;
		*a++ = c;
		c >>= UNIT_BITS;
	}
	return c;
}

/*
* carry = sb(extInteger a, extInteger b) -- substract, a -= b
*/

uint32 sb(extInteger a, extInteger b)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	while (i--) {
		c = *a - *b++ - c;
		*a++ = c;
		c = (c >> UNIT_BITS) & 1;
	}
	return c;
}

/*
* carry = sr(extInteger a) -- shift right, a >>= 1
*/

uint32 sr(extInteger a)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	a += BIG_INTEGER_SIZE;
	while (i--) {
		c |= *--a;
		*a = c >> 1;
		c = (c & 1) << UNIT_BITS;
	}
	return c;
}

/*
* carry = sl(extInteger a) -- shift left, a <<= 1
*/

uint32 sl(extInteger a)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	while (i--) {
		c |= (uint32)* a << 1;
		*a++ = c;
		c = (c >> UNIT_BITS) & 1;
	}
	return c;
}

/*
* dm(extInteger a, extInteger b, extInteger c) -- divide-modulo unsigned, a = a / b, c = a % b
*/

void dm(extInteger a, extInteger b, extInteger c)
{
	uint32 i = BIG_INTEGER_SIZE * UNIT_BITS;
	cl(c);
	while (i--) {
		sl(c);
		*c |= sl(a);
		if (sb(c, b)) {
			ad(c, b);
		}
		else {
			*a |= 1;
		}
	}
}

/*
* remainder = di(extInteger a, int n) -- divide by integer
*/

uint32 di(extInteger a, uint32 t)
{
	uint32 c = 0, i = BIG_INTEGER_SIZE;
	while (i--) {
		c = (c << UNIT_BITS) | a[i];
		a[i] = c / t;
		c = c % t;
	}
	return c;
}

/*
* mu(extInteger a, extInteger b) -- multiply unsigned, a *= b
*/

void mu(extInteger a, extInteger b)
{
	uint32 i = BIG_INTEGER_SIZE * UNIT_BITS;
	bigInteger c;
	cl(c);
	while (i--) {
		sl(c);
		if (sl(a))
			ad(c, b);
	}
	cp(a, c);
}

/*
* mm(extInteger a, extInteger b, extInteger m) -- modular multiply, a = a * b mod m
*/

void mm(extInteger a, extInteger b, extInteger m)
{
	uint32 i = BIG_INTEGER_SIZE * UNIT_BITS;
	bigInteger c;
	cl(c);
	while (i--) {
		sl(c);
		if (sb(c, m))
			ad(c, m);
		if (sl(a))
			ad(c, b);
		if (sb(c, m))
			ad(c, m);
	}
	cp(a, c);
}

/*
* pmm(extInteger a, extInteger b, extInteger m, uint32 p) -- internal modmul w/precision for modexp
*/

#ifndef AMIGA
void pmm(extInteger aa, extInteger b, extInteger m, uint32 p) {
	uint32 k, c, j = UNIT_BITS, i;
	bigInteger v;
	extInteger a;
	i = p;
	cl(v);
	a = aa + p;
	while (!*--a
		&& i)
		i--;
	if (i) {
		while (!(*a & (1 << j)) && j)
			j--;
		cp(v, b);
	} while (i--) {
		while (j--) {
			for (k = 0, c = 0; k < p; k++) {
				c |= (uint32)v[k] << 1;
				v
					[k] = c;
				c >>= UNIT_BITS;
			} for (k = 0, c = 0; k < p; k++) {
				c = v[k] - m[k] - c;
				v[k] = c;
				c = (c >> UNIT_BITS) & 1;
			} if (c)
				for (k = 0, c = 0; k < p; k++) {
				c = v[k] + m[k] + c;
				v[k] = c;
				c >>= UNIT_BITS;
				} if (*a & (1 << j)) {
				for (k = 0, c = 0; k < p; k++) {
					c = v[k] + b[k] + c;
					v[k] = c;
					c >>= UNIT_BITS;
				} for (k = 0, c = 0; k < p; k++) {
					c = v[k] - m[k] - c;
					v[k] = c;
					c = (c >> UNIT_BITS) & 1;
				} if (c)
					for (k = 0, c = 0; k < p; k++) {
					c = v[k] + m[k] + c;
					v[k] = c;
					c >>= UNIT_BITS;
					}
				}
		}
		a--;
		j = UNIT_BITS;
	}
	cp(aa, v);
}

#endif

/*
* em(extInteger a, extInteger b, extInteger m) -- modular exponentation, a = a^b mod n
*/

void em(extInteger a, extInteger e, extInteger m)
{
	uint32 i = BIG_INTEGER_SIZE, j = UNIT_BITS, p = BIG_INTEGER_SIZE;
	bigInteger c;
	extInteger mp;
	cl(c);
	*c = 1;
	e += BIG_INTEGER_SIZE;
	while (!*--e && i)
		i--;
	if (i) {
		while (!(*e & (1 << j)))
			j--;
		cp(c, a);
	}
	mp = m + BIG_INTEGER_SIZE;
	while (!*--mp && p)
		p--;
	if (*mp & SIGN_BIT && p < BIG_INTEGER_SIZE)
		p++;
	while (i--) {
		while (j--) {
			pmm(c, c, m, p);
			if (*e & (1 << j))
				pmm(c, a, m, p);
		}
		e--;
		j = UNIT_BITS;
	}
	cp(a, c);
}

/*
* gd(extInteger a, extInteger b) -- a = greatest common divisor(a,b)
*/

void gd(extInteger a, extInteger bb)
{
	bigInteger r, b;
	cp(b, bb);
	while (ts(b)) {
		dm(a, b, r);
		cp(a, b);
		cp(b, r);
	}
}

/*
* iv(extInteger a, extInteger b) -- multiplicative inverse, a = a^{-1} mod b
*/

void iv(extInteger a, extInteger b)
{
	bigInteger c, d, e, f, g, y;
	cp(c, b);
	cl(e);
	cl(f);
	*f = 1;
	while (ts(a)) {
		cp(y, c);
		dm(y, a, d);
		if (f[BIG_INTEGER_SIZE - 1] & SIGN_BIT) {
			ng(f);
			mu(y, f);
			ng(f);
			ng(y);
		}
		else
			mu(y, f);
		cp(g, e);
		sb(g, y);
		cp(c, a);
		cp(a, d);
		cp(e, f);
		cp(f, g);
	}
	if (e[BIG_INTEGER_SIZE - 1] & SIGN_BIT)
		ad(e, b);
	cp(a, e);
}

/*
* nh(char *a, extInteger b) -- convert value to a hex string (use for debugging)
*/

void nh(char *a, extInteger b)
{
	char *d = "0123456789abcdef";
	bigInteger c;
	uint32 i = BIG_INTEGER_SIZE * sizeof(uint16) * 2; /* 2 digits/byte! */
	cp(c, b);
	a += BIG_INTEGER_SIZE * sizeof(uint16) * 2;
	*a = 0;
	while (i--) {
		*--a = d[*c & 15];
		sr(c);
		sr(c);
		sr(c);
		sr(c);
	}
}

/*
* hn(extInteger a, char *b) -- lower-case hex string to value (use for constants)
*/

void hn(extInteger a, char *b)
{
	cl(a);
	while (*b) {
		sl(a);
		sl(a);
		sl(a);
		sl(a);
		*a += *b < 'a' ? *b - '0' : *b - ('a' - 10);
		b++;
	}
}

/*
* prime generation and RSA stuff
*/
static short text[BIG_INTEGER_SIZE] = {
	12, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


static uint32 sp[PRIMES] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
	59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
	137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
	227, 229 };

/*
* divisor = sieve_prime(extInteger n) -- try to find divisor of n by sieving
* with small integers returns divisor or 0 if no divisor found.
*/

uint32 sieve_prime(extInteger n)
{
	uint32 i;
	bigInteger a;
	for (i = 0; i<PRIMES; i++) {
		cp(a, n);
		if (!di(a, sp[i]))
			return (sp[i]);
	}
	return (0);
}

/*
* flag = prob_prime(extInteger n) -- test if 2^(n-1) mod n == 1. Returns 0 if
* test failed, !0 if success. Large n which passes this test is a
* probable prime. This test does not work well with small value of n.
* Because this test is slow, you should first try sieving n.
*/

int prob_prime(extInteger m)
{
	uint32 i = BIG_INTEGER_SIZE, j = UNIT_BITS, p = BIG_INTEGER_SIZE;
	bigInteger c, ee;
	extInteger mp, e = ee + BIG_INTEGER_SIZE;
	cl(c);
	*c = 1;
	cp(ee, m);
	sb(ee, c);
	while (!*--e && i)
		i--;
	if (i) {
		while (!(*e & (1 << j)))
			j--;
		*c = 2;
	}
	mp = m + BIG_INTEGER_SIZE;
	while (!*--mp && p)
		p--;
	if (*mp & SIGN_BIT && p < BIG_INTEGER_SIZE)
		p++;
	while (i--) {
		while (j--) {
			pmm(c, c, m, p);
			if (*e & (1 << j)) {
				sl(c);
				if (sb(c, m)) ad(c, m);
			}
		}
		e--;
		j = UNIT_BITS;
	}
	cl(ee);
	*ee = 1;
	return (!cu(c, ee));
}

/*
* next_prime(extInteger a) -- find next probable prime >= a
*/

void next_prime(extInteger a)
{
	bigInteger b;
	*a |= 1;
	cl(b); *b = 2;
	for (;;) {
		if (!sieve_prime(a)) {
			if (prob_prime(a))
				return;
		}
		ad(a, b);
	}
}

/*
* bits rsa_gen(rsa_key *key) -- generate a RSA key from key->p and key->q
* Initialize key->p and key->q either with primes or strong random
* integers of apporopriate size. Returns number of bits in modulus key->pq
* or 0 if key generation failed.
*/

uint32 rsa_gen(rsa_key *k)
{
	bigInteger p1, q1, pq1, f, g, t;
	next_prime(k->p);
	next_prime(k->q);
	if (cu(k->p, k->q) < 0) {
		cp(t, k->p);
		cp(k->p, k->q);
		cp(k->q, t);
	}
	hn(t, "1");
	cp(p1, k->p);
	sb(p1, t);
	cp(q1, k->q);
	sb(q1, t);
	cp(g, p1);
	gd(g, q1);
	hn(t, "ff");//255
	if (cu(t, g) < 0)
		return 0;
	cp(k->pq, k->p);
	mu(k->pq, k->q);
	cp(pq1, p1);
	mu(pq1, q1);
	cp(f, pq1);
	dm(f, g, t);
	hn(k->e, "3");
	hn(k->qp, "1");
	cp(t, pq1);
	gd(t, k->e);
	if (cu(t, k->qp)) {
		hn(k->e, "10001");
		cp(t, pq1);
		gd(t, k->e);
		if (cu(t, k->qp))
			return 0;
	}
	cp(k->d, k->e);
	iv(k->d, f);
	cp(t, k->d);
	dm(t, p1, k->dp);
	cp(t, k->d);
	dm(t, q1, k->dq);
	cp(k->qp, k->q);
	iv(k->qp, k->p);
	cp(t, k->pq);
	for (k->b = 0; ts(t); sr(t), k->b++)
		; /* VOID */
	return (k->b);
}

/*
* rsa_dec(extInteger m, rsa_key *key) -- low level rsa decryption. Result undefined
* (ie. wrong) if key is not private rsa key.
*/

void rsa_dec(extInteger m, rsa_key * k)
{
	bigInteger mp, mq, t;
	cp(t, m);
	dm(t, k->p, mp);
	cp(t, m);
	dm(t, k->q,
		mq);
	em(mp, k->dp, k->p);
	em(mq, k->dq, k->q);
	if (sb(mp, mq))
		ad(mp, k->p);
	mm(mp, k->qp,
		k->p);
	mu(mp, k->q);
	ad(mp, mq);
	cp(m, mp);
}

/*
* rsa_enc(extInteger m, rsa_key *k) -- low level rsa encryption
*/

void rsa_enc(extInteger m, rsa_key * k)
{
	em(m, k->e, k->pq);
}

/*
* len = n_to_b(unsigned char *buf, extInteger a) -- convert a to bytes, most
* significant byte first. Returns number of bytes written to buf. buf
* should be large enough to hold sizeof(bigInteger) bytes. (Note that number
* is handled as unsigned, negative value converts to sizeof(bigInteger) bytes.)
* (XXX check portablility when converting to not-16/32 bit machine)
*/
uint32 n_to_b(unsigned char *b, extInteger a)
{
	uint32 i = BIG_INTEGER_SIZE - 1, l = 1;
	a += BIG_INTEGER_SIZE;
	while (!*--a && i)
		i--;
	if (*a > 255) {
		*b++ = *a >> 8;
		l++;
	}
	*b++ = *a;
	while (i--) {
		*b++ = *--a >> 8;
		*b++ = *a;
		l += 2;
	}
	return (l);
}

/*
* b_to_n(extInteger a, unsigned char *buf,uint32 len) -- convert len bytes from
* buf to value a. Conversion is unsigned, most significant byte first.
* (XXX check portablility when converting to not-16/32 bit machine)
*/

void b_to_n(extInteger a, unsigned char *b, uint32 l)
{
	uint32 i;
	if (l > BIG_INTEGER_SIZE * sizeof(uint16))
		l = BIG_INTEGER_SIZE * sizeof(uint16);
	b += l;
	cl(a);
	i = l / 2;
	while (i--) {
		*a = *--b;
		*a++ |= (uint32)*--b << 8;
	}
	if (l & 1)
		*a = *--b;
}

