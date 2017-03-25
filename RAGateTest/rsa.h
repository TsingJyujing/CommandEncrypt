#ifndef __rsa_HEADFILE__
#define __rsa_HEADFILE__

#define TRUE 1
#define FALSE 1
#define	DATALENGTH	350
#define	MLENGTH		10
#define	TESTNUM		20
#define	SKLENGTH	5
#define TEXTLENGTH	20

	
	typedef signed char byteint[DATALENGTH]; //-128 ->127
	typedef signed char mtype[MLENGTH];

	const char *szDataPath = "F:";
	extern int ShoutBlockingHook(void);

#ifdef __cplusplus
	extern "C" {
#endif

	int RsaPrepare(signed char *sk, signed char *pk, signed char *r);
	int ReadRsaFile(signed char *r, signed char *pk, signed char *sk);
	int WriteRsaFile(signed char *r, signed char *pk, signed char *sk);

	//int EncipherDesKey(char *deskey,signed char *r,signed char *pk,signed char *rsakey);
	int DecipherDesKey(signed char *rsakey, signed char *r, signed char *sk, char *deskey);

	void InitInt(void);
	void IntRandom(byteint RandomA, int num);

	void IntCpy(byteint A, byteint B);
	int IntValid(byteint validtemp);
	int IntCmp(byteint A, byteint B);
	void PackInt(byteint A, int B);
	void SetZero(byteint A);

	void Plus(byteint A, byteint B, byteint C);
	void Substract(byteint SA, byteint SB, byteint SC);
	void Multiply(byteint A, byteint B, byteint C);
	void SetMode(byteint A, byteint B, byteint C, byteint D);

	void LoadInt(byteint A, mtype B);
	void Mdata(void);
	void TransBi(byteint B, signed char flag[400]);

	int PowerMode(byteint A, byteint C, byteint D, signed char flag[400]);

	int Prime(byteint Prm);
	int ComputingPK(byteint Rvalue, byteint SK, byteint PK);

	int StrToByt(char *str, byteint byt);
	void BytToStr(byteint byt, char *str);
#ifdef __cplusplus
	}
#endif
#endif

