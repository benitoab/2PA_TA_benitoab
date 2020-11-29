#ifndef __COMBATSCENE_H__
#define __COMBATSCENE_H__ 1

#include "scene.h"

class CombatScene : public Scene{
  
  public:
  
  CombatScene();
  virtual ~CombatScene();
  
  void init() override;
  void input(SDL_Event* eve) override;
  void update() override;
  
  //Atributes
  
};


#endif