/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Generic Entity Class implementation

#include "entity.h"

Entity::Entity() {

  tag_ = 0;
  enabled_ = 0;

}

void Entity::init() {

  tag_ = 0;
  enabled_ = 0;
  
}

void Entity::setEnable(){

  enabled_ = 1;

}