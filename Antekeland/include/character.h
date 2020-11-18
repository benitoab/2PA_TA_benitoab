/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__ 1 

#include "entity.h"

enum kEnumProfession{
  kEnumProfession_Warrior = 0,
  kEnumProfession_Hunter ,
  kEnumProfession_Rogue ,
  kEnumProfession_Mage ,
  kEnumProfession_Warlock ,
  kEnumProfession_Shepherd  ,
  kEnumProfession_Monster ,
};

class Character : public Entity{

  public :
  Character();
  ~Character();
  
  void init();
  
  void levelUp();
  void updatePosition(); 
  void movCharacter(SDL_Event* e);
  
  uint8_t cell();
  
  void draw(SDL_Renderer* ren);
  
  protected:
  
  RBM::Vec2 velocity;
  
  int32_t hp_;
  int32_t attack_;
  int32_t defense_;
  int32_t movement_;
  int32_t profession_;
  int32_t xp_;
  int32_t level_;

};


#endif  // __CHARACTER_H__