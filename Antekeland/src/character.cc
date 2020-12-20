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
  char_id_ = 0;
  
}

Character::~Character(){}



void Character::init(){
  
  GameManager& gM = GameManager::Instantiate(); 
/*
  base_.hp = 100;
  base_.mana = 100;
  base_.physical_att = 10;
  base_.magic_att = 10;
  base_.armor = 10;
  base_.magic_resist = 10;
  base_.movement = 7; 
  */
  profession_ = kEnumProfession_Warrior;
 
  base_ = *(gM.data_base_.p_[profession_]);
  current_ = base_;

  xp_ = 0;
  level_ = 1;
  char_id_ = 0;

  int32_t* skin_ptr = (int32_t*)&skin_id_;

  for(int i = 2; i < 23; ++i){

    *(skin_ptr+i) = 0;

  }

  skin_id_.gender = 1;
  skin_id_.skin = 1;
  skin_id_.hair_color = 1;
    for(int i=0; i<11; ++i){
    previous_movs_[i]=-1;
  }
  
  index_mov_=0;
}

void Character::init(int prof, unsigned char id){
  
  GameManager& gM = GameManager::Instantiate(); 
  profession_ = prof;
 
  base_ = *(gM.data_base_.p_[profession_]);
  current_ = base_;

  xp_ = 0;
  level_ = 1;
  
  int32_t* skin_ptr = (int32_t*)&skin_id_;

  for(int i = 2; i < 23; ++i){

    *(skin_ptr+i) = 0;

  }

  skin_id_.gender = 1;
  skin_id_.skin = 1;
  skin_id_.hair_color = 1;
  for(int i=0; i<11; ++i){
    previous_movs_[i]=-1;
  }
  
  index_mov_=0;
}




void Character::levelUp(){}

void Character::updatePosition(){ 



}


bool Character::CheckPreviousMovs(const int next_pos_x, 
                                  const int next_pos_y){
  
  int i = index_mov_-1;
  bool end = false;
  int aux_mov_cost = 0;
 
  while(i>=0 && !end){
    //aux_mov_cost += board[*(chara->previous_movs + i)].movement_cost;
    aux_mov_cost += 1;
    if((previous_movs_[i]) == next_pos_y * 16+ next_pos_x){
      current_.movement += aux_mov_cost;
      index_mov_ = i;
      end = true;
    }
    --i;
  }
  return end;
}

/**
  * @brief Tells if you can move to a position
  * @param next_pos_x x coordinate of the next tile 
  * @param next_pos_y y coordinate of the next tile 
  * @return true if you can move, otherwise false.
  */

bool Character::CheckBeforeMove(const int next_pos_x, 
                                const int next_pos_y){
  
  GameManager& gM = GameManager::Instantiate();
  int m_cost = 1;
  //const int m_cost = board[next_pos].movement_cost;
  if(gM.logic_board_[next_pos_y][next_pos_x].enabled_ == 1){
    m_cost = 1;
  }else{
    m_cost = 1234567890;
  }
  
  //printf("coste : %d\n", m_cost);
  //printf("movs_res : %d\n", chara->n_movement);
  if(CheckPreviousMovs(next_pos_x, next_pos_y)){
    return true;
  }
  
  
  if(m_cost <= current_.movement){
    index_mov_++;
    current_.movement -=m_cost;
    return true;
  }
  return false;

}


