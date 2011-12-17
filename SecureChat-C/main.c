/* 
 * File:   main.c
 * Author: develop
 *
 * Created on 15. Dezember 2011, 10:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "crypto.h"
#include "connection.h"

void print_help() {
     printf("help comming soon! \n");
}



/*
 * 
 */
int main(int argc, char** argv) {

    if(argc==0) {
        print_help();
    }
    
    local_rsa=genKey();
    
    unsigned char * text=(unsigned char *)"Hallo2kljasldkjalskjdlkasjdlkasjdlkjasldkjalsdlaskjdlkajsdTEst";
    unsigned char * crypted;
    int cryptedsize=encrypt(text,strlen((char *)text),local_rsa,&crypted);
    unsigned char * decrypted;
    decrypt(crypted,cryptedsize,local_rsa,&decrypted);
    char * result=(char *)decrypted;
    printf("%s", result);
    printf("\n");
    
    
    // loop and return var definitions
    int ret,n;
    
    // variables for thread-handling
    int listening,connecting;
    pthread_t p1, p2;
    listening=0;
    connecting=0;

    //parameter parsing
    
    int hasValue_1=0;
    int hasValue_2=0;
   
    for(n = 1; n < argc; n++){

        if(argv[n][0] == '-'){

            if(strlen(argv[n]) == 2 ){
                // get the argument
                if(n+1 < argc && argv[n+1][0] != '-' && argv[n+1][0] != '/'){
                    hasValue_1 = 1;
                }
                if(n+2 < argc && argv[n+2][0] != '-' && argv[n+2][0] != '/'){
                    hasValue_2 = 1;
                }

                 switch (argv[n][1]) {

                    case 'h':   {
                                    print_help();
                                    return (EXIT_SUCCESS);
                                }

                    case 'i':   {
                                    if(hasValue_1){
                                        strcpy(local_nick,argv[n+1]);
                                        printf("Nick: %s \n", local_nick);

                                        //generate new RSA Key
                                        return (EXIT_SUCCESS);
                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                        return (EXIT_FAILURE);
                                    }
                                    break;
                                }
                    case 'c':   {
                                    if(hasValue_1 && hasValue_2){

                                        // Todo get the nick from db
                                        local_nick="Test";
                                        struct host * target;
                                        target=(struct host*)malloc(sizeof(struct host));
                                        target->ip =(char*)malloc(strlen(argv[n+1]));
                                        strcpy(target->ip,argv[n+1]);
                                        target->port = atoi(argv[n+2]);
                                        
                                        ret=pthread_create(&p2,NULL,connector,(void *) target);
                                        if(!ret){
                                            connecting=1;
                                        }

                                    }
                                    else{
                                        printf("Specify ip and port of destination.\n");
                                    }
                                    break;
                                }
                    case 'l':   {
                                    if(hasValue_1){
                                        int  port =atoi(argv[n+1]);
                                       
                                        //listen for connections
                                        printf("Listening on port: %d\n",port);
                                        ret=pthread_create(&p1,NULL,listener,(void *) port);
                                        if(!ret){
                                            listening=1;
                                        }
                                    }
                                    else{
                                        printf("Specify port to listen on.\n");
                                    }
                                    break;
                                }
                    case 'r':   {
                                    if(hasValue_1){
                                        // change nickname
                                        strcpy(local_nick,argv[n+1]);
                                        printf("Nick: %s \n", local_nick);
                                        return (EXIT_SUCCESS);
                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                        return (EXIT_FAILURE);
                                    }
                                    break;
                                }

                                    
                    default:    printf("Illegal argument. \n");
                                break;
                 }
            }
        }
               
    }

   
    if(listening) {
        pthread_join(p1,NULL);
    }
    if(connecting) {
        pthread_join(p2,NULL);
    }

    return (EXIT_SUCCESS);
}



