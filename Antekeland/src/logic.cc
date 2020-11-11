/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include "logic.h"

Logic::Logic(){

  enabled_ = nullptr; // Not walkable, 1 = walkable
  enter_ = 0; // Not entereable, 1 = allows to enter

}

Logic::~Logic(){
}

Logic::init(){

  enabled_ = nullptr; // Not walkable, 1 = walkable
  enter_ = 0; // Not entereable, 1 = allows to enter

}