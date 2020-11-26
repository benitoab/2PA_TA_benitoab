#ifndef __DATABASE_H__
#define __DATABASE_H__ 1

#include "sqlite3.h"


int callbackProffesion(void *proffdata, int argc,
                       char **argv, char **azcolname);
                       
//int callbackAttacks(void *attdata, int argc,
                    //char **argv, char **azcolname); 


//void ReadProffesion(const char* directory);                   

#endif