/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */
 
#include "board.h"
#include "gamemanager.h"

#include <stdlib.h>

// Initializes the Layer 1
void Board::initLayer1(){

  GameManager& gM = GameManager::Instantiate();

  SDL_Rect aux_rect;  // Storages the info to init every tile of the board
  int x = gM.kWindowWidth/kBoardSize * (kBoardSize/gM.kViewSize);
  int y = gM.kWindowHeight/kBoardSize * (kBoardSize/gM.kViewSize);
  
  for(int r = 0; r < kBoardSize; ++r){
    for(int c = 0; c < kBoardSize; ++c){

      aux_rect = {c*x, r*y, x, y};
      
      if(rand()%100 <= kCellconcentration * 100){
        
        map_[r][c].init(&aux_rect, 0, rand()%kNState+1, 1);

      }else{

        map_[r][c].init(&aux_rect, 0, 0, 1);

      }
    }
  }

}

// Initializes the Layer 2
void Board::initLayer2(){

  GameManager& gM = GameManager::Instantiate();

  SDL_Rect aux_rect;  // Storages the info to init every tile of the board
  int x = gM.kWindowWidth/kBoardSize * (kBoardSize/gM.kViewSize);
  int y = gM.kWindowHeight/kBoardSize * (kBoardSize/gM.kViewSize);
  
  for(int r = 0; r < kBoardSize; ++r){
    for(int c = 0; c < kBoardSize; ++c){

      aux_rect = {c*x, r*y, x, y};
        
      map_[r][c].init(&aux_rect, 43, 0, 1);
      
    }
  }
}

// Draws the map
void Board::drawMap(SDL_Renderer* renderer){
    
  for(int r = 0; r < kBoardSize; ++r){
    for(int c = 0; c < kBoardSize; ++c){

      map_[r][c].draw(renderer);

    }
  }

}