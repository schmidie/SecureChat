/* 
 * File:   main.c
 * Author: develop
 *
 * Created on 15. Dezember 2011, 13:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

 static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
  }



/*
 * 
 */
int main2(int argc, char** argv) {
    (void)argc;
    (void)argv;

    sqlite3 *db;
    int ret;
    char *errorMsg = 0;
    char*home=getenv("HOME");
    ret = sqlite3_open(strcat(home,"/chatstore"), &db);
    if( ret ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(EXIT_FAILURE);
    }
    ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (t1key INTEGER PRIMARY KEY, name TEXT,e BLOB, n BLOB, d BLOB); ", callback, 0, &errorMsg);
    if( ret!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", errorMsg);
        sqlite3_free(errorMsg);
    }
    sqlite3_close(db);
    return (EXIT_SUCCESS);
}

