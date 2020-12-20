#include "stdlib.h"

#include "combatscene.h"
#include "gamemanager.h"
#include <stdlib.h>


CombatScene::CombatScene(){
  
  num_turns_ = 0;
  current_character_ = 0;
  total_turns_ = 0;
}

CombatScene::~CombatScene(){

}

void CombatScene::init(){

  GameManager& gM = GameManager::Instantiate();
  gM.over_world_scene_=0;
  SDL_Rect r1 = {0, 0, 640, 640};
  
  cave_[0].initSprite(*gM.ground_cave_, &r1, &r1);
  cave_[1].initSprite(*gM.frozen_cave_, &r1, &r1);

  // Init Logic Cave map
  for(int i = 0; i < 16; ++i){
    for(int j = 0; j < 16; ++j){
      if(i == 0 || i == 15 || j == 0 || j == 15
        ||i == 1 || j == 14|| j == 1){ 
        gM.logic_board_[i][j].enabled_ = 0;
        gM.logic_board_[i][j].enter_ = 0;
        gM.units_board_[i][j].enabled_ = 255;        
      }else{
        gM.logic_board_[i][j].init();
        gM.units_board_[i][j].enabled_ = 255;
      }
      
    }
  }
  
  if(rand()%10 < 5){
    gM.logic_board_[2][2].enabled_ = 0;
    gM.logic_board_[2][13].enabled_ = 0;
    gM.logic_board_[3][10].enabled_ = 0;
    gM.logic_board_[4][4].enabled_ = 0;
    gM.logic_board_[4][5].enabled_ = 0;
    gM.logic_board_[4][10].enabled_ = 0;
    gM.logic_board_[4][11].enabled_ = 0;
    gM.logic_board_[4][11].enter_ = 3;
    gM.logic_board_[5][4].enabled_ = 0;
    gM.logic_board_[5][10].enabled_ = 0;
    gM.logic_board_[5][11].enabled_ = 0;
    gM.logic_board_[5][12].enabled_ = 0;
    gM.logic_board_[7][7].enabled_ = 0;
    gM.logic_board_[7][8].enabled_ = 0;
    gM.logic_board_[8][7].enabled_ = 0;
    gM.logic_board_[9][5].enabled_ = 0;
    gM.logic_board_[10][5].enabled_ = 0;
    gM.logic_board_[10][11].enabled_ = 0;
    gM.logic_board_[10][12].enabled_ = 0;
    gM.logic_board_[10][13].enabled_ = 0;
    gM.logic_board_[11][3].enabled_ = 0;
    gM.logic_board_[11][4].enabled_ = 0;
    gM.logic_board_[11][5].enabled_ = 0;
    gM.logic_board_[13][9].enabled_ = 0;
    gM.logic_board_[13][12].enabled_ = 1;
    gM.logic_board_[13][12].enter_ = 1;
    gM.logic_board_[14][9].enabled_ = 0;
    ent_list.push_back(&cave_[0]);
  }else{
    gM.logic_board_[2][13].enabled_ = 0;
    gM.logic_board_[2][13].enter_ = 3;
    gM.logic_board_[4][3].enabled_ = 0;
    gM.logic_board_[4][4].enabled_ = 0;
    gM.logic_board_[4][5].enabled_ = 0;
    gM.logic_board_[5][3].enabled_ = 0;
    gM.logic_board_[5][4].enabled_ = 0;
    gM.logic_board_[5][5].enabled_ = 0;
    gM.logic_board_[6][3].enabled_ = 0;
    gM.logic_board_[6][4].enabled_ = 0;
    gM.logic_board_[6][5].enabled_ = 0;
    gM.logic_board_[8][9].enabled_ = 0;
    gM.logic_board_[8][10].enabled_ = 0;
    gM.logic_board_[8][11].enabled_ = 0;
    gM.logic_board_[9][5].enabled_ = 0;
    gM.logic_board_[9][6].enabled_ = 0;
    gM.logic_board_[10][5].enabled_ = 0;
    gM.logic_board_[10][6].enabled_ = 0;
    gM.logic_board_[9][9].enabled_ = 0;
    gM.logic_board_[9][10].enabled_ = 0;
    gM.logic_board_[9][11].enabled_ = 0;
    gM.logic_board_[10][9].enabled_ = 0;
    gM.logic_board_[10][10].enabled_ = 0;
    gM.logic_board_[10][11].enabled_ = 0;
    gM.logic_board_[10][3].enabled_ = 1;
    gM.logic_board_[10][3].enter_ = 1;
    ent_list.push_back(&cave_[1]);
  }

  //Init  Enemies
  
  int n_e = rand()%5+2,x = 0, y = 0;
  
  for(int i= 0; i < n_e; ++i){
    gM.NPC_[i].initEnemy((rand()%5)+1, i+4);
    //Give initial pos
    do{
      x = rand()%16, y = rand()%3+2;
    }while(gM.logic_board_[y][x].enabled_ == 0
        || gM.units_board_[y][x].enabled_ != 255);
    gM.NPC_[i].dst_rect_.x = x;
    gM.NPC_[i].dst_rect_.y = y;
    gM.NPC_[i].dst_rect_.w = 40;
    gM.NPC_[i].dst_rect_.h = 40;
    gM.units_board_[y][x].enabled_= i+4;
    
    ent_list.push_back(&gM.NPC_[i]);

  }
  
  for(int i= 0; i < 4; ++i){
    //Give initial pos
    
    do{
      x = rand()%16, y = rand()%3+11;
    }while(gM.logic_board_[y][x].enabled_ == 0
        || gM.units_board_[y][x].enabled_ != 255);
        
    gM.units_board_[y][x].enabled_= i;
    gM.player_[i].dst_rect_.x = x;
    gM.player_[i].dst_rect_.y = y;
    gM.player_[i].dst_rect_.w = 40;
    gM.player_[i].dst_rect_.h = 40;
    gM.player_[i].index_mov_ = 0;
    gM.player_[i].previous_movs_[gM.player_[i].index_mov_]= gM.player_[i].dst_rect_.y*16+ gM.player_[i].dst_rect_.x;
    gM.player_[i].current_.movement = gM.player_[i].base_.movement;
    ent_list.push_back(&gM.player_[i]);

  }
  num_turns_ = 0;
  total_turns_ = 4 + n_e;

  SDL_Color black = {102,0,0,50};
  
  gM.combat_.initCombat(gM.player_[0]);
  gM.combat_.current_char_ = &gM.player_[0];

  gM.ui_rects_[0].dst_rect_.x = gM.kBoardWidth;
  gM.ui_rects_[0].dst_rect_.y = 0;
  gM.ui_rects_[0].dst_rect_.w = gM.kWindowWidth - gM.kBoardWidth;
  gM.ui_rects_[0].dst_rect_.h = gM.kWindowHeight;
  
  gM.ui_rects_[1].dst_rect_.x = 0;
  gM.ui_rects_[1].dst_rect_.y = gM.kBoardHeight;
  gM.ui_rects_[1].dst_rect_.w = gM.kWindowWidth;
  gM.ui_rects_[1].dst_rect_.h = gM.kWindowHeight - gM.kBoardHeight;
  
  gM.ui_rects_[0].fill_color_ = black;
  gM.ui_rects_[1].fill_color_ = black;

  ent_list.push_back (&gM.ui_rects_[0]);
  ent_list.push_back (&gM.ui_rects_[1]);
  for(int i= 0; i<8; ++i){
    ent_list.push_back(&gM.combat_.stats_text_[i]);
  }
  for(int i = 0; i<6; ++i){
    ent_list.push_back(&gM.combat_.stats_rect_[i]);
  }

  
}
/*
void CombatScene::quit(){
  
  ent_list.clear();
}*/


void CombatScene::input(SDL_Event* eve){

  GameManager& gM = GameManager::Instantiate();
  
  if(eve->type == SDL_KEYDOWN){ 
   
  } 
  if(eve->key.keysym.sym == SDLK_p){
    ++num_turns_%=total_turns_;
    gM.combat_.initCombat(gM.player_[num_turns_]);
    gM.combat_.current_char_ = &gM.player_[num_turns_];
  }
  if(num_turns_<4){
    gM.player_[num_turns_].movCharacterCombat(eve);
  }

  
}

void CombatScene::update(){
  GameManager& gM = GameManager::Instantiate();
  
  gM.player_[num_turns_].updateSpriteC();
  gM.combat_.updateStats();
  //int a = gM.player_[0].mhDistance(&gM.player_[1].dst_rect_);
  
  //printf("distance:%d\n",a);
  
}

void CombatScene::drawImgui(SDL_Renderer* ren){
  
}