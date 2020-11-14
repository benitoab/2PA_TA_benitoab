/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__ 1

#include "SDL.h"
#include "texture.h"
#include "board.h"
#include "logic.h"

class GameManager{
  public:  
    //Constant
    static const int kWindowWidth = 800;
    static const int kWindowHeight = 800;    
    static const unsigned char kViewSize = 10;
   
    //Methods  
    ~GameManager();

    //Factory
    static GameManager& Instantiate();
    
    // Atributes
    Board layer1_;
    Board layer2_;     // Graphic map
    Logic board_[Board::kBoardSize][Board::kBoardSize];
    Logic units_[Board::kBoardSize][Board::kBoardSize]; // Logical map
    Texture* map_texture_;
 
  private:
    //Methods
    GameManager();
    static GameManager* instance_gm_;      

};

#endif  // __GAMEMANAGER_H__