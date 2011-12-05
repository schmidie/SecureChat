/* 
 * File:   main.cpp
 * Author: develop
 *
 * Created on 21. November 2011, 19:59
 */

#include <unistd.h>


#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "Connection.h"
#include "Crypt.h"

#define _THREADCOUNT 2

/*
 * 
 */

void * changeMode(void * mode){
    Connection* con = new Connection();
    con->changeMode((int)mode);
}


int main(int argc, char** argv) {

    Crypt *crypt = new Crypt();
    long a = 1024;
    printf("Keys: \n");
    crypt->genKey();

    char cryptText[1024], encText[1024];
    crypt->encrypt("ITS ALL GREEK TO ME",cryptText);
    crypt->decrypt(cryptText,encText);

    pthread_t th_pool[_THREADCOUNT];
    
    int m = argc>1 ? atoi(argv[1]): _READMODE;

    pthread_create(&th_pool[0],NULL, changeMode, (void *) m);

    pthread_exit(NULL);
    return (EXIT_SUCCESS);
    
}


