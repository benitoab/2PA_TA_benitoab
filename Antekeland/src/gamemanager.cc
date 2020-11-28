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
  map_texture_ = nullptr;
  over_world_scene_ = 0;
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


void GameManager::initsAttacks(){
  
  attacks[0].id = 0;
  attacks[0].dmg = 0;
  attacks[0].mana_cost = 0;
  attacks[0].range = 0;
  attacks[0].type = 0;
  attacks[0].name = "nada";
  
  attacks[1].id = 1;
  attacks[1].dmg = 10;
  attacks[1].mana_cost = 0;
  attacks[1].range = 1;
  attacks[1].type = 1;
  attacks[1].name = "Golpe simple";
  
  
  attacks[2].id = 2;
  attacks[2].dmg = 20;
  attacks[2].mana_cost = 5;
  attacks[2].range = 1;
  attacks[2].type = 1;
  attacks[2].name = "Golpe potente";
  
  
  attacks[3].id = 3;
  attacks[3].dmg = 10;
  attacks[3].mana_cost = 5;
  attacks[3].range = 2;
  attacks[3].type = 0;
  attacks[3].name = "Bola de Fuego";
  
  
  attacks[4].id = 4;
  attacks[4].dmg = 20;
  attacks[4].mana_cost = 10;
  attacks[4].range = 2;
  attacks[4].type = 0;
  attacks[4].name = "Ventisca";
  
  
  attacks[5].id = 5;
  attacks[5].dmg = 15;
  attacks[5].mana_cost = 2;
  attacks[5].range = 1;
  attacks[5].type = 1;
  attacks[5].name = "Estocada veloz";
}

