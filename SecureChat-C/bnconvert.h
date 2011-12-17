/* 
 * File:   convert.h
 * Author: develop
 *
 * Created on 16. Dezember 2011, 23:40
 */

#include <openssl/bn.h>
#include <arpa/inet.h>

#ifndef _BNCONVERT_H
#define	_BNCONVERT_H


unsigned char * bn_to_char(BIGNUM * bignum);
uint32_t bn_get_size_bigendian(BIGNUM * bignum);
int bn_get_size(BIGNUM *bignum);
BIGNUM * char_to_bn(unsigned char * number,int size );

#endif	/* _CONVERT_H */

