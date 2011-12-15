/* 
 * File:   Connection.cpp
 * Author: develop
 * 
 * Created on 23. November 2011, 12:45
 */

#include "Connection.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Connection::Connection()
{


}

Connection::Connection(const Connection& orig)
{
}

Connection::~Connection()
{
}

void Connection::setPort(int port)
{
    this->port = port;
}

int Connection::getPort()
{
    return this->port;
}

void Connection::writeMsg(char *)
{

}

char * Connection::readMsg()
{

}

void Connection::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Connection::changeMode(int _mode) {

    //printf("change mode to %d \n", (int)_mode);
    this->mode = (int)_mode;
    int port;
    this->port == NULL ? port = htons(_PORT) : port = htons(this->port);

    if (this->mode == _READMODE)
    {
        int sockfd, newsockfd, pid;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        bzero((char *) & serv_addr, sizeof (serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = port;
        

        if (bind(sockfd, (struct sockaddr *) & serv_addr, sizeof (serv_addr)) < 0)
            error("ERROR on binding");
        listen(sockfd, 5);
        clilen = sizeof (cli_addr);
             
        while (1) {

         //printf("Waiting for messages\n");
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
                error("ERROR on fork");
            if (pid == 0) {
                close(sockfd);
                int n;
                char buffer[256];

                bzero(buffer, 256);
                n = read(newsockfd, buffer, 255);
                if (n < 0) error("ERROR reading from socket");
                printf("message: %s", buffer);

                exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     close(sockfd);

    }
    else if (this->mode == _WRITEMODE) {

        struct sockaddr_in stSockAddr;
        int Res;
        char buffer[82];
        int n;


        while (1) {

            int SocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            if (-1 == SocketFD) {
                perror("cannot create socket");
                exit(EXIT_FAILURE);
            }

            memset(&stSockAddr, 0, sizeof (stSockAddr));

            stSockAddr.sin_family = AF_INET;
            stSockAddr.sin_port = port;
            Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

            if (0 > Res) {
                perror("error: first parameter is not a valid address family");
                close(SocketFD);
                exit(EXIT_FAILURE);
            } else if (0 == Res) {
                perror("char string (second parameter does not contain valid ipaddress)");
                close(SocketFD);
                exit(EXIT_FAILURE);
            }

            if (-1 == connect(SocketFD, (struct sockaddr *) & stSockAddr, sizeof (stSockAddr))) {
                perror("connect failed");
                close(SocketFD);
                exit(EXIT_FAILURE);
            }

            printf("Please enter your message: ");
            bzero(buffer, 82);
            fgets(buffer, 80, stdin);
            write(SocketFD, buffer, strlen(buffer));
            n = read(SocketFD, buffer, 80);
            //printf("The return message was\n");
            //write(1, buffer, n);

            close(SocketFD);

        }

    }
}