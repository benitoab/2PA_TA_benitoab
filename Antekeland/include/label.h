/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/

#ifndef __LABEL_H__
#define __LABEL_H__ 1

#include "SDL.h"
#include "SDL_ttf.h"
#include "entity.h"

class Label: public Entity{
  
  
  public:
  //Methods
  
  Label();
  ~Label();
  
  void init(const char* font_path, uint16_t size, 
            const SDL_Color c, const char* t,
            const SDL_Rect r);
                
  void initFont(const char* font_path, 
                const uint16_t size);
 
  void changeText(const char* t);
  
  void setPosition(const SDL_Rect* r);
  
  void initRect(const int x, const int y,
                const int w, const int h);
  
  void draw(SDL_Renderer* render) override;
  
  void changeColor(const SDL_Color c);
  
  // Atributes
  
  char* text_;
  TTF_Font* font_;
  SDL_Color color_;
  uint16_t size_;
  
  
  
  
};

#endif