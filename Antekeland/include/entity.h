/**
 * Antekeland 2077
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <stdint.h>
#include "SDL.h"
#include "RBMmath.h"

class Entity{
  public:
  
  //Methods
  
  Entity();
  Entity(const Entity& e);
  
  ~Entity();
  
  void init();
  void init(const int32_t t, 
            const int8_t e, 
            const RBM::Transform2* tr,
            const SDL_Rect r);
  
  
  void set_position(RBM::Vec2 v);
  RBM::Vec2 position();
  
  void set_rotation(float r);
  float rotation();
  
  void set_scale(RBM::Vec2 v);
  RBM::Vec2 scale();
   
  int32_t id();
  
  //Atributes

  static int32_t next_id_;
  int32_t tag_;
  uint8_t enabled_;
  SDL_Rect dst_rect_;
 
  protected:
  RBM::Transform2 transform_;
  
  private:
  int32_t id_;
};

#endif
