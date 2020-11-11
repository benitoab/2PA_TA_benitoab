/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __TILE_H__  
#define __TILE_H__ 1

#include "SDL.h"
#include "entity.h"
#include "sprite.h"

class Tile : public Entity {

  public:
    // Methods
    Tile();    
    ~Tile();

    void init();
    void initSubSprite();
  
    //Atributes  
    uint8_t state_;   // Cell State
    uint8_t type_;    // Cell Type
    
    Sprite sprite_;
    // Inherites SDL_Rect dst_rect_ from Entity
  
};

#endif  // __TILE_H__
