#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__ 1

#include "scene.h"
#include "gamemanager.h"

class MainScene : public Scene{
  
  public:
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  
};


#endif