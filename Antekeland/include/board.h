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
#include "gamemanager.h"

using namespace GameManager;

//Constant of procedural generation
const float kCellconcentration = 0.55f;
const int kChanceToMove = 721;
const unsigned char kSearchRange = (kBoardSize/4)*3;
const unsigned char kNState = 7;

class Board{  
  public:  
    //Methods
    void initLayer1(const int window_w, const int window_h);
    void initLayer2(const int window_w, const int window_h);
    void drawMap(SDL_Renderer* renderer);
      
    //Atributes
    Tile map_[kBoardSize][kBoardSize];
    Texture map_texture_;

};

#endif  // __BOARD_H__