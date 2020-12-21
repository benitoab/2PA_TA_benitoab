#ifndef __DATABASE_H__
#define __DATABASE_H__ 1

#include <stdint.h>
#include "sqlite3.h"
extern "C" {
#include "../ADT/adt_memory_node.h"
#include "../ADT/adt_vector.h"
#include "abgs_platform_types.h"
#include "abgs_memory_manager.h"
}

const int32_t kNumSavedGames = 4;
const int32_t kNumProfession = 10;
const int32_t kNumAttacks = 16;
const int32_t kNumCharacter = 4;
const int32_t kNumTiles = 64*64;

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

struct AttacksData{

  int32_t id;
  int32_t dmg;       ///@var damage of the attack
  int32_t mana_cost; ///@var how many mana it costs
  uint8_t range;     ///@var the manhatan distance you need to be to use it.
  uint8_t type;      ///@var the type of the damage magic(0) or physical(1)
  char* name;        ///@var the name of the attack

};

struct SaveLoadBoard{
  int32_t id_world;
  int32_t logic_enabled;
  int32_t logic_enter;
  int32_t units_enabled;
  int32_t layer1_state;
  int32_t layer1_type;
  int32_t layer2_state;
  int32_t layer2_type;
};


struct GameData{
  int32_t id_game;
  int32_t id_char_1;
  int32_t id_char_2;
  int32_t id_char_3;
  int32_t id_char_4;
};

struct CharacterData{
  int32_t id;
  /*Tenemos que ver lo que poner*/
};

int callbackProfesion(void *profdata, int argc,
                       char **argv, char **azcolname);
      
int callbackAttacks(void *attdata, int argc,
                    char **argv, char **azcolname);

int callbackGame(void *gamedata, int argc,
                 char **argv, char **azcolname);
      
int callbackBoard(void *boardinfo, int argc,
                  char **argv, char **azcolname);      
      



class DataBase{
  
  public:
  
  DataBase();
  ~DataBase();
  
  int openDB(const char* path);
  void closeDB();
  
  void init();
  void freeData();
  
  void ReadGameData(const char* path);
  
  void readProfessionData();
  void readGameData();
  void readCharacterData();
  void readAttacksData();
  void readBoardData();
  void readLastGame();
  
  void saveBoardData();
  void saveNewCharacter();
  void saveGameData();
  
  void loadData();
  
  void loadCharacter();
  void loadBoard();
  
  
  void printProfession();
  
  
  //Atributes
  Vector* prof_vector_;
  Vector* games_vector_;
  Vector* char_vector_;
  Vector* att_vector_;
  Vector* board_vector_;
  

  AttacksData* attacks_[kNumAttacks]; 
  Character_Stats* profession_;
  Character_Stats* p_[kNumProfession];
  GameData* games_;
  CharacterData* char_data_;
  AttacksData* att_data_;
  SaveLoadBoard* board_data_;
  
  sqlite3* db_;
  
  
};

 


//void ReadProffesion(const char* directory);                   

#endif