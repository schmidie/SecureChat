
#include "bnconvert.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

unsigned char * bn_to_char(BIGNUM * bignum) {
    unsigned char * bignumchar=malloc(BN_num_bytes(bignum));
    BN_bn2bin(bignum,bignumchar);
    return bignumchar;
}

uint32_t bn_get_size_bigendian(BIGNUM * bignum) {
    int bytes=BN_num_bytes(bignum);
    return htonl(bytes);
}

int bn_get_size(BIGNUM *bignum) {
    return BN_num_bytes(bignum);
}

BIGNUM * char_to_bn(const unsigned char * number,int size ) {
    BIGNUM * bn=BN_new();
    BN_bin2bn(number,size,bn);
    return bn;
}