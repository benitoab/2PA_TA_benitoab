#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__ 1

#include "SDL.h"
#include "entity.h"
#include "texture.h"
#include <stdint.h>

class Background : public Entity{
  
  public:
 
  Background();
  ~Background();
  
  void init(const RBM::Transform2 tr, 
            const uint8_t hs, 
            const uint8_t vs,
            Texture& tex,
            const RBM::Vec2* vel);
                 
  void update(float dt);               
  void draw(SDL_Renderer* render);
  //void drawOnly1(SDL_Renderer* render);  
  
  uint8_t horizontal_scroll_;
  uint8_t vertical_scroll_;
  RBM::Vec2 velocity_;
  Texture* texture_;  
  
};;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


#endif


