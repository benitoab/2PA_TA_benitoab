/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Generic Entity Class definition
#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include "JBAmath.h"
#include "SDL.h"

#include <stdint.h>

class Entity {

  public:
    Entity();
    ~Entity();

    void init();
    void setEnable();

    int32_t tag_;
    uint8_t enabled_;

};

#endif //__ENTITY_H__