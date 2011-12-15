/* 
 * File:   main.c
 * Author: develop
 *
 * Created on 15. Dezember 2011, 10:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypto.h"
#include "connection.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int n, l;

    char nick[256];
    char host[256];
    int port;
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
                                        strcpy(host,argv[n+1]);
                                        port = (int)argv[n+2];
                                        printf("Host: %s \n", host);
                                        printf("Port: %d \n", port);

                                        //try to connect to host

                                    }
                                    else{
                                        printf("Write nick without - or / \n");
                                    }
                                    break;
                                }
                    case 'l':   {
                                    if(hasValue_1){
                                        port = (int)argv[n+1];
                                        printf("Port: %d \n", port);

                                        //listen for connections

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
    
    return (EXIT_SUCCESS);
}



