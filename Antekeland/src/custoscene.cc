#include "custoscene.h"
#include "gamemanager.h"
#include "customization.h"
CustoScene::CustoScene(){


}

CustoScene::~CustoScene(){
  
}

void CustoScene::init(){
  GameManager& gM = GameManager::Instantiate();
  ent_list.push_back(&gM.bg_custo_);
  InitCustomization();
  
}

void CustoScene::input(SDL_Event* eve){}

void CustoScene::update(){
  
  GameManager& gM = GameManager::Instantiate();
  gM.bg_custo_.update(1);
  CustomizeCharacter(&gM.player_[0]);
  
}



void CustoScene::drawImgui(SDL_Renderer* ren){
  GameManager& gM = GameManager::Instantiate();
  DrawCustomization();
  DrawCharacter(ren, gM.player_[0]);
}
