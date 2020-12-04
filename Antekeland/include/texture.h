/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include "SDL.h"
#include <stdint.h>

class Texture{
  public: 
    static const int32_t kMaxTextures = 100;
    
    //Methods 
    ~Texture();
    
    int loadTexture(const char* img_path, SDL_Renderer* r);
    
    //void loadTexture(int32_t width, int32_t height, uint8_t* data );
    int32_t width();
    int32_t height();
    
    //Factory
    static Texture* CreateTexture(const char* img_path,
                           SDL_Renderer* r);
  
  //Atributes
  SDL_Texture* texture_;
  
  private:
    static int32_t total_textures_;
    Texture();

};

#endif  // __TEXTURE_H__