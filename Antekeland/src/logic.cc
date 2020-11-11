/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include "logic.h"

Logic::Logic(){

  enabled_ = 1;
  enter_ = 0;

}

Logic::~Logic(){
}

void Logic::set_enabled(const uint8_t e){

  enabled_ = e;

}

uint8_t Logic::enabled(){

  return enabled_;

}

void Logic::set_enter(const uint8_t e){

  enter_ = e;

}

uint8_t Logic::enter(){

  return enter_;

}
