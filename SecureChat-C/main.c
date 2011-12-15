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

    int n;

   // char input[256];

    char nick[256];
    char host[256];
    int port = 0;
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
*/
    for(n = 1; n <= argc; n++){

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

                                        struct host target;

                                        strcpy(target.ip,argv[n+1]);
                                        target.port = atoi(argv[n+2]);
                                        printf("Host: %s \n", host);
                                        printf("Port: %d \n", port);

                                        //try to connect to host
                                        //connector(host,port);

                                        pthread_create(&p2,NULL,connector, &target);

                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                    }
                                    break;
                                }
                    case 'l':   {
                                    if(hasValue_1){
                                        port = atoi(argv[n+1]);
                                        printf("Port: %d \n", port);

                                        //listen for connections
                                        pthread_create(&p1,NULL,listener,(void *) port);

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
    pthread_join(&p1,NULL);
    pthread_join(&p2,NULL);
    return (EXIT_SUCCESS);
}



