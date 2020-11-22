/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__ 1 

#include "entity.h"


struct Attacks{
  int32_t id;
  int32_t dmg; ///@var damage of the attack
  int32_t mana_cost; ///@var how many mana it costs
  uint8_t range; ///@var the manhatan distance you need to be to use it.
  uint8_t type; ///@var the type of the damage magic(0) or physic(1)
  char* name; ///@var the name of the attack
};

///@brief strcut that store the stats of the characters
struct Character_Stats{
  int32_t hp;
  int32_t mana;
  int32_t physical_att; 
  int32_t magic_att;
  int32_t armor;
  int32_t magic_resist;
  int32_t movement; 
};


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
  
  Attacks char_attacks_[4]; ///@var the info of the character attacks. 0 means no attack
  public:
  
  RBM::Vec2 velocity;
  
  ///@var Stats base of the characters.
  Character_Stats base_;
  ///@var Stats that change during the combat.
  Character_Stats current_;
  
  int32_t profession_;
  int32_t xp_;
  int32_t level_;

};


#endif  // __CHARACTER_H__