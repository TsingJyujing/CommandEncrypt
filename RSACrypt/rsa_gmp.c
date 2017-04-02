#include "rsa_common.h"
#include "gmp.h"

#define ENDIAN 0
#define NAILS 0
#define ORDER 1

void bytes2bigInt(unsigned char buffer, size_t bufferSize, mpz_t bigInt){
    mpz_import(bigInt, bufferSize, ORDER, sizeof(buffer[0]), ENDIAN, NAILS, buffer);
}

