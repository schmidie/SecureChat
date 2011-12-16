/*
 * File:   Connection.cpp
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#include "connection.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



void *listener(void * _port){
        int  port=(int )_port;
   
        int sockfd, newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            pthread_exit(NULL);
        }

        bzero((char *) & serv_addr, sizeof (serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = port;


        if (bind(sockfd, (struct sockaddr *) & serv_addr, sizeof (serv_addr)) < 0) {
            perror("ERROR on binding");
            pthread_exit(NULL);
        }

        listen(sockfd, 5);
        clilen = sizeof (cli_addr);

        newsockfd = accept(sockfd,(struct sockaddr *) & cli_addr, &clilen);
            if (newsockfd < 0) {
                    perror("ERROR on accept");
                    pthread_exit(NULL);
            }

        int n;
        char buffer[256];

        fd_set listener_set;
        FD_ZERO(&listener_set);
        FD_SET(newsockfd, &listener_set);
        while (1) {
           bzero(buffer, 256);
           select(1+newsockfd,&listener_set,NULL,NULL,NULL);
           n = read(newsockfd, buffer, 255);
           if (n < 0)
           {
               perror("ERROR reading from socket");
           } else if(n==0) {
               close(newsockfd);
               pthread_exit(NULL);
           } else {
                printf(">>%s", buffer);
           }

            
              
        } 
     
}

void *connector(void * _target){

        struct host* target = (struct host*)_target;

        struct sockaddr_in stSockAddr;
        int Res;
        char buffer[82];
        int ret;


        while (1) {

            int SocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            printf("Trying to connect to %s on port %d...\n",target->ip,target->port);
            if (-1 == SocketFD) {
                perror("Cannot create socket");
                pthread_exit(NULL);
            }

            memset(&stSockAddr, 0, sizeof (stSockAddr));

            stSockAddr.sin_family = AF_INET;
            stSockAddr.sin_port = target->port;
            Res = inet_pton(AF_INET, target->ip, &stSockAddr.sin_addr);

            if (0 > Res) {
                perror("error: first parameter is not a valid address family");
                close(SocketFD);
                 pthread_exit(NULL);
            } else if (0 == Res) {
                perror("char string (second parameter does not contain valid ipaddress)");
                close(SocketFD);
                 pthread_exit(NULL);
            }
            
            ret=connect(SocketFD, (struct sockaddr *) & stSockAddr, sizeof (stSockAddr));
            if (ret == 0 ) {
                printf("Connection successfully established.\n");
                while(1) {
                    bzero(buffer, 82);
                    fgets(buffer, 80, stdin);
                    send(SocketFD, buffer, strlen(buffer),0);
                }
                
            } else {
                printf("Faild connecting. Trying again in 5 seconds.\n");
                fflush( stdout );
                sleep(5);
            }

            
            

        }
}

