#include <stdlib.h>
#include <stdio.h>
#include "database.h"
#include "gamemanager.h"


/*
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
}*/

int callbackProfesion(void *profdata, int argc,
                      char **argv, char **azcolname){
        
  Vector* aux_vector = (Vector*)profdata;
  Character_Stats* prof_info;
  
  prof_info = (Character_Stats*)calloc(1,sizeof(Character_Stats));
  
  prof_info->hp = atoi(argv[1]);
  prof_info->mana = atoi(argv[2]);
  prof_info->physical_att = atoi(argv[3]);
  prof_info->magic_att = atoi(argv[4]);
  prof_info->armor = atoi(argv[5]);
  prof_info->magic_resist = atoi(argv[6]);
  prof_info->movement = atoi(argv[7]);
  prof_info->mana_regen = atoi(argv[8]);
  prof_info->crit_chance = atoi(argv[9]);

  aux_vector->ops_->insertLast(aux_vector, 
  (void*)prof_info, (uint16_t)sizeof(Character_Stats));
  return 0;
}

int callbackAttacks(void *attdata, int argc,
                    char **argv, char **azcolname){
     
  Vector* aux_vector = (Vector*)attdata;
  AttacksData *att_info = (AttacksData*)calloc(1,sizeof(GameData));
 
  att_info->id = atoi(argv[0])-1;
  att_info->dmg = atoi(argv[1]);
  att_info->mana_cost = atoi(argv[2]);
  att_info->range = (uint8_t)atoi(argv[3]);
  att_info->type = (uint8_t)atoi(argv[4]);
  att_info->name = argv[5];
  
  aux_vector->ops_->insertLast(aux_vector, 
  (void*)att_info, (uint16_t)sizeof(AttacksData));

  return 0;                       
}

int callbackGame(void *gamedata, int argc,
                 char **argv, char **azcolname){
        
  Vector* aux_vector = (Vector*)gamedata;
  
  GameData *game_info = (GameData*)calloc(1,sizeof(GameData));
 
  game_info->id_game = atoi(argv[0]);
  game_info->id_char_1 = atoi(argv[1]);
  game_info->id_char_2 = atoi(argv[2]);
  game_info->id_char_3 = atoi(argv[3]);
  game_info->id_char_4 = atoi(argv[4]);
  
  aux_vector->ops_->insertLast(aux_vector, 
  (void*)game_info, (uint16_t)sizeof(GameData));

  return 0;
}

int callbackBoard(void *boardinfo, int argc,
                  char **argv, char **azcolname){
                    
  Vector* aux_vector = (Vector*)boardinfo;
  
  SaveLoadBoard *board_info = (SaveLoadBoard*)calloc(1,sizeof(SaveLoadBoard));

 
  board_info->logic_enabled = atoi(argv[1]);
  board_info->logic_enter = atoi(argv[2]);
  board_info->units_enabled = atoi(argv[3]);
  board_info->layer1_state = atoi(argv[4]);
  board_info->layer1_type = atoi(argv[5]);
  board_info->layer2_state = atoi(argv[6]);
  board_info->layer2_type = atoi(argv[7]);
  board_info->id_world = atoi(argv[8]);
  
  aux_vector->ops_->insertLast(aux_vector, 
  (void*)board_info, (uint16_t)sizeof(SaveLoadBoard));
 
  return 0;   
  
}


int callbackCharacter(void *characterdata, int argc,
                      char **argv, char **azcolname){
        
  Vector* aux_vector = (Vector*)characterdata;
  
  CharacterData *char_info = (CharacterData*)calloc(1,sizeof(CharacterData));

  char_info->id = atoi(argv[0]);/*
  char_info->logic_enabled = atoi(argv[1]);
  char_info->logic_enter = atoi(argv[2]);
  char_info->units_enabled = atoi(argv[3]);
  char_info->layer1_state = atoi(argv[4]);
  char_info->layer1_type = atoi(argv[5]);
  char_info->layer2_state = atoi(argv[6]);
  char_info->layer2_type = atoi(argv[7]);*/
  
  aux_vector->ops_->insertLast(aux_vector, 
  (void*)char_info, (uint16_t)sizeof(CharacterData));   

  return 0;
}



DataBase::DataBase(){
  
  profession_ = nullptr;
  games_ = nullptr;
  char_data_ = nullptr;
  att_data_ = nullptr;
  board_data_ = nullptr;
  db_ = nullptr;
  
  prof_vector_ = NULL;
  games_vector_ = NULL;
  char_vector_ = NULL;
  att_vector_ = NULL;
  board_vector_ = NULL;
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
  
  prof_vector_->ops_->destroy(prof_vector_);
  
  games_vector_->ops_->destroy(games_vector_);
  
  char_vector_->ops_->destroy(char_vector_);
  
  att_vector_->ops_->destroy(att_vector_);
  
  board_vector_->ops_->destroy(board_vector_);
  
}

