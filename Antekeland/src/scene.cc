#include "scene.h"

#include "entity.h"

Scene::Scene(){
}

Scene::~Scene(){}

void Scene::draw(SDL_Renderer* ren){
  
  for each(Entity* aux_ent in  ent_list){
    aux_ent->draw(ren);
    //printf("JAvie no me deja trabaja");
  }

}