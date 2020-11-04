/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Texture Class implementation

#include "texture.h"
Texture::Texture(){
  name_ = nullptr;
}

Texture::~Texture(){
  SDL_DestroyTexture(texture_);
  SDL_DestroySurface(surface_);
}

void Texture::init(const char* name) {

  if(nullptr == name) return;

  surface_ = IMG_Load(name);

}

void Texture::load(SDL_Renderer* renderer) {

  texture_ = SDL_CreateTextureFromSurface(renderer, surface_);

}