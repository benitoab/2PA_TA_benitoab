/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Texture Class implementation

#include "texture.h"

void Texture::init(const char* name) {

  if(nullptr == name) return;

  surface_ = IMG_Load(name);

}

void Texture::load(SDL_Renderer* renderer) {

  texture_ = SDL_CreateTextureFromSurface(renderer, surface_);

}