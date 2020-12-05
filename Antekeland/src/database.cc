#include <stdlib.h>
#include <stdio.h>
#include "database.h"
#include "character.h"



int callbackProfesion(void *profdata, int argc,
                       char **argv, char **azcolname){
        
  Character_Stats* p_data = (Character_Stats*)profdata;
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

int callbackGame(void *gdata, int argc,
                 char **argv, char **azcolname){
        
  GameData* g_data = (GameData*)gdata;
  int i = atoi(argv[0])-1;
   
  (g_data+i)->previous_board = atoi(argv[1]);
  (g_data+i)->id_board = atoi(argv[2]);
  (g_data+i)->id_char_1 = atoi(argv[3]);
  (g_data+i)->id_char_2 = atoi(argv[4]);
  (g_data+i)->id_char_3 = atoi(argv[5]);
  (g_data+i)->id_char_4 = atoi(argv[6]);

  return 0;
}


/*
int callbackCharacter(void *characterdata, int argc,
                      char **argv, char **azcolname){
        
  CharacterData* c_data = (CharacterData*)characterdata;
  int i = atoi(argv[0])-1;
   
  (c_data+i)->privous_board = atoi(argv[1]);
  (c_data+i)->id_board = atoi(argv[2]);
  (c_data+i)->id_char_1 = atoi(argv[3]);
  (c_data+i)->id_char_2 = atoi(argv[4]);
  (c_data+i)->id_char_3 = atoi(argv[5]);
  (c_data+i)->id_char_4 = atoi(argv[6]);

  return 0;
}*/


int callbackBoard(void *boardinfo, int argc,
                  char **argv, char **azcolname){
        
  SaveLoadBoard* b_data = (SaveLoadBoard*)boardinfo;
  
  int i = atoi(argv[0])-1;
   
  (b_data+i)->id_world = atoi(argv[1]);
  (b_data+i)->logic_state = atoi(argv[2]);
  (b_data+i)->logic_type = atoi(argv[3]);
  (b_data+i)->units_state = atoi(argv[4]);
  (b_data+i)->layer1_state = atoi(argv[5]);
  (b_data+i)->layer1_type = atoi(argv[6]);
  (b_data+i)->layer2_state = atoi(argv[7]);
  (b_data+i)->layer2_type = atoi(argv[8]);
 
  return 0;   
  
}

int callbackAttacks(void *attdata, int argc,
                    char **argv, char **azcolname){
     
  AttacksData* a_data = (AttacksData*)attdata;
  
  int i = atoi(argv[0])-1;
  (a_data+i)->id = atoi(argv[0])-1;
   
  (a_data+i)->dmg= atoi(argv[1]);
  (a_data+i)->mana_cost = atoi(argv[2]);
  (a_data+i)->range = (uint8_t)atoi(argv[3]);
  (a_data+i)->type = (uint8_t)atoi(argv[4]);
  (a_data+i)->name = argv[5];

  return 0;                       
}



DataBase::DataBase(){
  profession_ = nullptr;
  games_ = nullptr;
  db_ = nullptr;
}

DataBase::~DataBase(){
  if(nullptr != profession_){
    free(profession_);
  }
  
  if(nullptr != games_){
    free(profession_);
  }
  
  if(nullptr != db_){
    sqlite3_close(db_);
  }
  
  if(nullptr != char_data_){
    free(char_data_);
  }
  
  if(nullptr != att_data_){
    free(att_data_);
  }
  
  if(nullptr != board_data_){
    free(board_data_);
  }
  
}

void DataBase::init(){
  
  profession_ = (Character_Stats*) calloc(kNumProfession, sizeof(Character_Stats));
  games_ = (GameData*) calloc(kNumSavedGames, sizeof(GameData));
  char_data_ = (CharacterData*) calloc(kNumCharacter, sizeof(CharacterData));
  att_data_ = (AttacksData*) calloc(kNumAttacks, sizeof(AttacksData));
  board_data_ = (SaveLoadBoard*) calloc(kNumTiles, sizeof(SaveLoadBoard));
 
}

void DataBase::freeData(){
  if(nullptr != profession_){
    free(profession_);
  }
  
  if(nullptr != games_){
    free(games_);
  }
  
  if(nullptr != char_data_){
    free(char_data_);
  }
  
  if(nullptr != att_data_){
    free(att_data_);
  }
  
  if(nullptr != board_data_){
    free(board_data_);
  }

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
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM character_profession";
  printf("HOLA");
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)profession_, &err_msg);

}

void DataBase::readGameData(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM games";
  printf("HOLA");
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)games_, &err_msg);
}

void DataBase::readCharacterData(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM character";
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)char_data_, &err_msg);
}

void DataBase::readAttacksData(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM attacks";
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)att_data_, &err_msg);
}

void DataBase::readBoardData(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM board";
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)board_data_, &err_msg);
}




