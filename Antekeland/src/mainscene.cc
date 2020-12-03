#include "mainscene.h"
#include "gamemanager.h"


MainScene::MainScene(){
  
  //ent_list = nullptr;
  
}

MainScene::~MainScene(){
 // if(nullptr != ent_list){
   // ent_list.clear();
    //ent_list = nullptr;
  //}
}



void MainScene::init(){

  GameManager& gM = GameManager::Instantiate();
  SDL_Color black = {102,0,0,50};
  
  gM.over_world_scene_ = 1;
 
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
  
  // introduce all entities to draw
  
  for(int i = 0; i< Board::kBoardSize; ++i){
    for(int j = 0; j< Board::kBoardSize; ++j){    
      ent_list.push_back(&gM.layer1_.map_[i][j]); 
    }
  }


  ent_list.push_back(&gM.player_[0]);
  
  

  for(int i = 0; i<Board::kBoardSize; ++i){
    for(int j = 0; j<Board::kBoardSize; ++j){
      
      ent_list.push_back(&gM.layer2_.map_[i][j]);
    }
  }
  ent_list.push_back (&gM.ui_rects_[0]);
  ent_list.push_back (&gM.ui_rects_[1]);
  for(int i= 0; i<8; ++i){
    ent_list.push_back(&gM.combat_.stats_text_[i]);
  }
  for(int i = 0; i<6; ++i){
    ent_list.push_back(&gM.combat_.stats_rect_[i]);
  }
 
}

void MainScene::input(SDL_Event* eve){
  
  GameManager::Instantiate().player_[0].movCharacter(eve);
}

void MainScene::update(){
  GameManager& gM = GameManager::Instantiate();
  
  gM.layer1_.reset0Position();
  gM.layer2_.reset0Position();
  
  gM.layer1_.update0Position();
  gM.layer2_.update0Position();
  gM.combat_.updateStats();

  
  
}