#ifndef __CUSTOSCENE_H__
#define __CUSTOSCENE_H__ 1

#include "scene.h"
#include "SDL.h"
#include "character.h"

class CustoScene : public Scene{
  
  public:
  
  CustoScene();
  virtual ~CustoScene();
  
  void init(SDL_Renderer* ren) override;
  void input(SDL_Event* eve) override;
  void update(Character* c) override;
  void drawCustomCharacter(SDL_Renderer* ren, Character c);
  
  //Atributes
  
};


#endif