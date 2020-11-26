/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __COMBAT_H__  
#define __COMBAT_H__ 1

#include "SDL.h"
#include "label.h"



class Combat {

  public:
    Combat();
    ~Combat();
    
    void initCombat();
    //DrawCosas  
    void drawMark(SDL_Renderer* ren);
    void drawAttacks(SDL_Renderer* ren);
  
    //Atributes
    Label att_text_[4];
    
    /// @var It represent the character's turn. 0 the first one, 2 the thrid,...
    int32_t turn_;
    ///@var it means in which satge of the turn the character is (moving, attacking,etc)
    uint8_t stage_; 
    /// @var how many units are in the combat. Allais + ennemies.
    uint8_t n_entities_;
    
};

#endif  // __COMBAT_H__
