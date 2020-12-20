#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__ 1

#include "scene.h"
#include "label.h"

class Character;

class MenuScene : public Scene{
  
  public:
  
  MenuScene();
  virtual ~MenuScene();
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  void drawImgui(SDL_Renderer* ren) override;
  
  //Atributes

  Label menu_text_[3];
  
};

#endif  // __MENUSCENE_H__