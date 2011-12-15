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

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t p1, p2;

    int ret,n,listening,connecting;

   // char input[256];

    char nick[256];

    int hasValue_1=0;
    int hasValue_2=0;
   
    /*
    while(1){

        argc = 1;

    printf(">>");
    gets(input);
    
    char* pch;
    char det[] = " ";

    pch = strtok(input,det);

    while(pch != NULL){
        sprintf(argv[argc],"%s",pch);
        pch = strtok(NULL,det);
        argc++;
    }
     *
*/
    listening=0;
    connecting=0;
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
                                    printf("help comming soon! \n");
                                    break;
                                }

                    case 'i':   {
                                    if(hasValue_1){
                                        strcpy(nick,argv[n+1]);
                                        printf("Nick: %s \n", nick);

                                        //generate new RSA Key

                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                    }
                                    break;
                                }
                    case 'c':   {
                                    if(hasValue_1 && hasValue_2){

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
                                        printf("Write nick without - or / \n");
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
                                        printf("Write port without - or / \n");
                                    }
                                    break;
                                }
                    case 'r':   {
                                    if(hasValue_1){
                                        // change nickname
                                        strcpy(nick,argv[n+1]);
                                        printf("Nick: %s \n", nick);
                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                    }
                                    break;
                                }

                                    
                    default:    printf("Illegal argument. \n");
                                break;
                 }
            }
        }
               
    }

   // genKey();
    if(listening) {
        pthread_join(p1,NULL);
    }
    if(connecting) {
        pthread_join(p2,NULL);
    }

    return (EXIT_SUCCESS);
}



