/**
 * Antekeland 2077
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include "SDL.h"
#include "entity.h"
#include "texture.h"

class Sprite : public Entity{
  
  public:  
    //Methods
    Sprite();
    ~Sprite();
    
    void initSprite(const Texture& t,
                    const SDL_Rect* position,
                    const SDL_Rect* snip);
    
    int width();
    int height();

    void set_texture(const Texture& tex);
    
    void draw(SDL_Renderer* ren) override;
    
    //Atributes
    SDL_Rect snip_rect_;

  
    Texture* texture_;
 
};

#endif