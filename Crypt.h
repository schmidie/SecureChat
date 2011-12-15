/* 
 * File:   Crypt.h
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/


#ifndef _CRYPT_H
#define	_CRYPT_H

#define _KEY_LENGTH 1024
#define _KEY_D 0
#define _KEY_N 1
#define _KEY_E 2

class Crypt {
public:
    Crypt();
    Crypt(const Crypt& orig);
    virtual ~Crypt();

    int decrypt( char* c, char* m);
    int encrypt(char* m, char* c);
    void genKey();

private:
    char * generatePrime(int numBit);
    int modInverse(int phi, int e);
    char* key[3];

};

#endif	/* _CRYPT_H */

