#ifndef __COMBATSCENE_H__
#define __COMBATSCENE_H__ 1

#include "scene.h"
#include "sprite.h"
#include "logic.h"
#include "rect.h"
#include "label.h"

class CombatScene : public Scene{
  
  public:
  
    CombatScene();
    virtual ~CombatScene();
    
    void init() override;
    void input(SDL_Event* eve) override;
    void update() override;
    void drawImgui(SDL_Renderer* ren) override;
    //void quit()override;
  
  //Atributes

    Rect combat_button_[4];
    Label actions_text_[4];
    unsigned char attacking_;   // 0 = not attacking; 1 = attacking.

    Sprite cave_[2];
    int16_t num_turns_; // [0, 3] = Characters, >3 = IA
    unsigned char current_character_;
    unsigned char total_turns_;
    
  
};


#endif