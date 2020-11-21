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
#include "character.h"
#include "combat.h"

class GameManager{
  public:  
    //Constant
    static const int kWindowWidth = 1024;
    static const int kWindowHeight = 768;
    static const int kBoardWidth = 640;
    static const int kBoardHeight = 640;    
    static const unsigned char kViewSize = 16;
   
    //Methods  
    ~GameManager();
    //It has to be change of .h
    void drawBlackRects(SDL_Renderer* ren);
    //Factory
    static GameManager& Instantiate();
    
    // Atributes
    Board layer1_;
    Board layer2_;     // Graphic map
    Logic board_[Board::kBoardSize][Board::kBoardSize];
    Logic units_[Board::kBoardSize][Board::kBoardSize]; // Logical map
    Character c;
    Texture* map_texture_;
    Combat combat_;
 
  private:
    //Methods
    GameManager();
    static GameManager* instance_gm_;      

};

#endif  // __GAMEMANAGER_H__