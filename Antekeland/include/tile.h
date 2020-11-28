/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __TILE_H__  
#define __TILE_H__ 1

#include "SDL.h"
#include "sprite.h"

class Tile : public Sprite {

  public:
    // Methods
    Tile();    
    ~Tile();

    void init(const SDL_Rect* r, const uint8_t t, const uint8_t s, const int8_t e);
    void initSubSprite(); // To be done when the map is already created
    //void draw(SDL_Renderer* ren)override;
    
    //Atributes 
   // Sprite tile_sprite_;
    uint8_t state_;   // Cell State
    uint8_t type_;    // Cell Type
    
    // Inherites SDL_Rect dst_rect_ from Entity
  
};

#endif  // __TILE_H__
