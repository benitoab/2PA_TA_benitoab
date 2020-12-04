#ifndef __DATABASE_H__
#define __DATABASE_H__ 1

#include <stdint.h>
#include "sqlite3.h"


/** @struct Stores the stats of the characters */
struct Character_Stats{

  int32_t hp;
  int32_t mana;
  int32_t physical_att; 
  int32_t magic_att;
  int32_t armor;
  int32_t magic_resist;
  int32_t movement; 
  int32_t mana_regen; 
  int32_t crit_chance; 
};

struct SaveLoadBoard{
  int32_t id_world;
  int32_t logic_state;
  int32_t logic_type;
  int32_t units_state;
  int32_t layer1_state;
  int32_t layer1_type;
  int32_t layer2_state;
  int32_t layer2_type;
};


struct GameData{
  int32_t previous_board;
  int32_t id_board;
  int32_t id_char_1;
  int32_t id_char_2;
  int32_t id_char_3;
  int32_t id_char_4;
};


int callbackProfesion(void *proffdata, int argc,
                       char **argv, char **azcolname);
                       
//int callbackAttacks(void *attdata, int argc,
                    //char **argv, char **azcolname);



class DataBase{
  
  public:
  
  DataBase();
  ~DataBase();
  
  int openDB(const char* path);
  void closeDB();
  
  void init();
  
  void ReadGameData(const char* path);
  //void readProfessionData(const char* path);
  void readProfessionData();
  
  
  //Atributes
  Character_Stats* profession_;
  
  sqlite3* db_;
  
  
};

 


//void ReadProffesion(const char* directory);                   

#endif