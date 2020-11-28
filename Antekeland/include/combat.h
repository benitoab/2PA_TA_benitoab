/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __COMBAT_H__  
#define __COMBAT_H__ 1
#define _CRT_SECURE_NO_WARNINGS

#include "SDL.h"
#include "label.h"
#include "rect.h"

class Character;


class Combat {

  public:
    Combat();
    ~Combat();
    
    void initCombat(Character& current_char);
    //DrawUI  
    //void drawCombatUI(SDL_Renderer* ren);
    void drawMark(SDL_Renderer* ren);
    void drawAttacks(SDL_Renderer* ren);
    void updateStats();
  
    //Atributes
    Character* current_char_;
    
    Label att_text_[4];
    Label stats_text_[10];
    Rect stats_rect_[6];
    
    SDL_Rect ui_stats_rect_;
    SDL_Rect attacks_rect_;
    float stats_scale_; ///@var scale of the box where the stats are shown
    
    /// @var It represent the character's turn. 0 the first one, 2 the thrid,...
    int32_t turn_;
    ///@var it means in which satge of the turn the character is (moving, attacking,etc)
    uint8_t stage_; 
    /// @var how many units are in the combat. Allais + ennemies.
    uint8_t n_entities_;
    
};

#endif  // __COMBAT_H__
