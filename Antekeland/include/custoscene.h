#ifndef __CUSTOSCENE_H__
#define __CUSTOSCENE_H__ 1

#include "scene.h"

class CustoScene : public Scene{
  
  public:
  
  CustoScene();
  virtual ~CustoScene();
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  
  //Atributes
  
};


#endif