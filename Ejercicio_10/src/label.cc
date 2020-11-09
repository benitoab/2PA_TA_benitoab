/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Label Class implementation

#include "label.h"

Label::Label(){

}

Label::~Label(){

}

void Label::init(const char* src_font, const uint8_t size,
                 const char* msg, SDL_Color color,
                 SDL_Rect dst_rect){

  Label::initFont(src_font, size);

}

void Label::initFont(const char* src_font, uint8_t size){

  font_ = TTF_OpenFont(src_font, size);

  if(!font_){ printf("TTF_OpenFont: %s\n", TTF_GetError()); }

}

void Label::drawText(SDL_Renderer* ren, SDL_Texture* texture,
                     SDL_Rect dst_rect){

  SDL_Surface* text_surface;
