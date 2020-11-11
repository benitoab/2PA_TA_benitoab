/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */


#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__ 1

#include <SDL.h>
#include "texture.h"
#include "rect.h"
#include "board.h"
#include "label.h"
#include "logic.h"

class GameManager{
  public:  
    //Constant
    static const int kWindowWidth = 640;
    static const int kWindowHeight = 640;    
    static const unsigned char kBoardSize = 64;
    static const unsigned char kViewSize = 64;
   
    //Methods  
    ~GameManager();

    //Factory
    static GameManager* Instantiate();
    
    // Atributes
    Board layer1_, layer2_;     // Graphic map
    Logic board_[kBoardSize][kBoardSize], units_[kBoardSize][kBoardSize]; // Logical map
    Texture map_texture_;
 
  private:
    //Methods
    static GameManager* instance_gm;
    GameManager();
  

};

#endif  // __GAMEMANAGER_H__