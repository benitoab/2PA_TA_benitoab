/**
 * Antekeland 2077
 * Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
 * Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__ 1 

#include "entity.h"
#include "sprite.h"
#include "database.h"

struct SkinsCustomization{

  int32_t gender;         /** @var Defines whether it's male (1) or female (2) */
  int32_t skin;           /** @var ID of the skin */
  int32_t hair;           /** @var ID of the hair */
  int32_t hair_color;     /** @var ID of the hair color */
  int32_t eyes;           /** @var ID of the eyes */
  int32_t ears;           /** @var ID of the ears */
  int32_t nose;           /** @var ID of the nose */  
  int32_t beard;          /** @var ID of the beard */
  int32_t mustache;       /** @var ID of the mustache */
  int32_t mustache_color; /** @var ID of the mustache */
  int32_t torso;          /** @var ID of the torso */
  int32_t cape;           /** @var ID of the cape */
  int32_t legs;           /** @var ID of the legs */

  int32_t head;           /** @var ID of the helmet/hat */
  int32_t neck;           /** @var ID of the necklace */
  int32_t belt;           /** @var ID of the belt */
  int32_t armor;          /** @var ID of the armor/shirt/dress */
  int32_t back;           /** @var ID of the back */
  int32_t bracelets;      /** @var ID of the bracelets */
  int32_t bracers;        /** @var ID of the bracers */
  int32_t gloves;         /** @var ID of the gloves */
  int32_t pants;          /** @var ID of the pants */
  int32_t feet;           /** @var ID of the boots/shoes */

};

enum kEnumProfession{

  kEnumProfession_Warrior = 0,
  kEnumProfession_Sorceress ,
  kEnumProfession_Berserker ,
  kEnumProfession_Valkyrie ,
  kEnumProfession_Mage ,
  kEnumProfession_Darkknight ,
  kEnumProfession_Archer ,
  kEnumProfession_Guardian ,
  kEnumProfession_Hashashin ,
  kEnumProfession_Healer ,
  kEnumProfession_Hunter , 
  kEnumProfession_Shepherd  ,
  kEnumProfession_Monster ,

};

class Character : public Entity{

  public :
  Character();
  ~Character();
  
  void init() override;
  void init(int prof, unsigned char id) ;
  
  void cpyCharacter(Character& c);
  
  void levelUp();
  void updateSpriteC(); 
  
  bool CheckBeforeMove(const int next_pos_x, 
                       const int next_pos_y);
  bool CheckPreviousMovs(const int next_pos_x, 
                         const int next_pos_y);                     
  void movCharacter(SDL_Event* e);
  void movCharacterCombat(SDL_Event* e);
  
  uint8_t cell();
  
  void draw(SDL_Renderer* ren) override;

  char name_[32] = "";
  char name2_[32] = "";
  
  AttacksData char_attacks_[4]; ///@var the info of the character attacks. 0 means no attack
  public:
  
    ///@var base_ Base stats of the characters.
    Character_Stats base_;
    ///@var current_ Current stats that change over the combat.
    Character_Stats current_;

    unsigned char char_id_;    
    
    int32_t profession_;
    int32_t xp_;
    int32_t level_;
    int32_t direction_;
    
    int32_t previous_movs_[11];
    int32_t index_mov_;
    
    SkinsCustomization skin_id_;      /** @var Storages all the skins used for every character */

    Sprite skin_[7];                  /** @var Manages the skin customization */
    Sprite outfit_[10];               /** @var Manages the outfit customization */

    unsigned char turn_completed_;    /** @var turn_completed_ Identifies whether the turn has been completed by the character. 0 = uncompleted, 1 = completed */

};

#endif  // __CHARACTER_H__