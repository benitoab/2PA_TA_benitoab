#include "character.h"
#include "gamemanager.h"
#include "rbmmath.h"
#include <stdio.h>



Character::Character(){
  hp_ = 100;
  attack_ = 10;
  defense_ = 10;
  movement_ = 10;
  profession_ = kEnumProfession_Shepherd;
  xp_ = 0;
  level_ = 1;
}

Character::~Character(){}

void Character::init(){
  
  hp_ = 100;
  attack_ = 10;
  defense_ = 10;
  movement_ = 10;
  profession_ = kEnumProfession_Shepherd;
  xp_ = 0;
  level_ = 1;
  
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
     // printf(" w:%d h:%d\n",w_tile, h_tile);
    }
    printf(" x:%d y:%d\n",Board::x_origin_, Board::y_origin_ );
  }
  
}

uint8_t Character::cell(){

  /*GameManager& gM = GameManager::Instantiate();
  //sustituir por el ancho del personaje
  int w_tile =  gM.layer1_.map_[0][0].dst_rect_.w;
  int h_tile =  gM.layer1_.map_[0][0].dst_rect_.h;

  // 4 points of the character
  SDL_Point character_point[4];
  character_point[0] = {dst_rect_.x, dst_rect_.y};
  character_point[1] = {dst_rect_.x + dst_rect_.w, dst_rect_.y};
  character_point[2] = {dst_rect_.x + dst_rect_.w, dst_rect_.y + dst_rect_.h};
  character_point[3] = {dst_rect_.x, dst_rect_.y + dst_rect_.h};

  uint8_t collision = 1;
  
  unsigned char x_c=0, y_c =0;
  
  x_c = RBM::GetMatrixPosition(0,
        (-Board::x_origin_)/w_tile);
  y_c = RBM::GetMatrixPosition(0,
        (-Board::y_origin_)/h_tile);

  if(Board::x_origin_ > 0){
    x_c = RBM::GetMatrixPosition(x_c,(-gM.kViewSize/2)-1);
  }else{
    x_c = RBM::GetMatrixPosition(x_c,(-gM.kViewSize/2));
  }
  if(Board::y_origin_ > 0){
    y_c = RBM::GetMatrixPosition(y_c,(-gM.kViewSize/2)-1);
  }else{
    y_c = RBM::GetMatrixPosition(y_c,(-gM.kViewSize/2));    
  }

  for(int i = -1; i <= 1; ++i){

    for(int j = -1; j <= 1; ++j){

      if(gM.board_[RBM::GetMatrixPosition(y_c, i)][RBM::GetMatrixPosition(x_c, j)].enabled_ == 0){

        //for(int h = 0; i < 4; ++h){

          if(SDL_PointInRect(&character_point[0], &gM.layer1_.map_[RBM::GetMatrixPosition(y_c, i)][RBM::GetMatrixPosition(x_c, j)].dst_rect_)){
            collision = 0;
          }

        //}

      }

    }
  }
  
  // SDL_PointInRect(const SDL_Point* p, const SDL_Rect* r);

  // printf("%d %d\n", x_c, y_c);
  
  return collision;*/
  return 1;
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