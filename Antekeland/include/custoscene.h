#ifndef __CUSTOSCENE_H__
#define __CUSTOSCENE_H__ 1

#include "scene.h"

class Character;

class CustoScene : public Scene{
  
  public:
  
  CustoScene();
  virtual ~CustoScene();
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  void drawImgui(SDL_Renderer* ren) override;
  
  //Atributes
  
  Character* current_c_;
  
};


#endif