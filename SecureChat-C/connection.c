/*
 * File:   Connection.cpp
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#include "connection.h"
#include "bnconvert.h"
#include "crypto.h"

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

        int numBytes;
        int size;
        printf("Incoming chat connection.\n");
       
        //For Waiting on Data
        fd_set listener_set;
        FD_ZERO(&listener_set);
        FD_SET(newsockfd, &listener_set);
        
         //Send n
        unsigned char * n_char=bn_to_char(local_rsa->n_bn);

        uint32_t nsize=bn_get_size_bigendian(local_rsa->n_bn);
        write(newsockfd,&nsize,4);
        write(newsockfd,n_char,bn_get_size(local_rsa->n_bn));

        //Send e
        unsigned char * e_char=bn_to_char(local_rsa->e_bn);
        uint32_t esize=bn_get_size_bigendian(local_rsa->e_bn);
        write(newsockfd,&esize,4);
        write(newsockfd,e_char,bn_get_size(local_rsa->e_bn));

        // Read Nick
        numBytes = read(newsockfd, &size, 4);
        if(numBytes==0) {
             perror("Couldn't read nick length.");
             pthread_exit(NULL);
        }
        size=ntohl(size);
        remote_nick=malloc(size);
        bzero(remote_nick,size);
        numBytes = read(newsockfd, remote_nick, size);
        printf("Remote Nick is %s.\n",remote_nick);
         fflush( stdout );
         
        while (1) {
           
           select(1+newsockfd,&listener_set,NULL,NULL,NULL);

           numBytes = read(newsockfd, &size, 4);
           size=ntohl(size);
           if (numBytes < 0)
           {
               perror("ERROR reading from socket");
               close(newsockfd);
               pthread_exit(NULL);
           } else if(numBytes==0) {
               // Remote connection closed
               close(newsockfd);
               pthread_exit(NULL);
           } else {
               unsigned char * crypted=malloc(size);
               bzero(crypted,size);
               numBytes = read(newsockfd, crypted, size);
               unsigned char * message;
               decrypt(crypted,size,local_rsa,&message);
               printf(">>%s", message);
           }
           
            
              
        } 
     
}

void *connector(void * _target){

        struct host* target = (struct host*)_target;

        struct sockaddr_in stSockAddr;
        int Res;
        
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
                int size,numBytes;
                remote_rsa=malloc(sizeof(struct RSA));
                // Read n
                numBytes = read(SocketFD, &size, 4);
                if(numBytes==0) {
                     perror("Couldn't read public key.");
                     pthread_exit(NULL);
                }
                size=ntohl(size);
                unsigned char * n_char=malloc(size);

                bzero(n_char,size);

                numBytes = read(SocketFD, n_char, size);

                remote_rsa->n_bn=char_to_bn(n_char,size);


                // Read e
                numBytes = read(SocketFD, &size, 4);
                if(numBytes==0) {
                     perror("Couldn't read public key.");
                     pthread_exit(NULL);
                }
                size=ntohl(size);
                unsigned char * e_char=malloc(size);
                //bzero(e_char,size);
                numBytes = read(SocketFD, e_char, size);

                remote_rsa->e_bn=char_to_bn(e_char,size);
               
                
                //Send Nick
                int nicklength=htonl((uint32_t)(strlen(local_nick)+1));
                
                write(SocketFD,&nicklength,sizeof(int));
                
                write(SocketFD,local_nick,strlen(local_nick)+1);
                
                while(1) {
                    unsigned char *buffer=malloc(INPUT_LENGTH);
                    bzero(buffer, INPUT_LENGTH);
                    fgets((char *)buffer, INPUT_LENGTH, stdin);

                    unsigned char * encrypted;
                    int cryptedsize=encrypt(buffer,strlen((char *)buffer),remote_rsa,&encrypted);
                    uint32_t msglength=htonl(cryptedsize);
                    send(SocketFD,(char *)&msglength,4,0);
                    send(SocketFD, (char *)encrypted, cryptedsize,0);
                }
                
            } else {
                printf("Failed connecting. Trying again in 5 seconds.\n");
                fflush( stdout );
                sleep(5);
            }

            
            

        }
}

