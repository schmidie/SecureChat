/* 
 * File:   Crypt.h
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/


#ifndef _CRYPT_H
#define	_CRYPT_H

#define _KEY_D 0
#define _KEY_N 1
#define _KEY_E 2

class Crypt {
public:
    Crypt();
    Crypt(const Crypt& orig);
    virtual ~Crypt();

    char * generatePrime(long numBit);
    int decrypt( char* c, char * m);
    int encrypt(char* m, char * c);
    void genKey();

private:
    int modInverse(int phi, int e);
    int key[3];

};

#endif	/* _CRYPT_H */

