#include "character.h"
#include "gamemanager.h"
#include "rbmmath.h"
#include <stdio.h>



Character::Character(){
  base_.hp = 100;
  base_.mana = 100;
  base_.physical_att = 10;
  base_.magic_att = 10;
  base_.armor = 10;
  base_.magic_resist = 10;
  base_.movement = 7; 
  
  current_ = base_;
  profession_ = kEnumProfession_Shepherd;
  xp_ = 0;
  level_ = 1;
  
}

Character::~Character(){}

void Character::init(){
  
  base_.hp = 100;
  base_.mana = 100;
  base_.physical_att = 10;
  base_.magic_att = 10;
  base_.armor = 10;
  base_.magic_resist = 10;
  base_.movement = 7; 
  
  current_ = base_;

  profession_ = kEnumProfession_Shepherd;
  xp_ = 0;
  level_ = 1;
  
  char_attacks_[0] = GameManager::Instantiate().attacks[1];
  char_attacks_[1] = GameManager::Instantiate().attacks[2];
  char_attacks_[2] = GameManager::Instantiate().attacks[3];
  char_attacks_[3] = GameManager::Instantiate().attacks[4];

  int32_t* skin_ptr = (int32_t*)&skin_id_;

  for(int i = 2; i < 23; ++i){

    *(skin_ptr+i) = 0;

  }

  skin_id_.gender = 1;
  skin_id_.skin = 1;
  skin_id_.hair_color = 1;
  
}

void Character::levelUp(){}

void Character::updatePosition(){  
}

void Character::movCharacter(SDL_Event* e){
  //Input i compruebo si me puedo mover
  uint8_t can_move = 0;
  int8_t vertical_mov = 0;
  int8_t horizontal_mov = 0;
  
  // siempre me voy a mover de celda si puedo, y si me salgo del rango,
  // tambien movere el tablero.
  GameManager& gM = GameManager::Instantiate();
  //sustituir por el ancho del personaje
  int w_tile =  gM.layer1_.map_[0][0].dst_rect_.w;
  int h_tile =  gM.layer1_.map_[0][0].dst_rect_.h;
  
  
  
  if(e->type == SDL_KEYDOWN){
 
    if(e->key.keysym.sym == SDLK_UP &&
    gM.board_[RBM::GetMatrixPosition(dst_rect_.y,-1)][dst_rect_.x].enabled_ == 1){
      vertical_mov = 1;
      dst_rect_.y = RBM::GetMatrixPosition(dst_rect_.y,-1);
      can_move = 1;
    }
    else if(e->key.keysym.sym == SDLK_DOWN &&
    gM.board_[RBM::GetMatrixPosition(dst_rect_.y,1)][dst_rect_.x].enabled_ == 1){
      vertical_mov = -1;
      dst_rect_.y = RBM::GetMatrixPosition(dst_rect_.y,1);
      can_move = 1;
    }
      
    else if(e->key.keysym.sym == SDLK_LEFT &&
    gM.board_[dst_rect_.y][RBM::GetMatrixPosition(dst_rect_.x,-1)].enabled_ == 1){
      horizontal_mov = 1;
      dst_rect_.x = RBM::GetMatrixPosition(dst_rect_.x,-1);
      can_move = 1;
      
    }
    else if(e->key.keysym.sym == SDLK_RIGHT &&
    gM.board_[dst_rect_.y][RBM::GetMatrixPosition(dst_rect_.x,1)].enabled_ == 1){
      horizontal_mov = -1;
      dst_rect_.x = RBM::GetMatrixPosition(dst_rect_.x,1);
      can_move = 1;
      
    }

    
    printf("Casilla character x:%d y:%d\n",dst_rect_.x, dst_rect_.y );

    if(1 == can_move){
      
      Board::x_origin_ += w_tile * horizontal_mov;
      Board::y_origin_ += h_tile * vertical_mov;
     
    }
    printf(" x:%d y:%d\n",Board::x_origin_, Board::y_origin_ );
  }
  
}

void Character::draw(SDL_Renderer* ren){
  GameManager& gM = GameManager::Instantiate();
  SDL_SetRenderDrawColor(ren,0,255,0,255);
  
  SDL_Rect aux_rect;
  aux_rect = dst_rect_;
  
  aux_rect.x = gM.layer1_.map_[0][0].dst_rect_.w *
               gM.kViewSize/2;
  aux_rect.y = gM.layer1_.map_[0][0].dst_rect_.h *
               gM.kViewSize/2;
  
  SDL_RenderDrawRect(ren,&aux_rect);
  
 /*
  
  aux_rect.x = dst_rect_.x * gM.kWindowWidth/(gM.kViewSize) 
              + 4 + Board::x_origin_;
                   
  aux_rect.y = dst_rect_.y * gM.kWindowHeight/(gM.kViewSize) 
              + 4 + Board::y_origin_;
                    
  
  // SDL_RenderDrawRect(ren,&dst_rect_);*/
  
  
  
}