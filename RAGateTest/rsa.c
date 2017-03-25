#include "rsa.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

signed char R[DATALENGTH], PK[DATALENGTH], RsaKey[DATALENGTH];
signed char SK[DATALENGTH];
unsigned char DesKey[9];
byteint R, SK, PK, RsaKey;
mtype Model[TESTNUM];
byteint ONEVALUE, ZEROVALUE, TWOVALUE, EIGHTVALUE;

int ShoutBlockingHook(void){
	return 0;
}

int RsaPrepare(byteint sk, byteint pk, byteint r){
	byteint p, q, Rvalue, buf1, buf2;
	Mdata();
	InitInt();
	Prime(p);
	Prime(q);
	Multiply(p, q, r);
	Substract(p, ONEVALUE, buf1);
	Substract(q, ONEVALUE, buf2);
	Multiply(buf1, buf2, Rvalue);
	ComputingPK(Rvalue, sk, pk);
	return TRUE;
}

int ReadRsaFile(byteint r, byteint pk, byteint sk) 
{
	char file[80], temp[100 + 1];

	sprintf(file, "%s/rsa.dat", szDataPath);
	printf("FILE READING:%s\n", file);
	if (GetPrivateProfileString("RSA", "R", "", temp, 100, (LPCWSTR)file) != 0)
		StrToByt(temp, r);
	else
		return FALSE;
	if (GetPrivateProfileString("RSA", "PK", "", temp, 100, (LPCWSTR)file) != 0)
		StrToByt(temp, pk);
	else
		return FALSE;
	if (GetPrivateProfileString("RSA", "SK", "", temp, 100, (LPCWSTR)file) != 0)
		StrToByt(temp, sk);
	else
		return FALSE;

	return TRUE;
}

int WriteRsaFile(byteint r, byteint pk, byteint sk)
{
	char file[80], temp[100 + 1];
	sprintf(file, "%s/rsa.dat", szDataPath);
	printf("FILE WRITING:%s\n", file);
	memset(temp, 0, 100 + 1);
	BytToStr(r, temp);
	if (WritePrivateProfileString("RSA", "R", temp, (LPCWSTR)file) == 0)
		return FALSE;
	memset(temp, 0, 100 + 1);
	BytToStr(pk, temp);
	if (WritePrivateProfileString("RSA", "PK", temp, (LPCWSTR)file) == 0)
		return FALSE;
	memset(temp, 0, 100 + 1);
	BytToStr(sk, temp);
	if (WritePrivateProfileString("RSA", "SK", temp, (LPCWSTR)file) == 0)
		return FALSE;

	return TRUE;
}


int DecipherDesKey(byteint rsakey, byteint r, byteint sk, char *deskey)
{
	byteint buf1;
	signed char flag[400];
	Mdata();
	InitInt();
	TransBi(sk, flag);
	PowerMode(rsakey, r, buf1, flag);
	BytToStr(buf1, deskey);
	return 0;
}

void InitInt(void)
{
	SetZero(ONEVALUE);
	ONEVALUE[DATALENGTH - 1] = 1;
	SetZero(ZEROVALUE);
	SetZero(TWOVALUE);
	TWOVALUE[DATALENGTH - 1] = 2;
	SetZero(EIGHTVALUE);
	EIGHTVALUE[DATALENGTH - 1] = 8;
	//randomize();
	srand((unsigned)time(NULL));
}

void Multiply(byteint A, byteint B, byteint C)
{
	register i, j, w;
	int X, Y, Z;
	int Avalid = 0;
	int Bvalid = 0;
	while (A[Avalid] == 0 && Avalid <DATALENGTH)
		Avalid++;
	while (B[Bvalid] == 0 && Bvalid <DATALENGTH)
		Bvalid++;
	SetZero(C);
	for (i = DATALENGTH - 1; i >= Avalid; i--)
	{
		for (j = DATALENGTH - 1; j >= Bvalid; j--)
		{
			X = A[i] * B[j];
			Y = X / 10;
			Z = X - 10 * Y;
			w = i + j - (DATALENGTH - 1);
			C[w] = C[w] + Z;
			C[w - 1] = C[w - 1] + (C[w] / 10) + Y;
			C[w] = C[w] - (C[w] / 10) * 10;
		}
	}
}

