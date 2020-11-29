#ifndef __SCENE_H__
#define __SCENE_H__ 1
#include "SDL.h"
#include <iostream> 
#include <list> 


class Entity;

class Scene{
  
  public:
  
  // Methods
  Scene();
  virtual ~Scene();
  
  virtual void init()=0;
  
  virtual void input(SDL_Event* eve)=0;
  virtual void update()=0;
  
  void draw(SDL_Renderer* ren);
  
  //Atributes
  
  //Sustituir por el vector de IA
  std::list <Entity*> ent_list; 
  
  
};

#endif