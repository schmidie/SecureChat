/*
 * File:   Crypt.cpp
 * Author: develop
 *
 * Created on 21. November 2011, 20:00
*/

#include "crypto.h"
#include <math.h>
#include <string.h>

  int decrypt(unsigned char *crypted,int msglength,struct RSA * rsa,unsigned char ** message) {
   
    int i;
    
    int blocksize=BN_num_bytes(rsa->n_bn);  //Get the length of n
   
    int blockcount=ceil((double)msglength/(double)blocksize);

    *message=malloc(blockcount*blocksize);

    for(i=0;i<blockcount;i++) {

        unsigned char * cryptedblock=malloc(blocksize);
        unsigned char * decryptedBlock=malloc(blocksize);

        memcpy(cryptedblock,crypted+i*blocksize,blocksize);
      
        decryptBlock(cryptedblock,blocksize,decryptedBlock,rsa);

        memcpy(*message+i*blocksize,decryptedBlock,blocksize);

        free(cryptedblock);
        free(decryptedBlock);

    }
    return blockcount*blocksize;

}

  int encrypt(unsigned char *message,int msglength,struct RSA * rsa,unsigned char ** crypted) {
   
    int i;
   
    int blocksize=BN_num_bytes(rsa->n_bn); //Get the length of n
   
    int blockcount=ceil((double)msglength/(double)blocksize);
    *crypted=malloc(blocksize*blockcount);
    
    for(i=0;i<blockcount;i++) {

        unsigned char * block=malloc(blocksize);
        unsigned char * encryptedBlock=malloc(blocksize);

        int copySize=blocksize;

        if((msglength-i*blocksize)<blocksize) {
            copySize=msglength-i*blocksize;
        }

        memcpy(block,message+i*blocksize,copySize);
       
        encryptBlock(block,copySize,encryptedBlock,rsa);
        
        memcpy(*crypted+i*blocksize,encryptedBlock,blocksize);

        free(encryptedBlock);
        free(block);
    }
    return blocksize*blockcount;

}


void decryptBlock( const unsigned char* crypted,int length, unsigned char * message,struct RSA * rsa)
{

    BIGNUM * bn_crypted = BN_new();
    BN_bin2bn(crypted,length,bn_crypted);

   
    BIGNUM *bn_decrypted = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BN_mod_exp(bn_decrypted,bn_crypted,rsa->d_bn,rsa->n_bn,ctx);
    
   
    BN_bn2bin(bn_decrypted,message);
    BN_free(bn_crypted);
    BN_free(bn_decrypted);
    BN_CTX_free(ctx);
   

}
void encryptBlock( const unsigned char* message ,int length, unsigned char* crypted,struct RSA * rsa)
{
    int n_size=BN_num_bytes(rsa->n_bn);
    int i;
    unsigned char * paddedmsg=malloc(n_size);
    memcpy(paddedmsg,message,length);
    for(i=length;i<n_size;i++) {
        paddedmsg[i]='\0';
    }

    BIGNUM * bn_message= BN_new();
    BN_bin2bn(paddedmsg,n_size,bn_message);
    free(paddedmsg);
    
    BIGNUM *bn_crypted = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BN_mod_exp(bn_crypted,bn_message,rsa->e_bn,rsa->n_bn,ctx);
    
    BN_bn2bin(bn_crypted,crypted);

    BN_free(bn_crypted);
    BN_free(bn_message);
    BN_CTX_free(ctx);

}


struct RSA * genKey()
{
    struct RSA * rsa=malloc(sizeof(struct RSA));
    //TODO: FIX KEYS
    rsa->n_bn = BN_new();
    rsa->e_bn = BN_new();
    rsa->d_bn = BN_new();

    BIGNUM * phi_bn = BN_new();
    BIGNUM * p_bn = BN_new();
    BIGNUM * q_bn = BN_new();

    BN_CTX * ctx = BN_CTX_new();

    char *p = generatePrime(64);
    char *q = generatePrime(64);
    char *d = generatePrime(72);

    BN_dec2bn(&p_bn,p);
    BN_dec2bn(&q_bn,q);
    BN_dec2bn(&rsa->d_bn,d);

    // calculate n
    BN_mul(rsa->n_bn,p_bn,q_bn,ctx);

    //calculate phi
    BIGNUM *tmp1 = BN_new();
    BIGNUM *tmp2 =  BN_new();
    BIGNUM *one =  BN_new();
    BN_dec2bn(&one,"1");
    BN_sub(tmp1,p_bn,one);
    BN_sub(tmp2,q_bn,one);
    BN_mul(phi_bn,tmp1,tmp2,ctx);

    // calculate e
    BN_mod_inverse(rsa->e_bn,rsa->d_bn,phi_bn,ctx);
    
    //release things
    free(q);
    free(p);
    free(d);
    BN_CTX_free(ctx);
    BN_free(tmp1);
    BN_free(tmp2);
    BN_free(one);
    BN_free(phi_bn);
    BN_free(q_bn);
    BN_free(p_bn);
    return rsa;
}

 char * generatePrime(int numBit) {

    char *prime;
    BIGNUM *num_tmp;
    num_tmp = BN_new();

    BN_generate_prime(num_tmp, numBit, 1, NULL, NULL, NULL, NULL);
    prime = ( char *) malloc(BN_num_bytes(num_tmp));
    prime = BN_bn2dec(num_tmp);
    BN_free(num_tmp);
    return prime;

}