void Character::movCharacterCombat(SDL_Event* e){
  
  int next_up = RBM::GetMatrixPosition(dst_rect_.y,-1);
  int next_down = RBM::GetMatrixPosition(dst_rect_.y,1);
  int next_right = RBM::GetMatrixPosition(dst_rect_.x,1);
  int next_left = RBM::GetMatrixPosition(dst_rect_.x,-1);
  
  if(e->type == SDL_KEYDOWN){
   
   
    // printf("pulso: %d,%d\n",dst_rect_.x, dst_rect_.y);
    // printf("pulso: %d,%d,%d,%d\n\n",next_up,next_down,next_right,next_right);
    if(e->key.keysym.sym == SDLK_UP &&
    CheckBeforeMove(dst_rect_.x, next_up)){
      
      dst_rect_.y = next_up;
      previous_movs_[index_mov_] = next_up * 16 + dst_rect_.x;
      // printf("%d\n",previous_movs_[index_mov_]);
    }
    
    if(e->key.keysym.sym == SDLK_DOWN &&
    CheckBeforeMove(dst_rect_.x, next_down)){
      
      dst_rect_.y = next_down;
      previous_movs_[index_mov_] = next_down * 16 + dst_rect_.x; 
      // printf("%d\n",previous_movs_[index_mov_]);
    }
    
    if(e->key.keysym.sym == SDLK_RIGHT &&
    CheckBeforeMove(next_right, dst_rect_.y)){
      
      dst_rect_.x = next_right;
      previous_movs_[index_mov_] = dst_rect_.y * 16 + next_right; 
      // printf("%d\n",previous_movs_[index_mov_]);
    }
    
    if(e->key.keysym.sym == SDLK_LEFT &&
    CheckBeforeMove(next_left, dst_rect_.y)){

      dst_rect_.x = next_left;
      previous_movs_[index_mov_] = dst_rect_.y * 16 + next_left; 
      // printf("%d\n",previous_movs_[index_mov_]);
    } 
  }
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

    
   // printf("Casilla character x:%d y:%d\n",dst_rect_.x, dst_rect_.y );

    if(1 == can_move){
      
      Board::x_origin_ += w_tile * horizontal_mov;
      Board::y_origin_ += h_tile * vertical_mov;
     
    }
    //printf(" x:%d y:%d\n",Board::x_origin_, Board::y_origin_ );
  }
  
}

void Character::draw(SDL_Renderer* ren){
  GameManager& gM = GameManager::Instantiate();
  //SDL_SetRenderDrawColor(ren,0,255,0,255);
  
  SDL_Rect aux_rect;
  aux_rect = dst_rect_;
  if(gM.over_world_scene_==1){
  aux_rect.x = gM.layer1_.map_[0][0].dst_rect_.w *
               gM.kViewSize/2;
  aux_rect.y = gM.layer1_.map_[0][0].dst_rect_.h *
               gM.kViewSize/2;
               
  }
  else{
    
    aux_rect.x = aux_rect.w *dst_rect_.x;             
    aux_rect.y = aux_rect.h *dst_rect_.y; 
    
    SDL_Rect aux_rect2;
    SDL_SetRenderDrawColor(ren,255,0,0,1);

    for(int i=0; i<= index_mov_; ++i){
      aux_rect2.w = 40; 
      aux_rect2.h = 40;
      aux_rect2.x = 40 * (previous_movs_[i]%16);
      aux_rect2.y = 40 * (previous_movs_[i]/16); 
      SDL_RenderDrawRect(ren,&aux_rect2); 
    }
  }    
  SDL_SetRenderDrawColor(ren,0,255,0,255);
  SDL_RenderDrawRect(ren,&aux_rect);/*
  SDL_Rect aux_rect2;
  SDL_SetRenderDrawColor(ren,255,0,0,1);
  for(int i=0; i<= index_mov_; ++i){
    aux_rect2.w = aux_rect.w; 
    aux_rect2.h = aux_rect.h;
    aux_rect2.x = 40 * previous_movs_[i]%16;
   
    aux_rect2.y = 40 * previous_movs_[i]/16;
    printf("\nCasilla:%d",previous_movs_[i]);
    printf("x:%d p:%d", aux_rect2.x,previous_movs_[i]%16);
    printf("y:%d p:%d\n", aux_rect2.y,previous_movs_[i]/16);
    SDL_RenderDrawRect(ren, &aux_rect2);
  }*/
  
 /*
  
  aux_rect.x = dst_rect_.x * gM.kWindowWidth/(gM.kViewSize) 
              + 4 + Board::x_origin_;
                   
  aux_rect.y = dst_rect_.y * gM.kWindowHeight/(gM.kViewSize) 
              + 4 + Board::y_origin_;
                    
  
  // SDL_RenderDrawRect(ren,&dst_rect_);*/
  
  
  
}