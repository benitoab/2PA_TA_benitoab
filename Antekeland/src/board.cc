/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */
 
#include "board.h"
#include "gamemanager.h"
#include <stdio.h>
#include <stdlib.h>

int32_t Board::x_origin_ = 0;
int32_t Board::y_origin_ = 0;

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
        
      map_[r][c].init(&aux_rect, 50, 0, 1);
      
    }
  }

}

/*
// Move the position of the origin of the draw of the board
void Board::move0Position(SDL_Event* e){
 // vertical_mov_ = 0;
 // horizontal_mov_ = 0;

  if(e->type == SDL_KEYDOWN){
    
    if(e->key.keysym.sym == SDLK_UP ){vertical_mov_ = 1;}
    if(e->key.keysym.sym == SDLK_DOWN){vertical_mov_ = -1;}
    if(e->key.keysym.sym == SDLK_LEFT){horizontal_mov_ = 1;}
    if(e->key.keysym.sym == SDLK_RIGHT){horizontal_mov_ = -1;}

  }
  if(e->type == SDL_KEYUP && 
    (e->key.keysym.sym == SDLK_UP ||
     e->key.keysym.sym == SDLK_DOWN ||
     e->key.keysym.sym == SDLK_LEFT ||
     e->key.keysym.sym == SDLK_RIGHT)){   
    vertical_mov_ = 0;
    horizontal_mov_ = 0;
  }  
}
*/
void Board::reset0Position(){
  GameManager& gM = GameManager::Instantiate();  
  int total_w = (map_[0][0].dst_rect_.w*(kBoardSize));
  int total_h = (map_[0][0].dst_rect_.h*(kBoardSize));
  
  if(x_origin_ > gM.kWindowWidth){
    x_origin_ %= total_w;
  }
  
  else if(y_origin_ > gM.kWindowHeight){
    y_origin_ %= total_h;
  }
  
  else if(x_origin_ < -total_w){
    x_origin_ %= total_w;
  }
  
  else if(y_origin_ < -total_h){
    y_origin_ %= total_h;
  }  
}

// Update Position of the map
void Board::update0Position(){
  
  GameManager& gM = GameManager::Instantiate();
  
  int x = gM.kWindowWidth/kBoardSize * (kBoardSize/gM.kViewSize);
  int y = gM.kWindowHeight/kBoardSize * (kBoardSize/gM.kViewSize);
 /* 
  uint8_t speed = 1;
  
  x_origin_ += speed* horizontal_mov_;
  y_origin_ += speed* vertical_mov_;
  
 
  if(!gM.c.cell()){ 
    x_origin_ -= speed* horizontal_mov_;
    y_origin_ -= speed* vertical_mov_;
  }
  */
  for(int r = 0; r < kBoardSize; ++r){
    for(int c = 0; c < kBoardSize; ++c){
      map_[r][c].dst_rect_.x = c * x + x_origin_;
      map_[r][c].dst_rect_.y = r * y + y_origin_;
    }
  }
}

// Draws the map
void Board::drawMap(SDL_Renderer* renderer){
    
  int diagonal = 0;
  SDL_Rect aux_rect;
  SDL_Texture* map_t = GameManager::Instantiate().map_texture_->texture_;

  for(int r = 0; r < kBoardSize; ++r){
    for(int c = 0; c < kBoardSize; ++c){

      map_[r][c].draw(renderer);
      /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &map_[r][c].dst_rect_);*/

    }
  }  
  
  if(x_origin_ > 0){
    //printf("x_o positiva \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x - map_[r][c].dst_rect_.w*kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y ;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
       
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
    diagonal+=1;
  }  
  
  if(x_origin_ < -map_[0][0].dst_rect_.w){
    //printf("x_o negativa mucho \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x + map_[r][c].dst_rect_.w * kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y ;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
       
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
    diagonal+=10;
  }  
  
  if(y_origin_ > 0){
    //printf("y_o positiva \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x ;
        aux_rect.y = map_[r][c].dst_rect_.y - map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
       
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
    diagonal+=100;
  }  
  
  if(y_origin_ < -map_[0][0].dst_rect_.h){
    //printf("y_o negativa mucho \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x ;
        aux_rect.y = map_[r][c].dst_rect_.y + map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
       
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
    diagonal+=1000;
  }
  
  //DIAGONALS
  
  // upper and left
  if(diagonal == 101){
   // printf("diagonal arriba izq \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x - map_[r][c].dst_rect_.w*kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y - map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
       
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
  }
  
  // botton and left
  else if(diagonal == 1001){
    //printf("diagonal abajo izq \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x - map_[r][c].dst_rect_.w*kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y + map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
     
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
  }
  
  // upper right
  else if(diagonal == 110){
    //printf("diagonal arriba derecha \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x + map_[r][c].dst_rect_.w*kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y - map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
        
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
  }
 
 // bottom right
  else if(diagonal == 1010){
    //printf("diagonal abajo derecha \n");
    for(int r = 0; r < kBoardSize; ++r){
      for(int c = 0; c < kBoardSize; ++c){
        aux_rect.x = map_[r][c].dst_rect_.x + map_[r][c].dst_rect_.w*kBoardSize;
        aux_rect.y = map_[r][c].dst_rect_.y + map_[r][c].dst_rect_.h * kBoardSize;
        
        aux_rect.w = map_[r][c].dst_rect_.w;
        aux_rect.h = map_[r][c].dst_rect_.h;
        
        SDL_RenderCopy(renderer, map_t, 
                       &map_[r][c].snip_rect_, &aux_rect);
      }
    }
  }
}