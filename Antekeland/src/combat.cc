#include "combat.h"
#include "gamemanager.h"
#include <stdio.h>


Combat::Combat(){
  turn_ = 0;
  stage_ = 0;
  n_entities_ = 0;
}

Combat::~Combat(){}

void Combat::drawMark(SDL_Renderer* ren){
  
  GameManager& gM = GameManager::Instantiate();
  SDL_Rect mark_rect[8];
  int aux = gM.layer1_.map_[0][0].dst_rect_.w *gM.kViewSize/2;
  
  int w = 10, h = 10;
  
  mark_rect[0].x = aux - w;
  mark_rect[0].y = aux - h;
  mark_rect[0].w = gM.c.dst_rect_.w + w;
  mark_rect[0].h = h;
  
  mark_rect[1].x = aux + gM.c.dst_rect_.w;
  mark_rect[1].y = aux - h;
  mark_rect[1].w = w;
  mark_rect[1].h = gM.c.dst_rect_.h + h;
 
  mark_rect[2].x = aux;
  mark_rect[2].y = aux + gM.c.dst_rect_.h;
  mark_rect[2].w = gM.c.dst_rect_.w + w;
  mark_rect[2].h = h;
  
  mark_rect[3].x = aux - w;
  mark_rect[3].y = aux;
  mark_rect[3].w = w;
  mark_rect[3].h = gM.c.dst_rect_.h + h;
  
  SDL_SetRenderDrawColor(ren, 255,0,0,255);
  SDL_RenderFillRects(ren,mark_rect,4);
  
}


void Combat::initCombat(){
  
  GameManager& gM = GameManager::Instantiate();
  
  
  stats_scale_ = 1;
  stats_rect_.x = gM.kBoardWidth;
  stats_rect_.y = 0;
  stats_rect_.w = stats_scale_ * 
                  (gM.kWindowWidth - gM.kBoardWidth);
  stats_rect_.h = stats_scale_ * 
                  (gM.kWindowHeight - gM.kBoardHeight);
  
  SDL_Color white = {255,255,255,255};
  SDL_Rect aux_rect;
  aux_rect.x = 0;
  aux_rect.y = gM.kBoardHeight;
  aux_rect.w = 200;
  aux_rect.h = 50;
  
  att_text_[0].init("../data/fonts/combat.otf",25,white,
                    gM.c.char_attacks_[0].name,aux_rect);
  aux_rect.x = 200;
  aux_rect.y = gM.kBoardHeight;
  
  att_text_[1].init("../data/fonts/combat.otf",25,white,
                    gM.c.char_attacks_[1].name,aux_rect);               

  aux_rect.x = 0;
  aux_rect.y = gM.kBoardHeight+50;
  
  att_text_[2].init("../data/fonts/combat.otf",25,white,
                    gM.c.char_attacks_[2].name,aux_rect);

  aux_rect.x = 200;
  aux_rect.y = gM.kBoardHeight+50;
  
  att_text_[3].init("../data/fonts/combat.otf",25,white,
                    "el zumo de naranja lleva mucha azucar xdddddddddddddddd",aux_rect); 

  aux_rect.x = stats_rect_.x + stats_scale_ * 40;
  aux_rect.y = stats_rect_.y + stats_scale_ * 200;
  aux_rect.w = stats_scale_ * 50;
  aux_rect.h = stats_scale_ * 25;
 
  stats_text_[0].init("../data/fonts/combat.otf",stats_scale_ *25,
                      white,"HP:", aux_rect);
                      
  aux_rect.y += stats_scale_ * 40;                   
  stats_text_[1].init("../data/fonts/combat.otf",stats_scale_ *25,
                      white,"Mana:", aux_rect);

}

void Combat::drawAttacks(SDL_Renderer* ren){
  
  att_text_[0].drawText(ren);
  att_text_[1].drawText(ren);
  att_text_[2].drawText(ren);
  att_text_[3].drawText(ren);
  
  
}

void Combat::drawStats(SDL_Renderer* ren, 
                        Character& aux_char){
  //HP
  
  float hp_percentage = 1;
  SDL_Rect grey_rect, hp_rect;
  GameManager& gM = GameManager::Instantiate();
  
  grey_rect.x = stats_text_[0].dst_rect_.x + stats_scale_*60;
  grey_rect.y = stats_text_[0].dst_rect_.y+7 * stats_scale_;
  grey_rect.w = 150 * stats_scale_;
  grey_rect.h = 15 * stats_scale_;
  
  hp_rect = grey_rect;
  
  hp_percentage = ((float)aux_char.current_.hp / 
                   (float)aux_char.base_.hp);  
  stats_text_[0].drawText(ren);                   
  SDL_SetRenderDrawColor(ren, 170,170,170,170);
  SDL_RenderFillRect(ren,&grey_rect);
  hp_rect.w = (int)(hp_percentage * grey_rect.w);
  
  SDL_Color hp_color;
  
    hp_color.b = 0;
    hp_color.a = 255;
    
  if(hp_percentage >= 0.85){
    hp_color.r = 0;
    hp_color.g = 255;
  }
  else if(0.85 > hp_percentage && hp_percentage > 0.6){
    hp_color.r = 123;
    hp_color.g = 255;
  }
  else if(0.6 >= hp_percentage && hp_percentage >= 0.4){
    hp_color.r = 255;
    hp_color.g = 255;
  }
  else if(0.4 > hp_percentage && hp_percentage > 0.15){
    hp_color.r = 255;
    hp_color.g = 123;
  }
  else{
    hp_color.r = 255;
    hp_color.g = 0;
  }
  
  SDL_SetRenderDrawColor(ren, hp_color.r, hp_color.g, 
                         hp_color.b, hp_color.a);
  SDL_RenderFillRect(ren,&hp_rect);
  
  
  //MANA
  
  grey_rect.y = stats_text_[1].dst_rect_.y+7 * stats_scale_;
 
  hp_rect = grey_rect;
  
  hp_percentage = ((float)aux_char.current_.mana / 
                   (float)aux_char.base_.mana);  
  stats_text_[1].drawText(ren);   
  SDL_SetRenderDrawColor(ren, 170,170,170,170);
  SDL_RenderFillRect(ren,&grey_rect);
  hp_rect.w = (int)(hp_percentage * grey_rect.w);

  SDL_SetRenderDrawColor(ren,0,105,255,hp_color.a);
  SDL_RenderFillRect(ren,&hp_rect);
 
}






