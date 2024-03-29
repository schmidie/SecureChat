/* 
 * File:   main.c
 * Author: develop
 *
 * Created on 15. Dezember 2011, 13:54
 */
#include "sqlite.h"
#include "bnconvert.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

sqlite3 *db;

int init_sqlite() {
        
    int ret;
    char *errorMsg;
    char *home = getenv("HOME");
    ret = sqlite3_open(strcat(home,"/.chatstore"), &db);
    if( ret ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(EXIT_FAILURE);
    }
    ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (ID INTEGER PRIMARY KEY, name TEXT,n BLOB,d BLOB,e BLOB); ", NULL, 0, &errorMsg);
    if( ret!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", errorMsg);
        sqlite3_free(errorMsg);
    }
    
    return 0;
}

int get_data(char ** nickname,struct RSA ** rsa) {
        sqlite3_stmt *statement;
	char *sql = "SELECT * FROM users WHERE id = '1'";

        const unsigned char * nickname_const;
        const void * n_const;
        const void * d_const;
        const void * e_const;
	BIGNUM * n;
        BIGNUM * d;
        BIGNUM * e;
	sqlite3_prepare(db, sql, strlen(sql), &statement, NULL);

        int ret=1;
	while(sqlite3_step(statement) != SQLITE_DONE)
	{
            ret=0;
            nickname_const=sqlite3_column_text(statement, 1);
            n_const=sqlite3_column_blob(statement, 2);
            d_const=sqlite3_column_blob(statement, 3);
            e_const=sqlite3_column_blob(statement, 4);
             int nicklength=sqlite3_column_bytes(statement,1);
             int nlength=sqlite3_column_bytes(statement,2);
             int dlength=sqlite3_column_bytes(statement,3);
             int elength=sqlite3_column_bytes(statement,4);
            *nickname=malloc(nicklength);
            bzero(*nickname,nicklength);
            *rsa=malloc(sizeof(struct RSA));
            bzero(*rsa,nlength);
            bzero(*rsa,dlength);
            bzero(*rsa,elength);
            
            n=char_to_bn(n_const,nlength);
            e=char_to_bn(e_const,elength);
            d=char_to_bn(d_const,dlength);
            memcpy(*nickname,nickname_const,nicklength);
            (*rsa)->n_bn=n;
            (*rsa)->d_bn=d;
            (*rsa)->e_bn=e;
            
	}
       
	
	sqlite3_finalize(statement);
        return ret;
}

int set_data(char * nickname,struct RSA * rsa) {
  const char   *sql = "INSERT OR REPLACE INTO users(ID, name,n,d,e) VALUES('1',?,?,?,?)";
  sqlite3_stmt *statement;
  

  if( sqlite3_prepare_v2(db, sql, strlen(sql)+1, &statement,0) != SQLITE_OK )
  {
      fprintf(stderr, "DB error: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return EXIT_FAILURE;
  }

  if(statement)
  {
      sqlite3_bind_text(statement, 1, nickname,strlen(nickname)+1, SQLITE_STATIC);
      sqlite3_bind_blob(statement, 2, bn_to_char(rsa->n_bn), bn_get_size(rsa->n_bn), SQLITE_STATIC);
      sqlite3_bind_blob(statement, 3, bn_to_char(rsa->d_bn), bn_get_size(rsa->d_bn), SQLITE_STATIC);
      sqlite3_bind_blob(statement, 4, bn_to_char(rsa->e_bn), bn_get_size(rsa->e_bn), SQLITE_STATIC);
      sqlite3_step(statement);
      sqlite3_finalize(statement);
      sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
      return 0;
  }
  else
  {
      fprintf(stderr,"DB error: Prepared statement is empty");
      sqlite3_close(db);
      return EXIT_FAILURE;
  }

}

int set_nick(char * nickname) {
  const char   *sql = "UPDATE users SET name=? WHERE ID='1'";
  sqlite3_stmt *statement;


  if( sqlite3_prepare_v2(db, sql, strlen(sql)+1, &statement,0) != SQLITE_OK )
  {
      fprintf(stderr, "DB error: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return EXIT_FAILURE;
  }

  if(statement)
  {
      sqlite3_bind_text(statement, 1, nickname,strlen(nickname)+1, SQLITE_STATIC);
      sqlite3_step(statement);
      sqlite3_finalize(statement);
      sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
      return 0;
  }
  else
  {
      fprintf(stderr,"DB error: Prepared statement is empty");
      sqlite3_close(db);
      return EXIT_FAILURE;
  }
}

void close_sqlite() {
    sqlite3_close(db);
}