void SetZero(byteint A)
{
	memset(A, 0, DATALENGTH);
}

void IntCpy(byteint A, byteint B)
{
	memcpy(A, B, DATALENGTH);
}

void Plus(byteint A, byteint B, byteint C)
{
	register i;
	int X, Y, Z, m, n, valid;

	m = IntValid(A);
	n = IntValid(B);
	valid = (m>n) ? m + 1 : n + 1;
	SetZero(C);
	for (i = DATALENGTH - 1; i >= DATALENGTH - valid; i--)
	{
		X = A[i] + B[i];
		Y = X / 10;
		Z = X - 10 * Y;

		C[i] = C[i] + Z;
		C[i - 1] = C[i - 1] + Y;
	}
}

void Substract(byteint SA, byteint SB, byteint SC)
{
	byteint buf;
	register i, j;
	int X;

	IntCpy(buf, SA);
	SetZero(SC);

	for (i = DATALENGTH - 1; i >= 0; i--)
	{
		if (buf[i]<SB[i]){
			buf[i] += 10;
			if (buf[i - 1]>0)
				(buf[i - 1])--;
			else {
				j = i - 1;
				while (buf[j] == 0)
					buf[j--] = 9;
				buf[j]--;
			}
		}
		X = buf[i] - SB[i];
		SC[i] = X;
	}
}

int IntCmp(byteint A, byteint B)
{
	int stat;

	stat = memcmp(A, B, DATALENGTH);
	if (stat == 0)
		return 0;
	if (stat>0)
		return 1;
	return -1;
}

int IntValid(byteint validtemp)
{
	register i = 0;
	while (validtemp[i] == 0 && i<DATALENGTH)
		i++;
	return DATALENGTH - i;
}

void SetMode(byteint A, byteint B, byteint C, byteint D)
{
	register i, j, k;

	int valid_1, valid_2, valid, sbits, cmpval;
	byteint buf1, buf2;

	SetZero(D);
	IntCpy(C, A);
	valid_2 = IntValid(B);
	while ((cmpval = IntCmp(C, B))>0){
		valid_1 = IntValid(C);
		valid = valid_1 - valid_2;
		if (valid>0){
			i = DATALENGTH - valid_1;
			j = DATALENGTH - valid_2;
			sbits = 0;
			for (k = j; k<DATALENGTH; k++){
				if (C[i]>B[j])
					break;
				if (C[i]<B[j]){
					sbits = 1;
					break;
				}
				i++; j++;
			}
			valid = valid - sbits;
			SetZero(buf1);
			for (i = valid; i<DATALENGTH; i++){
				j = i - valid;
				buf1[j] = B[i];
			}
		}
		else
			IntCpy(buf1, B);

		D[DATALENGTH - 1 - valid]++;
		Substract(C, buf1, buf2);
		IntCpy(C, buf2);
	}

	if (cmpval == 0){
		SetZero(C);
		D[DATALENGTH - 1]++;
	}
}

void IntRandom(byteint RandomA, int num)
{
	int i;
	SetZero(RandomA);
	while (!(RandomA[DATALENGTH - 1] % 2))
		RandomA[DATALENGTH - 1] = rand() % 10;

	while (!RandomA[DATALENGTH - num])
		RandomA[DATALENGTH - num] = rand() % 10;

	i = DATALENGTH - 2;
	while (i >= DATALENGTH - num + 1)
		RandomA[i--] = rand() % 10;
}

void LoadInt(byteint A, mtype B)
{
	register i, j;

	SetZero(A);
	i = DATALENGTH - 1;
	j = MLENGTH - 1;
	while (j >= 0)
		A[i--] = B[j--];
}

void Mdata(void)
{
	register i, j;

	int k = MLENGTH - 2;
	memset(Model, 0, TESTNUM*MLENGTH);
	for (i = 0; i<TESTNUM; i++){
		for (j = MLENGTH - 1; j >= k; j--)
			Model[i][j] = rand() % 10;
		k -= 1;
	}
}

