/*
 * File:   Crypto.h
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/
#include <openssl/bn.h>
#include <openssl/crypto.h>

#ifndef _CRYPTO_H
#define	_CRYPTO_H

#define _KEY_D 0
#define _KEY_N 1
#define _KEY_E 2

struct RSA {
 BIGNUM *n_bn;
 BIGNUM *e_bn;
 BIGNUM *d_bn;
};

int encrypt(unsigned char *message,int length,struct RSA* rsa,unsigned char **crypted);
int decrypt(unsigned char *crypted,int length,struct RSA* rsa,unsigned char **message);
void decryptBlock(const unsigned char* crypted,int length, unsigned char * message,struct RSA* rsa);
void encryptBlock(const unsigned char* message ,int length, unsigned char* crypted,struct RSA* rsa);
struct RSA * genKey();
char * generatePrime(int numBit);



#endif	/* _CRYPTO_H */

