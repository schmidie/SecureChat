/*
 * File:   Connection.h
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#ifndef _CONNECTION_H
#define	_CONNECTION_H

void Connection();

void listener(int port);

void connector(char * host, int port);

void error(const char *msg);


#endif	/* _CONNECTION_H */

