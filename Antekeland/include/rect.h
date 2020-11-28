/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/


#ifndef __RECT_H__
#define __RECT_H__ 1

#include <SDL.h>
#include "entity.h"

class Rect : public Entity{
  
  public:
  
  //Methods
  
  Rect();
  virtual~Rect();
  
  void init()override;
  void init(RBM::Transform2* tr);
  void init(SDL_Rect* r, int32_t t, int8_t e, uint8_t c,
            RBM::Transform2* tr,
            SDL_Color* fc, SDL_Color* bc,
            uint8_t s, int32_t speed, float speedr);
            
  void draw(SDL_Renderer* renderer)override;
  void drawT(SDL_Renderer* renderer);
  
  void horizontalMovement(int w);
  
  void changeColor();
  
  void rotate();
  
  //Atributes
  SDL_Color border_color_;
  SDL_Color fill_color_;
  uint8_t solid_;
  uint8_t centered_;
  int32_t speed_;
  float speed_rot_;
  
};

#endif 