/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#include "tile.h"
#include "gamemanager.h"

Tile::Tile(){

  state_ = 0;
  type_ = 0;
  dst_rect_.x = 0;
  dst_rect_.y = 0;
  dst_rect_.w = 1;
  dst_rect_.h = 1;
  tag_ = 1;
  enabled_ = 1;

}

Tile::~Tile(){
}

void Tile::init(const SDL_Rect* r, const uint8_t t, const uint8_t s, const int8_t e){

  dst_rect_ = *r;  
  state_ = s;
  type_ = t;
  enabled_ = e;
  texture_ = GameManager::Instantiate().map_texture_;

}
/*
void Tile::draw(SDL_Renderer* ren){
  tile_sprite_.draw(ren);
}*/

void Tile::initSubSprite(){

  snip_rect_.x = type_ * 64;
  snip_rect_.y = state_ * 64;
  snip_rect_.w = 64;
  snip_rect_.h = 64;

}