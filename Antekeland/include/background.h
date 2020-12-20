#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__ 1

#include <stdint.h>
#include "entity.h"

class Texture;

class Background : public Entity{
  
  public:
 
  Background();
  virtual ~Background();
  
  void init(const RBM::Transform2 tr, 
            const uint8_t hs, 
            const uint8_t vs,
            Texture& tex,
            const RBM::Vec2* vel);
                 
  void updateB(float dt);               
  void update(float dt);               
  void draw(SDL_Renderer* ren) override;

  
  uint8_t horizontal_scroll_;
  uint8_t vertical_scroll_;
  RBM::Vec2 velocity_;
  Texture* texture_;  
  
};;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


#endif


