/*
 * File:   Crypto.h
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/


#ifndef _CRYPTO_H
#define	_CRYPTO_H

#define _KEY_LENGTH 1024
#define _KEY_D 0
#define _KEY_N 1
#define _KEY_E 2

void Crypt();

int decrypt(char* c, char* m);
int encrypt(char* m, char* c);
void genKey();
int getDecryptedSize(char *c);
int getEncryptedSize(char *m);
char* padding(int ascii);

char * generatePrime(int numBit);
int modInverse(int phi, int e);
char* key[3];


#endif	/* _CRYPTO_H */

