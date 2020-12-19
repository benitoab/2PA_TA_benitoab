#ifndef __COMBATSCENE_H__
#define __COMBATSCENE_H__ 1

#include "scene.h"
#include "sprite.h"
#include "logic.h"

class CombatScene : public Scene{
  
  public:
  
    CombatScene();
    virtual ~CombatScene();
    
    void init() override;
    void input(SDL_Event* eve) override;
    void update() override;
    void drawImgui(SDL_Renderer* ren) override;
  
  //Atributes

    Sprite cave_[2];
    unsigned char num_turns_; // [0, 3] = Characters, >3 = IA
    unsigned char current_character_;

    Logic logic_board_[16][16];
  
};


#endif