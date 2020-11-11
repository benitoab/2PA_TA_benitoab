/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#include "tile.h"

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
  type_ = t;
  state_ = s;
  enabled_ = e;

}

void Tile::initSubSprite(){

  sprite_.snip_rect_.x = type_ * 64;
  sprite_.snip_rect_.y = state_ * 64;
  sprite_.snip_rect_.w = 64;
  sprite_.snip_rect_.w = 64;

}
