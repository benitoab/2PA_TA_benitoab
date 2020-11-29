#include "custoscene.h"
#include "gamemanager.h"

CustoScene::CustoScene(){


}

CustoScene::~CustoScene(){
  
}

void CustoScene::init(){
  GameManager& gM = GameManager::Instantiate();
  ent_list.push_back(&gM.bg_custo_);
  
}

void CustoScene::input(SDL_Event* eve){}

void CustoScene::update(){
  
  GameManager& gM = GameManager::Instantiate();
  gM.bg_custo_.update(1);
  
}

