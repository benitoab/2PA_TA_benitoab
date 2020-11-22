#include "combat.h"
#include "gamemanager.h"

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