void DataBase::init(){
  
  prof_vector_ = (Vector*) VECTOR_create(kNumProfession);
  games_vector_ = (Vector*) VECTOR_create(kNumSavedGames);
  char_vector_ = (Vector*) VECTOR_create(kNumCharacter);
  att_vector_ = (Vector*) VECTOR_create(kNumAttacks);
  board_vector_ = (Vector*) VECTOR_create(kNumTiles);
  
  profession_ = (Character_Stats*) calloc(kNumProfession, sizeof(Character_Stats));
  games_ = (GameData*) calloc(kNumSavedGames, sizeof(GameData));
  char_data_ = (CharacterData*) calloc(kNumCharacter, sizeof(CharacterData));
  att_data_ = (AttacksData*) calloc(kNumAttacks, sizeof(AttacksData));
  board_data_ = (SaveLoadBoard*) calloc(kNumTiles, sizeof(SaveLoadBoard));
 
 prof_vector_->ops_->print(prof_vector_);
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
  rc = sqlite3_exec(db_,sql1, callbackProfesion, (void*)prof_vector_, &err_msg);
  /*prof_vector_->ops_->print(prof_vector_);
  
  for(int i = 0; i<10; ++i){
    Character_Stats *aux_ptr;
    aux_ptr = (Character_Stats*)prof_vector_->ops_->extractFirst(prof_vector_);
     
    printf("hp:%d\n mana:%d\n", aux_ptr->hp, aux_ptr->mana);
    
  }*/
  loadData();
  printProfession();
}


void DataBase::printProfession(){
  /*
  for(int i = 0; i<kNumProfession; ++i){
    printf("hp:%d\nmana:%d\nad:%d\nap:%d\narmor:%d\nmr:%d\nmov:%d\nmana_reg:%d\ncrit:%d\n", 
    (profession_+i)->hp,(profession_+i)->mana,
    (profession_+i)->physical_att,
    (profession_+i)->magic_att,
    (profession_+i)->armor,
    (profession_+i)->magic_resist,
    (profession_+i)->movement,
    (profession_+i)->mana_regen,
    (profession_+i)->crit_chance);
  }*/
  
  for(int i = 0; i<kNumProfession; ++i){
    printf("clase %d\n", i);
    printf("hp:%d\nmana:%d\nad:%d\nap:%d\narmor:%d\nmr:%d\nmov:%d\nmana_reg:%d\ncrit:%d\n", 
    p_[i]->hp,p_[i]->mana,
    p_[i]->physical_att,
    p_[i]->magic_att,
    p_[i]->armor,
    p_[i]->magic_resist,
    p_[i]->movement,
    p_[i]->mana_regen,
    p_[i]->crit_chance);
    printf("____________\n\n");
  }
  
}

void DataBase::readGameData(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM games";
  rc = sqlite3_exec(db_,sql1, callbackGame, (void*)games_vector_, &err_msg);
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
  //char sql1[500]; 
  //int n = sprintf (sql1, "SELECT * FROM board"
                  // "WHERE board.id_game == %d",0);
                   
  char *sql1 = "SELECT * FROM board WHERE (board.id_game==0)";
                
  
  board_vector_->ops_->print(board_vector_);
  rc = sqlite3_exec(db_,sql1, callbackBoard, (void*)board_vector_, &err_msg);
}

void DataBase::readLastGame(){
  
  char *err_msg = 0;
  int rc = 0;

  char *sql1 = "SELECT * FROM games ORDER BY games.id DESC LIMIT 1";
  rc = sqlite3_exec(db_,sql1, callbackGame, (void*)games_, &err_msg);
}


void DataBase::saveBoardData(){
  
  GameManager& gM = GameManager::Instantiate();
  char sql1[500];
  char *err_msg = 0;
  int rc = 0;
  for(int i=0; i<64; ++i){
    for(int j = 0; j<64; ++j){
      int n = sprintf (sql1, "INSERT INTO board"
                  "(logic_enabled,logic_enter,"
                  "units_enabled,layer1_state,"
                  "layer1_type, layer2_state,"
                  "layer2_type, id_game)"
                  "VALUES(%d,%d,%d,%d,%d,%d,%d,%d)",
                  gM.board_[i][j].enabled_, 
                  gM.board_[i][j].enter_,
                  gM.units_[i][j].enabled_, 
                  gM.layer1_.map_[i][j].state_,
                  gM.layer1_.map_[i][j].type_,
                  gM.layer2_.map_[i][j].state_,
                  gM.layer2_.map_[i][j].type_,
                  0 );
      rc = sqlite3_exec(db_,sql1, NULL, 0, &err_msg);
      printf("voy por la : %d", i*64+j);
    }          
  }                

  /*gM.current_game_data_.id_game ); */
  //rc = sqlite3_exec(db_,sql1, NULL, 0, &err_msg);
}

