/*
 * File:   Connection.h
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#ifndef _CONNECTION_H
#define	_CONNECTION_H

struct host{
    char* ip;
    int port;
};

void Connection();

void *listener(void * port);

void *connector(void * target);

void error(const char *msg);


#endif	/* _CONNECTION_H */

