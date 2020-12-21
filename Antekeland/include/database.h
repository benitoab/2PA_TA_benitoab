/**
  * @file main.cc
  * @brief Main file of the game.
  * @details This is the core file. It gathers all classes of the game to make it possible.
  * @author Ricardo Beltrán Muriel <beltranmu@esat-alumni.com>
  * @version alfa 1.0
  * @date Ded-2020
  * @copyright ESAT
  */
 



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

const int32_t kNumSavedGames = 4;  ///@var max num of saved games that we read
const int32_t kNumProfession = 11; ///@var num of saved proffesion in DB
const int32_t kNumAttacks = 16;    ///@var num of saved attacks in the DB
const int32_t kNumCharacter = 4;   ///@var max num of saved characters that we read
const int32_t kNumTiles = 64*64;   ///@var max num of saved tiles that we read

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
/** @struct Stores the stats of attacks */
struct AttacksData{

  int32_t id;        ///@var att id
  int32_t dmg;       ///@var damage of the attack
  int32_t mana_cost; ///@var how many mana it costs
  uint8_t range;     ///@var the manhatan distance you need to be to use it.
  uint8_t type;      ///@var the type of the damage magic(2) or physical(1)
  char* name;        ///@var the name of the attack

};


/** @struct Stores information of a board */
struct SaveLoadBoard{
  int32_t id_world;       ///@var id of the game that it belongs
  int32_t logic_enabled;  ///@var save the value of enabled in the logic board
  int32_t logic_enter;    ///@var save the value of enter in the logic board
  int32_t units_enabled;  ///@var save the value of enabled in the uits board
  int32_t layer1_state;   ///@var save the value of state in the layer1
  int32_t layer1_type;    ///@var save the value of type in the layer1
  int32_t layer2_state;   ///@var save the value of state in the layer2
  int32_t layer2_type;    ///@var save the value of type in the layer2
};

/** @struct Stores information of a game*/
struct GameData{
  int32_t id_game;    ///@var id of the game 
  int32_t id_char_1;  ///@var id of the character 1
  int32_t id_char_2;  ///@var id of the character 2
  int32_t id_char_3;  ///@var id of the character 3
  int32_t id_char_4;  ///@var id of the character 4
};

struct CharacterData{
  int32_t id;
  /*Tenemos que ver lo que poner*/
};
/** 
 *@brief Callback to read stats of each class
 */
int callbackProfesion(void *profdata, int argc,
                       char **argv, char **azcolname);
      
/** 
 *@brief Callback to read stats of each attack
 */      
int callbackAttacks(void *attdata, int argc,
                    char **argv, char **azcolname);

/** 
 *@brief Callback to read the information of saved games
 */
int callbackGame(void *gamedata, int argc,
                 char **argv, char **azcolname);
   
/** 
 *@brief Callback to read the information of the board
 */
int callbackBoard(void *boardinfo, int argc,
                  char **argv, char **azcolname);      
     
class DataBase{
  
  public:
  
  DataBase();
  ~DataBase();
  
  /** 
   *@brief open the data base
   *@param const char* path, the parth where is the DB
   *@return return 0 if all goes ok 1 if not.
  */
  int openDB(const char* path);
  /** 
   *@brief close the data base
  */
  void closeDB();
  /** 
   *@brief init all variables to work with DB
  */
  void init();
  
  
  /** 
   *@brief read the information of each class and save it
  */
  void readProfessionData();
  /** 
   *@brief read the information of each game and save it
  */
  void readGameData();
  /** 
   *@brief read the information of each character and save it
  */
  void readCharacterData();
  /** 
   *@brief read the information of each attack and save it
  */
  void readAttacksData();
  /** 
   *@brief read the information of a board and save it
  */
  void readBoardData();
  /** 
   *@brief read the information of the last game saved and save it
  */
  void readLastGame();
  /** 
   *@brief save the information of the current board
  */
  void saveBoardData();
  /** 
   *@brief save all 4 character information in the game
  */
  void saveCharacter();
  /*void saveGameData();*/
  
  /** 
   *@brief load the information of attacks and professions
  */
  void loadData();
  /** 
   *@brief load the information of the character
  */
  void loadCharacter();
  /** 
   *@brief load the information  of the board
  */
  void loadBoard();

  void printProfession();
  
  
  //Atributes
  Vector* prof_vector_;  ///@var vector that is use to save professions info
  Vector* games_vector_; ///@var vector that is use to save games info
  Vector* char_vector_;  ///@var vector that is use to save characters info
  Vector* att_vector_;   ///@var vector that is use to save attacks info
  Vector* board_vector_; ///@var vector that is use to save board info
  

  AttacksData* attacks_[kNumAttacks];    ///@var used to saved the att information 
  Character_Stats* p_[kNumProfession];   ///@var used to saved the profession information 
  GameData* games_;                      ///@var used to saved the game information 
  CharacterData* char_data_;             ///@var used to saved the character information 
  
  sqlite3* db_;   ///@var cotains the database
  
  
};

 


//void ReadProffesion(const char* directory);                   

#endif