void DataBase::saveNewCharacter(){
  
  char sql1[500];
  int rc = 0;
  char *err_msg = 0;
  int n = sprintf (sql1, "INSERT INTO character"/* Los campo que tenga nuestro character
            "(id_charracter1,id_charracter2,"
            "id_charracter3,id_charracter4)"
            "VALUES(%d,%d,%d,%d)",*/
            /*introducir los id de los nuevos personajes*/); 
           
   
  rc = sqlite3_exec(db_,sql1, NULL, 0, &err_msg);
}

void DataBase::saveGameData(){
  
  char sql1[500];
  int rc = 0;
  char *err_msg = 0;/*
  int n = sprintf (sql1, "INSERT INTO games"
            "(id_charracter1,id_charracter2,"
            "id_charracter3,id_charracter4)"
            "VALUES(%d,%d,%d,%d)",
            introducir los id de los nuevos personajes); */
           
   
  rc = sqlite3_exec(db_,sql1, NULL, 0, &err_msg);
 
}


void DataBase::loadCharacter(){
  GameManager& gM = GameManager::Instantiate();
  /*
  gM.player_[0] = *(char_data_+0);
  gM.player_[1] = *(char_data_+1);
  gM.player_[2] = *(char_data_+2);
  gM.player_[3] = *(char_data_+3);*/
  
}

void DataBase::loadBoard(){
  GameManager& gM = GameManager::Instantiate();
  int c = Board::kBoardSize, r = Board::kBoardSize;
  SaveLoadBoard* aux_board;

  for(int i = 0; i< r; ++i){
    for(int j = 0; j <c; ++j){
      
      aux_board = (SaveLoadBoard*) board_vector_->ops_->extractFirst(board_vector_);
      printf("\ni: %d\n", i*64+j);
     /* printf("e:%d\nen:%d\ne2:%d\ns:%d\nt:%d\ns2:%d\nt2:%d\n",
          aux_board->logic_enabled,aux_board->logic_enter,
          aux_board->units_enabled,
          aux_board->layer1_state,aux_board->layer1_type,
          aux_board->layer2_state,aux_board->layer2_type);*/
      
      gM.board_[i][j].enabled_ = aux_board->logic_enabled;
      gM.board_[i][j].enter_ = aux_board->logic_enter;
      gM.units_[i][j].enabled_ = aux_board->units_enabled;
      gM.layer1_.map_[i][j].state_ = aux_board->layer1_state;
      gM.layer1_.map_[i][j].type_ = aux_board->layer1_type;
      gM.layer2_.map_[i][j].state_ = aux_board->layer2_state;
      gM.layer2_.map_[i][j].type_ = aux_board->layer2_type;
      
      printf("e:%d\nen:%d\ne2:%d\ns:%d\nt:%d\ns2:%d\nt2:%d",
      gM.board_[i][j].enabled_,gM.board_[i][j].enter_,
      gM.units_[i][j].enabled_,
      gM.layer1_.map_[i][j].state_,gM.layer1_.map_[i][j].type_,
      gM.layer2_.map_[i][j].state_,gM.layer2_.map_[i][j].type_);
      
      

    }
  }
  /*
  for(int i = 0; i< r; ++i){
    for(int j = 0; j <c; ++j){
      
      gM.board_[i][j].enabled_ = (board_data_ + i * c + j)->logic_enabled;
      gM.board_[i][j].enter_ = (board_data_ + i * c + j)->logic_enter;
      gM.units_[i][j].enabled_ = (board_data_ + i * c + j)->units_enabled;
      gM.layer1_.map_[i][j].state_ = (board_data_ + i * c + j)->layer1_state;
      gM.layer1_.map_[i][j].type_ = (board_data_ + i * c + j)->layer1_type;
      gM.layer2_.map_[i][j].state_ = (board_data_ + i * c + j)->layer2_state;
      gM.layer2_.map_[i][j].type_ = (board_data_ + i * c + j)->layer2_type;
    }
  }*/
}


void DataBase::loadData(){
  
  for(int i = 0; i<kNumProfession; ++i){
    
    //(profession_+i) = (Character_Stats*)prof_vector_->ops_->extractFirst(prof_vector_);
    p_[i] = (Character_Stats*)prof_vector_->ops_->extractFirst(prof_vector_);
  }
  printProfession();
  //(...)
  
}



