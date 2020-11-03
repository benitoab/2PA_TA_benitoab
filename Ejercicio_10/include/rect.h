/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Generic Rect Class definition
#ifndef __RECT_H__
#define __RECT_H__ 1

#include "entity.h"
#include "SDL.h"

struct Transform {

  JBA::Vector2 position;
  float rotation;
  JBA::Vector2 scale;

};

class Rect : public Entity {

  public:

    Rect();

    void init(const float w, const float h);
    void setPosition(const float x, const float y);
    void setSpeed(const uint8_t s);
    void setSolid();
    void setFillColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    void setBorderColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    void draw(SDL_Renderer* renderer);

    Transform transform_;
    float width_;
    float height_;
    uint8_t speed_;
    uint8_t border_color_[4];  // RGBA
    uint8_t fill_color_[4];    // RGBA
    uint8_t solid_;

};

#endif // __RECT_H__