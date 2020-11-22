/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#include <stdio.h>
#include <stdlib.h>
#include "imgui.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "gamemanager.h"

GameManager* GameManager::instance_gm_ = nullptr;

/// @brief Instantiates only one object (Singletone)
GameManager& GameManager::Instantiate(){

  if(nullptr == instance_gm_){ instance_gm_ = new GameManager(); }

  return *instance_gm_;

}

GameManager::GameManager(){
}

GameManager::~GameManager(){  
}

void GameManager::drawBlackRects(SDL_Renderer* ren){
  
  SDL_Rect aux1, aux2;
  
  aux1.x = kBoardWidth;
  aux1.y = 0;
  aux1.w = kWindowWidth - kBoardWidth;
  aux1.h = kWindowHeight;
  //aux1.h = kBoardHeight;
  
  aux2.x = 0;
  aux2.y = kBoardHeight;
  aux2.w = kWindowWidth;
  // aux2.w = kBoardWidth;
  aux2.h = kWindowHeight - kBoardHeight;
  
  SDL_SetRenderDrawColor(ren,0,0,0,255);
  SDL_RenderFillRect(ren,&aux1);
  SDL_RenderFillRect(ren,&aux2);
}