/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __TILE_H__  
#define __TILE_H__ 1


#include "sprite.h"

class Tile : public Sprite {

  public:
    // Methods
    Tile();    
    ~Tile();
    /**
     *@brief Init a tile
     *@param const SDL_Rect* r
     *@param const uint8_t t
     *@param const uint8_t s
     *@param const uint8_t e
    */ 
    void init(const SDL_Rect* r, const uint8_t t, const uint8_t s, const int8_t e);
    void initSubSprite(); // To be done when the map is already created
    void draw(SDL_Renderer* ren)override;
    
    //Atributes 
    uint8_t state_;   // Cell State
    uint8_t type_;    // Cell Type
    
    // Inherites SDL_Rect dst_rect_ from Entity
  
};

#endif  // __TILE_H__
