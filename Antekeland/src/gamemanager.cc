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
  bg_texture_ = nullptr;
  ground_cave_ = nullptr;
  frozen_cave_ = nullptr;
  over_world_scene_ = 0;
  current_edit_ = 0;
  new_game_ = 0;
}

GameManager::~GameManager(){  
}



void GameManager::init(SDL_Renderer* ren){
  
  map_texture_ = Texture::CreateTexture("../data/resources/tileset.png", ren);
  bg_texture_ = Texture::CreateTexture("../data/resources/bgc.png", ren);
  ground_cave_ = Texture::CreateTexture("../data/resources/ground_cave.png", ren);
  frozen_cave_ = Texture::CreateTexture("../data/resources/frozen_cave.png", ren);
  
  for(int i = 0; i<44; ++i){
    textures_[i] = Texture::CreateEmptyTexture();
    /*textures_[i] = Texture::CreateTexture(
    "../data/skins/body/male/body1.png",ren);*/
  }
   
}