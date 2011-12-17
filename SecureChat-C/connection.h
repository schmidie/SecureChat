/*
 * File:   Connection.h
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#ifndef _CONNECTION_H
#define	_CONNECTION_H
#define INPUT_LENGTH 80

struct host{
    char* ip;
    int port;
};

struct RSA * remote_rsa;
struct RSA * local_rsa;
char * remote_nick;
char * local_nick;

void *listener(void * port);

void *connector(void * target);


#endif	/* _CONNECTION_H */

