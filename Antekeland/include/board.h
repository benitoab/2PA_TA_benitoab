/**
 * Antekeland 2077
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include "tile.h"
#include "texture.h"

class Board{  
  public:
    //Constant of procedural generation
    static const unsigned char kBoardSize = 64;
    const unsigned char kNState = 8;
    const float kCellconcentration = 0.55f;

    //Methods
    void initLayer1();
    void initLayer2();
    
    void update0Position();
    void reset0Position();
    //void move0Position(SDL_Event* e);
    
    void drawMap(SDL_Renderer* renderer);
      
    //Atributes
    Tile map_[kBoardSize][kBoardSize]; 
    static int32_t x_origin_;
    static int32_t y_origin_;


};

#endif  // __BOARD_H__