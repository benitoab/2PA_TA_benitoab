/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Label Class definition
#ifndef __LABEL_H__
#define __LABEL_H__ 1

#include "entity.h"

#include "SDL.h"
#include "SDL_ttf.h"

class Label : public Entity {

  public:
    // Methods
    Label();
    ~Label();
    
    void init(const char* src_font, const uint8_t size,
              const char* msg, SDL_Color color,
              SDL_Rect dst_rect);
    void initFont(const char* src_font, uint8_t size);
    void drawText(SDL_Renderer* ren, SDL_Texture* texture,
                  SDL_Rect dst_rect);

    // Attributes
    char* message_;
    TTF_Font* font_;
    SDL_Color color_;
    uint8_t size_;
    SDL_Rect dst_rect_;
}
