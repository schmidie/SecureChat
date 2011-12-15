/*
 * File:   Crypt.cpp
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/

#include "Crypto.h"
#include <openssl/bn.h>
#include <openssl/crypto.h>
#include <math.h>


void Crypt()
{

}


int getDecryptedSize(char *c){

    // bei Ascii mit max 3 stellen

}
int getEncryptedSize(char *m){

    // bei Ascii mit max 3 stellen
}

char* padding(int ascii){
    /*
   // bei Ascii mit max 3 stellen
    char retval[3];
    if(ascii >0){
        if(ascii < 10){
            retval[0]= '0';
            retval[1]='0';
            retval[2]= itoa(ascii);
        }
        else if(ascii < 100){
            retval[0]=itoa(0);
            retval[1]=itoa(floor(ascii /10));
            retval[2]= itoa(ascii%10);
        }
        else if(ascii < 1000){
            retval[0]=floor(ascii /100);
            retval[1]= floor((ascii%100) /10);
            retval[2]= ascii%10;
        }
    }

    return retval;*/return NULL;
}

int decrypt(char* _c, char * _m)
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
/*
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
        s.append(c_tmp);

        BIGNUM *bn_c = BN_new();
        BIGNUM *bn_n = BN_new();
        BIGNUM *bn_d = BN_new();
        BIGNUM *num_tmp = BN_new();

        BN_CTX *ctx = BN_CTX_new();

        BN_dec2bn(&bn_c,s.c_str());
        BN_dec2bn(&bn_d,key[_KEY_D]);
        BN_dec2bn(&bn_n,key[_KEY_N]);

        BN_mod_exp(num_tmp,bn_c,bn_d,bn_n,ctx);
        printf("DEC:%s = %s ^ %s mod %s \n",BN_bn2dec(num_tmp),s.c_str(),key[_KEY_D],key[_KEY_N] );
        retval.append(BN_bn2dec(num_tmp));

        //TODO: use BIGNUM, int is to small
       // int num_tmp = (int)pow(c_tmp_i,priv_key[_KEY_D]);
        //_m[i] = num_tmp % priv_key[_KEY_N];

    }
    BIGNUM *ret_bn = BN_new();
    BN_dec2bn(&ret_bn,retval.c_str());
    _m = (char *) malloc(BN_num_bytes(ret_bn));
    retval.copy(_m,retval.size(),0);

    return 1;*/return NULL;

}
int encrypt(char* _m , char* _c)
{

    //std::string m(_m);
    //std::string retval;

    // get key from database
    //pub_key[_KEY_E] = key[_KEY_E];
    //pub_key[_KEY_N] = key[_KEY_N];

    /*
    char* _c = (char *) malloc(length_m + 1);

    //Anzahl der Stellen pro Block
    const int digits = (((int)log10(atoi(key[_KEY_N]))+1))/2;
    
    double b = length_m/(double)digits;
    //Anzahl der Bloecke
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


        BIGNUM *bn_m = BN_new();
        BIGNUM *bn_n = BN_new();
        BIGNUM *bn_e = BN_new();
        BIGNUM *num_tmp = BN_new();

        BN_CTX *ctx = BN_CTX_new();

        BN_dec2bn(&bn_m,s.c_str());

        // TODO
        //char key_e[1024], key_n[1024];
        //sprintf(key_e,"%d",pub_key[_KEY_E]);
        BN_dec2bn(&bn_e,key[_KEY_E]);
        //sprintf(key_n,"%d",pub_key[_KEY_N]);
        BN_dec2bn(&bn_n,key[_KEY_N]);

        //printf("e: %s",key[_KEY_E]);
        //printf("n: %s",key[_KEY_N]);
        //printf("m: %s",s.c_str());
        //BN_print(stdout,bn1);
        //BN_print(stdout,bn2);
        //BN_print(stdout,bn3);

        BN_mod_exp(num_tmp,bn_m,bn_e,bn_n,ctx);

        //char * test = (char *) malloc(BN_num_bytes(num_tmp));
        //test = BN_bn2dec(num_tmp);
        //printf("encrypted: %s",test);
        //TODO: use BIGNUM, int is to small
        //int num_tmp = (pow(m_tmp_i,pub_key[_KEY_E]));
        //char * test = (char *) malloc(BN_num_bytes(num_tmp));
        //test = BN_bn2dec(num_tmp);


        printf("ENC: %s = %s ^ %s mod %s \n",BN_bn2dec(num_tmp),s.c_str(),key[_KEY_E],key[_KEY_N] );

        retval.append(BN_bn2dec(num_tmp)); //num_tmp % pub_key[_KEY_N];

    }

    BIGNUM *ret_bn = BN_new();
    BN_dec2bn(&ret_bn,retval.c_str());
    _c = (char *) malloc(BN_num_bytes(ret_bn));
    retval.copy(_c,retval.size(),0);

    return 1;
 * */
    return NULL;

}


void genKey()
{

    BIGNUM *n_bn = BN_new();
    BIGNUM *phi_bn = BN_new();
    BIGNUM *e_bn = BN_new();

    BIGNUM * p_bn = NULL;
    BIGNUM * q_bn = NULL;
    BIGNUM *d_bn = NULL;

    BN_CTX * ctx = BN_CTX_new();

    char *p = generatePrime(64);
    char *q = generatePrime(64);
    char *d = generatePrime(72);



    BN_dec2bn(&p_bn,p);
    BN_dec2bn(&q_bn,q);
    BN_dec2bn(&d_bn,d);

    // calculate n
    BN_mul(n_bn,p_bn,q_bn,ctx);

    //calculate phi
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 =  BN_new();
    BIGNUM *one =  BN_new();
    BN_dec2bn(&one,"1");
    BN_sub(tmp1,p_bn,one);
    BN_sub(tmp2,q_bn,one);
    BN_mul(phi_bn,tmp1,tmp2,ctx);

    // calculate e
    BN_mod_inverse(e_bn,d_bn,phi_bn,ctx);

    // store the key
    key[_KEY_E] =  (char *) malloc(BN_num_bytes(e_bn));
    key[_KEY_E] = BN_bn2dec(e_bn);
    key[_KEY_N] =  (char *) malloc(BN_num_bytes(n_bn));
    key[_KEY_N] = BN_bn2dec(n_bn);
    key[_KEY_D] =  (char *) malloc(BN_num_bytes(d_bn));
    key[_KEY_D] = BN_bn2dec(d_bn);

    printf("E: %s, N: %s, D: %s \n", key[_KEY_E],key[_KEY_N],key[_KEY_D]);

}

char * generatePrime(int numBit) {

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


