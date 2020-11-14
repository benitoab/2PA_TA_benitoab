#include "character.h"
#include "gamemanager.h"
#include "rbmmath.h"

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

uint8_t Character::cell(){

  GameManager& gM = GameManager::Instantiate();
  //sustituir por el ancho del personaje
  int w_tile =  gM.layer1_.map_[0][0].dst_rect_.w;
  int h_tile =  gM.layer1_.map_[0][0].dst_rect_.h;
  
  unsigned char x_c=0, y_c =0;
  
  x_c = RBM::GetMatrixPosition(0,
        RBM::Abs(gM.layer1_.x_origin_)/w_tile);
  y_c = RBM::GetMatrixPosition(0,
        RBM::Abs(gM.layer1_.y_origin_)/h_tile);

  x_c = RBM::GetMatrixPosition(x_c,(gM.kViewSize/2));
  y_c = RBM::GetMatrixPosition(y_c,(gM.kViewSize/2));
  
  /*
  if(gM.layer1.x_origin_ % w_tile < (w_tile/2)){
    
   // x_c = x_c + (gM.kViewSize /2) -1;
    x_c = GetMatrixPosition(x_c,(gM.kViewSize/2) -1);
  }
  else{
    x_c = GetMatrixPosition(x_c,(gM.kViewSize/2));
  }
  
  if(gM.layer1.y_origin_ % h_tile < (h_tile/2)){
    
    y_c = GetMatrixPosition(y_c,(gM.kViewSize/2) -1);
  }
  else{
   y_c = GetMatrixPosition(y_c,(gM.kViewSize/2));
  }
  
  
  */
  
  if( RBM::Abs(gM.layer1_.x_origin_)% w_tile == 0 &&
      RBM::Abs(gM.layer1_.y_origin_)% h_tile == 0){
        
     if(gM.board_[x_c][y_c].enabled_ == 0){
       return false;
     }
        
  }
  
  else{
    if(gM.board_[x_c][y_c].enabled_ == 0 ||
       gM.board_[x_c][RBM::GetMatrixPosition(y_c,1)].enabled_ == 0 ||
       gM.board_[RBM::GetMatrixPosition(x_c,1)][RBM::GetMatrixPosition(y_c,(gM.kViewSize/2))].enabled_ == 0 ||
       gM.board_[RBM::GetMatrixPosition(x_c,1)][y_c].enabled_ == 0){
         
         return false;
    }
  }
  
  return true;
}

void Character::draw(SDL_Renderer* ren){
  SDL_SetRenderDrawColor(ren,0,255,0,255);
  SDL_RenderDrawRect(ren,&dst_rect_);
}