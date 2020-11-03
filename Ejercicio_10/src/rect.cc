/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Generic Rect Class implementation

#include "rect.h"

Rect::Rect() {

  transform_.position = {0.0f, 0.0f};
  transform_.rotation = 0.0f;
  transform_.scale = {1.0f, 1.0f};

  width_ = 0.0f;
  height_ = 0.0f;

  for(int i = 0; i < 4; ++i) {

    border_color_[i] = 0xFF;
    fill_color_[i] = 0xFF;

  }

  solid_ = 0;

}

void Rect::init(const float w, const float h){

  width_ = w;
  height_ = h;

}

void Rect::setPosition(const float x, const float y){

  transform_.position.x = x;
  transform_.position.y = y;
  
}

void Rect::setSpeed(const uint8_t s){

  speed_ = s;

}

void Rect::setSolid() {

  solid_ = 1;

}

void Rect::setFillColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {

  fill_color_[0] = r;
  fill_color_[1] = g;
  fill_color_[2] = b;
  fill_color_[3] = a;

}

void Rect::setBorderColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {

  border_color_[0] = r;
  border_color_[1] = g;
  border_color_[2] = b;
  border_color_[3] = a;

}

void Rect::draw(SDL_Renderer* renderer) {

  if(!solid_){

    SDL_Point points[5] = {
            {transform_.position.x, transform_.position.y},
            {transform_.position.x + width_, transform_.position.y},
            {transform_.position.x + width_, transform_.position.y + height_},
            {transform_.position.x, transform_.position.y + height_},
            {transform_.position.x, transform_.position.y}};
    
    SDL_SetRenderDrawColor(renderer, border_color_[0],
                          border_color_[1], border_color_[2],
                          border_color_[3]);                       
    
    SDL_RenderDrawLines(renderer, points, 5);

  }else{

    SDL_Rect r = {transform_.position.x, transform_.position.y, width_, height_};

    SDL_SetRenderDrawColor(renderer, fill_color_[0],
                          fill_color_[1], fill_color_[2],
                          fill_color_[3]);
    SDL_RenderFillRect(renderer, &r);

  }

}
