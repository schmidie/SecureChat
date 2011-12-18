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
#include "sqlite.h"
void print_help() {
     printf("Use of the chat: \n");
     printf("chat -h : prints this message. \n");
     printf("chat -i <nick>: create and store RSA key pair for the nick\n");
     printf("chat -c <host> <port>: open secure connection\n");
     printf("chat -l <port>: listen to port\n");
     printf("chat -r <nick>: change user\n");
}



/*
 * 
 */
int main(int argc, char** argv) {

    // loop and return var definitions
    int ret,n;

    if(argc==1) {
        print_help();
    }

    ret=init_sqlite();
    if(ret) {
        return ret;
    }

   
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
                                        set_data(argv[n+1],genKey());
                                        printf("Nick: %s \n", argv[n+1]);

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
                                        
                                        ret=get_data(&local_nick,&local_rsa);
                                        
                                        if(ret) {
                                            printf("Generate keys before you connect to anyone.\n");
                                            return EXIT_FAILURE;
                                        }
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
                                        printf("Specify ip and port of destination host.\n");
                                    }
                                    break;
                                }
                    case 'l':   {
                                    if(hasValue_1){
                                        int  port =atoi(argv[n+1]);
                                        ret=get_data(&local_nick,&local_rsa);
                                        
                                        if(ret) {
                                            printf("Generate keys before you connect to anyone.\n");
                                            return EXIT_FAILURE;
                                        }
                                        
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
                                        set_nick(argv[n+1]);
                                        printf("Nick: %s \n", argv[n+1]);
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
    close_sqlite();
    return (EXIT_SUCCESS);
}



