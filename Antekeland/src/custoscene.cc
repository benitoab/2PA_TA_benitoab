#include "custoscene.h"
#include "gamemanager.h"

CustoScene::CustoScene(){


}

CustoScene::~CustoScene(){
  
}

void CustoScene::init(SDL_Renderer* ren){
  GameManager& gM = GameManager::Instantiate();
  ent_list.push_back(&gM.bg_custo_);
  InitCustomization(ren);
  
}

void CustoScene::input(SDL_Event* eve){}

void CustoScene::update(Character* c){
  
  GameManager& gM = GameManager::Instantiate();
  gM.bg_custo_.update(1);
  CustomizeCharacter(&c);
  
}

void CustoScene::drawCustomCharacter(SDL_Renderer* ren, Character c){

  DrawCustomization();
  DrawCharacter(ren, c);
  
}

