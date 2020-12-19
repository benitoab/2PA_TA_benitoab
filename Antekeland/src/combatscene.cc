#include "stdlib.h"

#include "combatscene.h"
#include "gamemanager.h"

CombatScene::CombatScene(){
  

  
}

CombatScene::~CombatScene(){

}

void CombatScene::init(){

  GameManager& gM = GameManager::Instantiate();

  SDL_Rect r1 = {0, 0, 640, 640};
  
  cave_[0].initSprite(*gM.ground_cave_, &r1, &r1);
  cave_[1].initSprite(*gM.frozen_cave_, &r1, &r1);

  // Init Logic Cave map
  for(int i = 0; i < 16; ++i){
    for(int j = 0; j < 16; ++j){
      if(i == 0 || i == 15 || j == 0 || j == 15){
        logic_board_[i][j].enabled_ = 0;
        logic_board_[i][j].enter_ = 0;
      }
      logic_board_[i][j].init();
      
    }
  }

  if(rand()%10 < 5){
    logic_board_[2][2].enabled_ = 0;
    logic_board_[2][13].enabled_ = 0;
    logic_board_[3][10].enabled_ = 0;
    logic_board_[4][4].enabled_ = 0;
    logic_board_[4][5].enabled_ = 0;
    logic_board_[4][10].enabled_ = 0;
    logic_board_[4][11].enabled_ = 0;
    logic_board_[4][11].enter_ = 3;
    logic_board_[5][4].enabled_ = 0;
    logic_board_[5][10].enabled_ = 0;
    logic_board_[5][11].enabled_ = 0;
    logic_board_[5][12].enabled_ = 0;
    logic_board_[7][7].enabled_ = 0;
    logic_board_[7][8].enabled_ = 0;
    logic_board_[8][7].enabled_ = 0;
    logic_board_[9][5].enabled_ = 0;
    logic_board_[10][5].enabled_ = 0;
    logic_board_[10][11].enabled_ = 0;
    logic_board_[10][12].enabled_ = 0;
    logic_board_[10][13].enabled_ = 0;
    logic_board_[11][3].enabled_ = 0;
    logic_board_[11][4].enabled_ = 0;
    logic_board_[11][5].enabled_ = 0;
    logic_board_[13][9].enabled_ = 0;
    logic_board_[13][12].enabled_ = 1;
    logic_board_[13][12].enter_ = 1;
    logic_board_[14][9].enabled_ = 0;
    ent_list.push_back(&cave_[0]);
  }else{
    logic_board_[2][13].enabled_ = 0;
    logic_board_[2][13].enter_ = 3;
    logic_board_[4][3].enabled_ = 0;
    logic_board_[4][4].enabled_ = 0;
    logic_board_[4][5].enabled_ = 0;
    logic_board_[5][3].enabled_ = 0;
    logic_board_[5][4].enabled_ = 0;
    logic_board_[5][5].enabled_ = 0;
    logic_board_[6][3].enabled_ = 0;
    logic_board_[6][4].enabled_ = 0;
    logic_board_[6][5].enabled_ = 0;
    logic_board_[8][9].enabled_ = 0;
    logic_board_[8][10].enabled_ = 0;
    logic_board_[8][11].enabled_ = 0;
    logic_board_[9][5].enabled_ = 0;
    logic_board_[9][6].enabled_ = 0;
    logic_board_[10][5].enabled_ = 0;
    logic_board_[10][6].enabled_ = 0;
    logic_board_[9][9].enabled_ = 0;
    logic_board_[9][10].enabled_ = 0;
    logic_board_[9][11].enabled_ = 0;
    logic_board_[10][9].enabled_ = 0;
    logic_board_[10][10].enabled_ = 0;
    logic_board_[10][11].enabled_ = 0;
    logic_board_[10][3].enabled_ = 1;
    logic_board_[10][3].enter_ = 1;
    ent_list.push_back(&cave_[1]);
  }

  ent_list.push_back(&gM.player_[0]);
  
}

void CombatScene::input(SDL_Event* eve){
  
  
}

void CombatScene::update(){
  
  
}

void CombatScene::drawImgui(SDL_Renderer* ren){
  
}