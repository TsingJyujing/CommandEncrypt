#include "cmd_encrypt.h"
#include "hex_utility.h"

#ifdef USE_GMP_LIBRARY
void byteBuffer2bigInteger(bytesBuffer bf, mpz_t bigInteger) {
    mpz_import(bigInteger, bf.size, ORDER, sizeof (bf.data[0]), ENDIAN, NAILS, bf.data);
}
#endif

RSAErrorType RSACryptBlock(
        RSAPassword RSAkey,
        byte rawPack[ENCRYPT_BLOCK_BYTE_SIZE],
        byte outputData[ENCRYPT_BLOCK_BYTE_SIZE]) {
        
#ifdef USE_GMP_LIBRARY
    mpz_t bImodulus;
    mpz_t bIkey;
    mpz_t dataRaw;
    mpz_t dataCrypted;

    mpz_init(bImodulus);
    mpz_init(bIkey);
    mpz_init(dataRaw);
    mpz_init(dataCrypted);

    byteBuffer2bigInteger(RSAkey.modulus, bImodulus);
    byteBuffer2bigInteger(RSAkey.key, bIkey);

    mpz_import(dataRaw, ENCRYPT_BLOCK_BYTE_SIZE, ORDER, sizeof (rawPack[0]), ENDIAN, NAILS, rawPack);
    mpz_powm(dataCrypted, dataRaw, bIkey, bImodulus);
    
    /*
     * These code used in debug mode only
     * printf("RAW = [%s]\n", mpz_get_str(NULL, 16, dataRaw));
     * printf("ENC = [%s]\n", mpz_get_str(NULL, 16, dataCrypted));
     */
    mpz_export(outputData, NULL, ORDER, SIZE_UNIT , ENDIAN, NAILS, dataCrypted);

#else
    // If can not compile min-gmp on you platform
    // contact yuanyifan@deewinfl.com to require a very slow but strong RSA algorithm
#endif
    return NO_ERROR;
}

RSAErrorType RSAEncrypt(
        RSAPassword key,
        byteArray rawData, unsigned char dataSize,
        byte outputData[ENCRYPT_BLOCK_BYTE_SIZE]) {

    byte buffer[ENCRYPT_BLOCK_BYTE_SIZE] = {0};
    unsigned int i = 0;
    
    //加密数据不得超过MAX_ENCRYPT_SIZE，暂时不支持分块儿加密
    if (dataSize > MAX_ENCRYPT_SIZE) {
        return TO_MUCH_DATA;
    }

    //开头第1个字节写入Size
    buffer[0] = dataSize;

    //第2个字节写入校验值
    buffer[1] = 0x00;
    for (i = 0; i < dataSize; i++) {
        buffer[1] ^= rawData[i];
        buffer[4 + i] = rawData[i];
    }

    //第3、4字节为随机盐，防止选择密文攻击
    buffer[2] = rand() & 0xff;
    buffer[3] = rand() & 0xff;

    //倒数1,2为0，防止“溢出”
    buffer[ENCRYPT_BLOCK_BYTE_SIZE - 1] = 0x00;
    buffer[ENCRYPT_BLOCK_BYTE_SIZE - 2] = 0x00;
    //倒数3,4为随机盐，防止选择密文攻击
    buffer[ENCRYPT_BLOCK_BYTE_SIZE - 3] = rand() & 0xff;
    buffer[ENCRYPT_BLOCK_BYTE_SIZE - 4] = rand() & 0xff;

    return RSACryptBlock(key, buffer, outputData);

}

RSAErrorType RSADecrypt(
        RSAPassword key,
        byte encryptedData[ENCRYPT_BLOCK_BYTE_SIZE],
        byteArray outputData, unsigned char * outDataSize) {

    byte buffer[ENCRYPT_BLOCK_BYTE_SIZE] = {0};
    RSAErrorType decResult = RSACryptBlock(key, encryptedData, buffer);
    //Verify
    unsigned char verifyFailed = 0x00;
    unsigned char dataSize = buffer[0];
    unsigned short i = 0;
    unsigned char xorVerify = 0x00;
    
    if (decResult != NO_ERROR) {
        return decResult;
    }
    
    verifyFailed = ASSERT_OR(buffer[ENCRYPT_BLOCK_BYTE_SIZE - 1] == 0x00, verifyFailed);
    verifyFailed = ASSERT_OR(buffer[ENCRYPT_BLOCK_BYTE_SIZE - 2] == 0x00, verifyFailed);
    verifyFailed = ASSERT_OR(dataSize <= MAX_ENCRYPT_SIZE, verifyFailed);

    for (i = 0; i < dataSize; i++) {
        xorVerify ^= buffer[i + 4];
    }
    verifyFailed = ASSERT_OR(xorVerify == buffer[1], verifyFailed);
    if (verifyFailed) {
        return VERIFY_FAILED;
    }
    outDataSize[0] = dataSize;
    for (i = 0; i < dataSize; i++) {
        outputData[i] = buffer[i + 4];
    }
    return NO_ERROR;
}

RSAErrorType digitalFingerPrintGenerate(
        byteArray document, unsigned int docSize,
        RSAPassword privateKey,
        byteArray fingerPrint
        ) {
    byte Digest[MD5_HASH_SIZE] = {0};
    //求文档HASH
    MD5(document, docSize, Digest);
    //反馈签名结果
    return RSAEncrypt(
            privateKey,
            Digest, MD5_HASH_SIZE,
            fingerPrint);
}

RSAErrorType digitalFingerPrintCheck(
        byteArray document, unsigned int docSize,
        RSAPassword publicKey,
        byteArray fingerPrint
        ) {
    byte Digest[MD5_HASH_SIZE] = {0};
    byte DigestDecrypt[MD5_HASH_SIZE] = {0};
    RSAErrorType decryptResult;
    int memcmpResult = 0x00;
    unsigned char decryptSize;
    
    //求Hash
    MD5(document, docSize, Digest);
    //解密获得它的Hash
    decryptResult = RSADecrypt(
            publicKey,
            fingerPrint,
            DigestDecrypt, &decryptSize);
    if (decryptResult != NO_ERROR || decryptSize != MD5_HASH_SIZE) {
        return VERIFY_FAILED;//校验失败
    } else {
        memcmpResult = memcmp(DigestDecrypt, Digest, MD5_HASH_SIZE);
        return memcmpResult == 0 ? NO_ERROR : VERIFY_FAILED;
    }
}
