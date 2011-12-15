/* 
 * File:   Connection.h
 * Author: develop
 *
 * Created on 23. November 2011, 12:45
 */

#ifndef _CONNECTION_H
#define	_CONNECTION_H

#define _PORT 51718
#define _ADDRESS 127.0.0.1
#define _READMODE 0
#define _WRITEMODE 1

class Connection {
public:

    Connection();
    Connection(const Connection& orig);
    virtual ~Connection();

    void setPort(int port);
    int getPort();

    void writeMsg(char *);
    char* readMsg();

    void changeMode(int mode);

    void error(const char *msg);

private:

    int port;
    char * adr;
    int mode;

};

#endif	/* _CONNECTION_H */

