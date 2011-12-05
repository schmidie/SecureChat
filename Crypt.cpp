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
/*
     std::string c(_c);
    int priv_key[3];

    // get key from database
    priv_key[_KEY_D] = key[_KEY_D];
    priv_key[_KEY_N] = key[_KEY_N];

    const int digits = (((int)log10(priv_key[_KEY_N])+1)/2);
    int size_m = strlen(_c);
    double b = (double)strlen(_c)/(double)digits;
    const int blocks = ceil(b);
 * */

    std::string c(_c);
    std::string retval;

    const int digits = (((int)log10(atoi(key[_KEY_N]))+1));
    int size_m = strlen(_c);
    double b = (double)strlen(_c)/(double)digits;
    const int blocks = ceil(b);

    char c_tmp[digits];
    int c_tmp_i = 0;
    std::string s;

    for(int i=0; i < blocks; i++){

        c.copy(c_tmp,digits,(i*digits));
        c_tmp_i = atoi(c_tmp);

        BIGNUM *bn_c = BN_new();
        BIGNUM *bn_n = BN_new();
        BIGNUM *bn_d = BN_new();
        BIGNUM *num_tmp = BN_new();

        BN_CTX *ctx = BN_CTX_new();

        BN_dec2bn(&bn_c,s.c_str());
        BN_dec2bn(&bn_d,key[_KEY_D]);
        BN_dec2bn(&bn_n,key[_KEY_N]);

        BN_mod_exp(num_tmp,bn_c,bn_d,bn_n,ctx);

        retval.append(BN_bn2dec(num_tmp));

        //TODO: use BIGNUM, int is to small
       // int num_tmp = (int)pow(c_tmp_i,priv_key[_KEY_D]);
        //_m[i] = num_tmp % priv_key[_KEY_N];

    }
     retval.copy(_m,retval.length(),0);

    return 1;

}
int Crypt::encrypt(char* _m ,char* _c)
{
    std::string m(_m);
    std::string retval;
    // get key from database
    //pub_key[_KEY_E] = key[_KEY_E];
    //pub_key[_KEY_N] = key[_KEY_N];

    const int digits = (((int)log10(atoi(key[_KEY_N]))+1))/2;
    int size_m = strlen(_m);
    double b = (double)strlen(_m)/(double)digits;
    const int blocks = ceil(b);

    //int c[blocks];

    char m_tmp[digits];
    int m_tmp_i = -1;
    char tmp[digits];
    std::string s;

    for(int i=0; i < blocks; i++){

        m.copy(m_tmp,digits,(i*digits));

        for(int j =0;j < digits; j++){
            int k = (int)m_tmp[j];
            sprintf(tmp,"%d",k);
            s.append(tmp);
        }
        m_tmp_i = atoi(s.c_str());

        
        BIGNUM *bn_c = BN_new();
        BIGNUM *bn_n = BN_new();
        BIGNUM *bn_e = BN_new();
        BIGNUM *num_tmp = BN_new();
        
        BN_CTX *ctx = BN_CTX_new();

        BN_dec2bn(&bn_c,s.c_str());

        // TODO
        //char key_e[1024], key_n[1024];
        //sprintf(key_e,"%d",pub_key[_KEY_E]);
        BN_dec2bn(&bn_e,key[_KEY_E]);
        //sprintf(key_n,"%d",pub_key[_KEY_N]);
        BN_dec2bn(&bn_n,key[_KEY_N]);

        printf("e: %s",key[_KEY_E]);
        printf("n: %s",key[_KEY_N]);
        printf("m: %s",s.c_str());
        //BN_print(stdout,bn1);
        //BN_print(stdout,bn2);
        //BN_print(stdout,bn3);

        BN_mod_exp(num_tmp,bn_c,bn_e,bn_n,ctx);

        //char * test = (char *) malloc(BN_num_bytes(num_tmp));
        //test = BN_bn2dec(num_tmp);
        //printf("encrypted: %s",test);
        //TODO: use BIGNUM, int is to small
        //int num_tmp = (pow(m_tmp_i,pub_key[_KEY_E]));
        //char * test = (char *) malloc(BN_num_bytes(num_tmp));
        //test = BN_bn2dec(num_tmp);
        retval.append(BN_bn2dec(num_tmp)); //num_tmp % pub_key[_KEY_N];

    }

    retval.copy(_c,retval.length(),0);

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
    //printf("generating Keys ...");
    /*int p = generatePrime(64), q = generatePrime(64);
    int n = p* q;
    int phi = (p-1)*(q-1);
    int e = generatePrime(128);
    int d = modInverse(phi,e);

    key[_KEY_E] = e;
    printf("public key \n n: %d, e: %d\n",n,e);
    key[_KEY_N] = n;
    key[_KEY_D] = d;
    printf("private key \n n: %d, d: %d\n",n,d);

     */
    BIGNUM *n_bn, *phi_bn, *d_bn;
    n_bn = BN_new();
    phi_bn = BN_new();
    d_bn = BN_new();

    BN_CTX * ctx = BN_CTX_new();
    
    char *p = "47";//generatePrime(64);
    char *q = "59";//generatePrime(64);
    char *e = "157";//generatePrime(128);

    BIGNUM * bn_p = NULL;
    BIGNUM * bn_q = NULL;
    BIGNUM *bn_e = NULL;

    BN_dec2bn(&bn_p,p);
    BN_dec2bn(&bn_q,q);
    BN_dec2bn(&bn_e,e);

    // calculate n
    BN_mul(n_bn,bn_p,bn_q,ctx);

    //calculate phi
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 =  BN_new();
    BIGNUM *one =  BN_new();
    BN_dec2bn(&one,"1");
    BN_sub(tmp1,bn_p,one);
    BN_sub(tmp2,bn_q,one);
    BN_mul(phi_bn,tmp1,tmp2,ctx);

    // calculate d
    BN_mod_inverse(d_bn,bn_e,phi_bn,ctx);

    key[_KEY_E] =  (char *) malloc(BN_num_bytes(bn_e));
    key[_KEY_E] = BN_bn2dec(bn_e);
    key[_KEY_N] =  (char *) malloc(BN_num_bytes(n_bn));
    key[_KEY_N] = BN_bn2dec(n_bn);
    key[_KEY_D] =  (char *) malloc(BN_num_bytes(d_bn));
    key[_KEY_D] = BN_bn2dec(d_bn);

    //char * prime = (char *) malloc(BN_num_bytes(d_bn));
    //prime = BN_bn2dec(d_bn);
    //printf("d: %s", prime);
    //char * prime = (char *) malloc(BN_num_bytes(n_bn));
    //prime = BN_bn2dec(n_bn);
    //printf("key \n n: %d",prime);

}


char * Crypt::generatePrime(int numBit) {

    char *prime;
    BIGNUM *num_tmp;
    num_tmp = BN_new();

    BN_generate_prime(num_tmp, numBit, 1, NULL, NULL, NULL, NULL);
    prime = (char *) malloc(BN_num_bytes(num_tmp));
    prime = BN_bn2dec(num_tmp);
    BN_free(num_tmp);
    return prime;

    //free(prime);
    //BN_free(num_tmp);
    //return NULL;
}

