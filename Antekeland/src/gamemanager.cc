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

//Instantiates only one object (Singletone)
GameManager& GameManager::Instantiate(){

  if(nullptr == instance_gm_){ instance_gm_ = new GameManager(); }

  return *instance_gm_;

}

GameManager::GameManager(){
}

GameManager::~GameManager(){  
}