void TransBi(byteint B, signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp;
	register i;

	memset(flag, 0, 400);
	i = 399;
	IntCpy(buf, B);
	while (IntCmp(buf, ZEROVALUE) == 1){
		ShoutBlockingHook();
		SetMode(buf, TWOVALUE, temp, result);
		flag[i] = temp[DATALENGTH - 1];
		IntCpy(buf, result);
		i--;
	}
	flag[i] = -1;
}

int PowerMode(byteint A, byteint C, byteint D, signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp, P;
	register i;

	IntCpy(temp, A);
	if (flag[399] == 1)
		IntCpy(result, A);
	else
		IntCpy(result, ONEVALUE);
	i = 398;
	while (flag[i] != -1){
		ShoutBlockingHook();
		Multiply(temp, temp, buf);
		SetMode(buf, C, temp, P);
		if (flag[i] != 0){
			Multiply(temp, result, buf);
			SetMode(buf, C, result, P);
		}
		i--;
	}
	IntCpy(buf, C);
	IntCpy(D, result);
	Substract(buf, ONEVALUE, temp);
	if (IntCmp(result, ONEVALUE) == 0)
		return 1;
	if (IntCmp(result, temp) == 0)
		return 2;
	return 0;
}

int Prime(byteint Prm)
{
	int i, k, ok, cnt = 0;
	signed char flag[400];
	byteint A, B, D, buf1, buf2;
	int pass = 0, pass_2 = 0;
	while (1){
		ShoutBlockingHook();
		cnt++;
		IntRandom(B, MLENGTH);
		IntCpy(Prm, B);
		Substract(B, ONEVALUE, buf1);
		SetMode(buf1, TWOVALUE, buf2, B);
		TransBi(B, flag);
		ok = 1;
		for (i = 0; i<TESTNUM; i++){
			LoadInt(A, Model[i]);
			k = PowerMode(A, Prm, D, flag);
			if (k != 1 && k != 2)
				break;
			if (k == 2){
				pass_2 = 1;
			}
		}
		if (ok && pass_2){
			return 0;
		}
	}
}

int ComputingPK(byteint Rvalue, byteint SK, byteint PK)
{
	register i;
	byteint PA, PB, PC, buf, temp, buf2;
	SetZero(PK);
	while (1)
	{
		IntRandom(SK, SKLENGTH);
		IntCpy(PB, SK);
		IntCpy(PA, Rvalue);
		while (1) {
			ShoutBlockingHook();
			SetMode(PA, PB, PC, PK);
			i = IntCmp(PC, ONEVALUE);
			if (i == 0)
				break;
			i = IntCmp(PC, ZEROVALUE);
			if (i == 0){
				i = -1;
				break;
			}
			IntCpy(PA, PB);
			IntCpy(PB, PC);
		}
		if (i == 0)
			break;
	}
	IntCpy(temp, ONEVALUE);
	IntCpy(PA, Rvalue);
	IntCpy(PB, SK);

	while (1){
		Multiply(PA, temp, buf);
		Plus(buf, ONEVALUE, buf2);
		SetMode(buf2, PB, buf, PK);
		if (IntCmp(buf, ZEROVALUE) == 0)
			break;
		Plus(temp, ONEVALUE, buf);
		IntCpy(temp, buf);
	}
	return 1;
}

void PackInt(byteint A, int B)
{
	register i = DATALENGTH - 1;

	SetZero(A);
	while (B>0){
		A[i--] = B % 10;
		B = B / 10;
	}
}

int StrToByt(char *str, byteint byt)
{
	unsigned int m;
	SetZero(byt);
	for (m = 0; m<strlen(str); m++)
		byt[DATALENGTH - 1 - m] = str[strlen(str) - m - 1] - '0';
	return 1;
}

void BytToStr(byteint byt, char *str)
{
	unsigned  int i = 0, j = 0;
	while (i<DATALENGTH&&byt[i] == 0) i++;
	for (; i<DATALENGTH; i++, j++)
	{
		str[j] = byt[i] + '0';
	}
}
