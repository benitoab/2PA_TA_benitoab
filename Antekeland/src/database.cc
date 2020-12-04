#include <stdlib.h>
#include <stdio.h>
#include "database.h"
#include "character.h"



int callbackProfesion(void *proffdata, int argc,
                       char **argv, char **azcolname){
        
  Character_Stats* p_data = (Character_Stats*)proffdata;
  printf("HOLA");
  int i = atoi(argv[0])-1;
 
  (p_data+i)->hp = atoi(argv[1]);
  (p_data+i)->mana = atoi(argv[2]);
  (p_data+i)->physical_att = atoi(argv[3]);
  (p_data+i)->magic_att = atoi(argv[4]);
  (p_data+i)->armor = atoi(argv[5]);
  (p_data+i)->magic_resist = atoi(argv[6]);
  (p_data+i)->movement = atoi(argv[7]);
  (p_data+i)->mana_regen = atoi(argv[8]);
  (p_data+i)->crit_chance = atoi(argv[9]);
  return 0;
}



DataBase::DataBase(){
  profession_ = nullptr;
  db_ = nullptr;
}

DataBase::~DataBase(){
  if(nullptr != profession_){
    free(profession_);
  }
  
  if(nullptr != db_){
    
    sqlite3_close(db_);
  }
}

void DataBase::init(){
  
  profession_ = (Character_Stats*) calloc(8, sizeof(Character_Stats));
 
}


int DataBase::openDB(const char* path){
  
  int rc = sqlite3_open(path, &db_);
  
  if(rc != SQLITE_OK){
    fprintf(stderr,"Cannot open database: %s\n", sqlite3_errmsg(db_));
    sqlite3_close(db_);
    return 1;
  }
  return 0;
}

void DataBase::closeDB(){
  
  if(nullptr != db_){
    
    sqlite3_close(db_);
  }
}

void DataBase::readProfessionData(){
  
  //sqlite3* db_;
  char *err_msg = 0;
  int rc = 0;
 // int rc = sqlite3_open(path, &db_);
  
 // if(rc != SQLITE_OK){
    //fprintf(stderr,"Cannot open database: %s\n", sqlite3_errmsg(db_));
    //sqlite3_close(db_);
    //return 1;
 // }
 // return 0;
  
  char *sql1 = "SELECT * FROM c";
  //char *sql1 = "SELECT * FROM character_profession";
  printf("HOLA");
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)profession_, &err_msg);
  sqlite3_close(db_);
  
  
}



