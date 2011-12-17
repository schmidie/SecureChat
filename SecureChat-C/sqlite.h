/* 
 * File:   sqlite.h
 * Author: develop
 *
 * Created on 17. Dezember 2011, 07:00
 */
#include "crypto.h"

#ifndef _SQLITE_H
#define	_SQLITE_H

int init_sqlite();
int set_data(char * nickname,struct RSA * rsa);
int get_data(char ** nickname,struct RSA ** rsa);
int set_nick(char * nickname);
void close_sqlite();

#endif	/* _SQLITE_H */

