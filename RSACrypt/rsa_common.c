#include "rsa_common.h"
#include <string.h>
#include <stdlib.h>

void deleteByteBuffer(bytesBuffer *bf) {
    free(bf->data);
    bf->size = 0;
}

void newByteBuffer(bytesBuffer *bf, unsigned char *data, unsigned int dataSize) {
    bf->data = NULL_PTR;
    bf->data = (unsigned char *) malloc(dataSize * sizeof (unsigned char));
    if (bf->data != NULL_PTR) {
        bf->size = dataSize;
        memcpy(bf->data, data, dataSize);
    }
}

