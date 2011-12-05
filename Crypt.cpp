/* 
 * File:   Crypt.cpp
 * Author: develop
 * 
 * Created on 21. November 2011, 20:00
*/

#include "Crypt.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <openssl/bn.h>
#include <openssl/crypto.h>
#include <math.h>
#include <sstream>


Crypt::Crypt()
{

}

Crypt::Crypt(const Crypt& orig)
{

}

Crypt::~Crypt()
{

}

int Crypt::decrypt(char* _c, char * _m)
{

     std::string c(_c);
    int priv_key[3];

    // get key from database
    priv_key[_KEY_D] = key[_KEY_D];
    priv_key[_KEY_N] = key[_KEY_N];

    const int digits = ((int)log10(key[_KEY_N]))+1;
    const int blocks = ceil(sizeof(c)/digits);

    //int c[blocks];

    char c_tmp[digits];
    int c_tmp_i = 0;

    for(int i=0; i < blocks; i++){

        c.copy(c_tmp,digits,(i*blocks));
        sscanf(c_tmp, "%d" , &c_tmp_i);
        _m[i] = (int)pow(c_tmp_i,priv_key[_KEY_D]) % priv_key[_KEY_N];

    }

    return 1;

}
int Crypt::encrypt(char* _m ,char * _c)
{
    std::string m(_m);
    int pub_key[3];

    // get key from database
    pub_key[_KEY_E] = key[_KEY_E];
    pub_key[_KEY_N] = key[_KEY_N];

    const int digits = (((int)log10(key[_KEY_N]))+1)/2;
    int size_m = strlen(_m);
    double b = (double)strlen(_m)/(double)digits;
    const int blocks = ceil(b);

    //int c[blocks];

    char m_tmp[digits];
    int m_tmp_i = -1;
    char tmp[2];
    std::string s;

    for(int i=0; i < blocks; i++){

        m.copy(m_tmp,digits,(i*blocks));

        for(int j =0;j < digits; j++){
            int k = (int)m_tmp[j];
            sprintf(tmp,"%d",k);
            s.append(tmp);
        }
        m_tmp_i = atoi(s.c_str());

        BIGNUM *num_tmp2;
        num_tmp2 = BN_new();
        
        //BN_dec2bn()

        //BN_mod_exp(num_tmp,)

        int num_tmp = (pow(m_tmp_i,pub_key[_KEY_E]));
        //sscanf(m_tmp, "%d" , &m_tmp_i);
       // int pot = pow(m_tmp_i,pub_key[_KEY_E]);
        _c[i] = num_tmp % pub_key[_KEY_N];

    }

    return 1;
    
}

int Crypt::modInverse(int _phi, int _e){
    
    unsigned int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = _e;
    v1 = 0;
    v3 = _phi;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = _phi - u1;
    else
        inv = u1;
    return inv;

}

void Crypt::genKey()
{
    printf("generating Keys ...");
    int p = 47, q = 59;
    int n = p* q;
    int phi = (p-1)*(q-1);
    int e = 157;
    int d = modInverse(phi,e);

    key[_KEY_E] = e;
    printf("public key \n n: %d, e: %d\n",n,e);
    key[_KEY_N] = n;
    key[_KEY_D] = d;
    printf("private key \n n: %d, d: %d\n",n,d);

}


char * Crypt::generatePrime(long numBit) {

   /* char *prime;
    BIGNUM *num_tmp;
    num_tmp = BN_new();

    BN_generate_prime(num_tmp, numBit, 1, NULL, NULL, NULL, NULL);
    prime = (char *) malloc(BN_num_bytes(num_tmp));
    prime = BN_bn2dec(num_tmp);
    BN_free(num_tmp);
    return prime;*/
    //free(prime);
    //BN_free(num_tmp);
    return NULL;
}

