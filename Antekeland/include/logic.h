/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Developemtn @ESAT
 */

#ifndef __LOGIC_H__
#define __LOGIC_H__ 1

#include <stdint.h>
#include "gamemanager.h"

class Logic{
  public:
    // Methods
    Logic();
    ~Logic();

    void init();

    // Attributes
    uint8_t* enabled_;
    uint8_t enter_;

};

#endif  // __LOGIC_H__