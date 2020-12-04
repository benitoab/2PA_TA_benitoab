#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__ 1

#include "scene.h"

class MainScene : public Scene{
  
  public:
  
  MainScene();
  virtual ~MainScene();
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  void drawImgui(SDL_Renderer* ren) override;
  
};


#endif