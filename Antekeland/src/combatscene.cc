#include "stdlib.h"

#include "combatscene.h"
#include "gamemanager.h"
#include <stdlib.h>


CombatScene::CombatScene(){
  
  num_turns_ = 0;
  current_character_ = 0;
  total_turns_ = 0;
}

CombatScene::~CombatScene(){

}

void CombatScene::init(){

  attacking_ = 0;

  GameManager& gM = GameManager::Instantiate();
  gM.over_world_scene_=0;
  SDL_Rect r1 = {0, 0, 640, 640};
  
  cave_[0].initSprite(*gM.ground_cave_, &r1, &r1);
  cave_[1].initSprite(*gM.frozen_cave_, &r1, &r1);

  // Init Logic Cave map
  for(int i = 0; i < 16; ++i){
    for(int j = 0; j < 16; ++j){
      if(i == 0 || i == 15 || j == 0 || j == 15
        ||i == 1 || j == 14|| j == 1){ 
        gM.logic_board_[i][j].enabled_ = 0;
        gM.logic_board_[i][j].enter_ = 0;
        gM.units_board_[i][j].enabled_ = 255;        
      }else{
        gM.logic_board_[i][j].init();
        gM.units_board_[i][j].enabled_ = 255;
      }
      
    }
  }
  
  if(rand()%10 < 5){
    gM.logic_board_[13][12].enabled_ = 1;
    gM.logic_board_[13][12].enter_ = 1;
    ent_list.push_back(&cave_[0]);
  }else{
    gM.logic_board_[10][3].enabled_ = 1;
    gM.logic_board_[10][3].enter_ = 1;
    ent_list.push_back(&cave_[1]);
  }

  //Init  Enemies
  
  int n_e = rand()%5+2,x = 0, y = 0;
  
  for(int i= 0; i < n_e; ++i){
    gM.NPC_[i].initEnemy((rand()%5)+1, i+4);
    //Give initial pos
    do{
      x = rand()%16, y = rand()%3+2;
    }while(gM.logic_board_[y][x].enabled_ == 0
        || gM.units_board_[y][x].enabled_ != 255);
    gM.NPC_[i].dst_rect_.x = x;
    gM.NPC_[i].dst_rect_.y = y;
    gM.NPC_[i].dst_rect_.w = 40;
    gM.NPC_[i].dst_rect_.h = 40;
    gM.NPC_[i].generate_mov_ = 1;
    gM.units_board_[y][x].enabled_= i+4;
    
    ent_list.push_back(&gM.NPC_[i]);

  }
  
  for(int i= 0; i < 4; ++i){
    //Give initial pos
    
    do{
      x = rand()%16, y = rand()%3+11;
    }while(gM.logic_board_[y][x].enabled_ == 0
        || gM.units_board_[y][x].enabled_ != 255);
        
    gM.units_board_[y][x].enabled_= i;
    gM.player_[i].dst_rect_.x = x;
    gM.player_[i].dst_rect_.y = y;
    gM.player_[i].dst_rect_.w = 40;
    gM.player_[i].dst_rect_.h = 40;
    gM.player_[i].index_mov_ = 0;
    gM.player_[i].previous_movs_[gM.player_[i].index_mov_]= gM.player_[i].dst_rect_.y*16+ gM.player_[i].dst_rect_.x;
    gM.player_[i].current_.movement = gM.player_[i].base_.movement;
    ent_list.push_back(&gM.player_[i]);

  }
  num_turns_ = 0;
  total_turns_ = 4 + n_e;

  SDL_Color black = {0,0,0,255};
  
  gM.combat_.initCombat(gM.player_[0]);
  gM.combat_.current_char_ = &gM.player_[0];

  gM.ui_rects_[0].dst_rect_.x = gM.kBoardWidth;
  gM.ui_rects_[0].dst_rect_.y = 0;
  gM.ui_rects_[0].dst_rect_.w = gM.kWindowWidth - gM.kBoardWidth;
  gM.ui_rects_[0].dst_rect_.h = gM.kWindowHeight;
  
  gM.ui_rects_[1].dst_rect_.x = 0;
  gM.ui_rects_[1].dst_rect_.y = gM.kBoardHeight;
  gM.ui_rects_[1].dst_rect_.w = gM.kWindowWidth;
  gM.ui_rects_[1].dst_rect_.h = gM.kWindowHeight - gM.kBoardHeight;
  
  gM.ui_rects_[0].fill_color_ = black;
  gM.ui_rects_[1].fill_color_ = black;

  ent_list.push_back (&gM.ui_rects_[0]);
  ent_list.push_back (&gM.ui_rects_[1]);
  for(int i= 0; i<9; ++i){
    ent_list.push_back(&gM.combat_.stats_text_[i]);
  }
  for(int i = 0; i<6; ++i){
    ent_list.push_back(&gM.combat_.stats_rect_[i]);
  }
  for(int i = 0; i < 2; ++i){
    ent_list.push_back(&gM.combat_.stats_title_[i]);
  }

  // Combat Buttons
  SDL_Color button_color = {121, 121, 121, 60};
  SDL_Color text_color = {0, 0, 0, 255};
  char* font_path = "../data/fonts/BreathFire.ttf";
  int font_size = 25;
  
    // Attack
  combat_button_[0].dst_rect_ = {760, 495, 150, 50};
  combat_button_[0].fill_color_ = button_color;
  
    // End Turn
  combat_button_[1].dst_rect_ = {760, 565, 150, 50};
  combat_button_[1].fill_color_ = button_color;

  for(int i = 0; i < 3; ++i){
    ent_list.push_back(&combat_button_[i]);
  }

  button_color = {255, 255, 255, 60};
  SDL_Rect action_dst = {785, 500, 100, 40};
  actions_text_[0].init(font_path, 25, button_color,"Attack", action_dst);

  action_dst = {785, 570, 100, 40};
  actions_text_[1].init(font_path, 25, button_color,"End Turn", action_dst);

  for(int i = 0; i < 2; ++i){
    ent_list.push_back(&actions_text_[i]);
  }

}
/*
void CombatScene::quit(){
  
  ent_list.clear();
}*/


void CombatScene::input(SDL_Event* eve){

  GameManager& gM = GameManager::Instantiate();

  SDL_Point mouse_position = {eve->button.x, eve->button.y};
  SDL_Rect button_dst = {760, 495, 150, 50};
  SDL_Color text_color_red = {255,0,0,255};
  SDL_Color text_color_grey = {255,255,255,60};
  SDL_Color button_color = {121, 121, 121, 60};

  // Attack Game
  if(!attacking_){
    if(SDL_PointInRect(&mouse_position, &button_dst)){

      actions_text_[0].changeColor(text_color_red);
      // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Prueba", "Hola", NULL);
      
      if(eve->type == SDL_MOUSEBUTTONDOWN &&
         eve->button.button == SDL_BUTTON_LEFT){
        
        char* font_path = "../data/fonts/BreathFire.ttf";
        attacking_ = 1;
        actions_text_[0].changeColor(text_color_grey);
        /* Do stuff */
        
        // Buttons
        combat_button_[0].dst_rect_ = {700, 495, 125, 50};
        combat_button_[1].dst_rect_ = {700, 565, 125, 50};
        combat_button_[2].dst_rect_ = {845, 495, 125, 50};
        combat_button_[3].dst_rect_ = {845, 565, 125, 50};

        // Text
        SDL_Rect tmp_rect = {705, 500, 120, 40};
        actions_text_[0].changeColor(text_color_grey);
        
        actions_text_[0].changeText("Default");
        actions_text_[0].setPosition(&tmp_rect);

        tmp_rect = {705, 570, 120, 40};
        actions_text_[1].changeText("Default");
        actions_text_[1].setPosition(&tmp_rect);

        /*tmp_rect = {850, 500, 120, 40};
        actions_text_[2].changeText("Default");
        actions_text_[2].setPosition(&tmp_rect);*/
        // actions_text_[1].changeText("Prueba");
        // actions_text_[2].changeText("Prueba");
        // actions_text_[0].changeText(gM.player_[num_turns_].char_attacks_[0].name);
        /*actions_text_[1].init(font_path, 15, text_color_grey, "Return",
                              {860, 570, 100, 40});
        actions_text_[2].init(font_path, 15, text_color_grey, "Return",
                              {860, 570, 100, 40});*/
        actions_text_[2].init(font_path, 25, text_color_grey, "Default",
                              {850, 500, 120, 40});
        actions_text_[3].init(font_path, 25, text_color_grey, "Return",
                              {860, 570, 100, 40});

        combat_button_[2].fill_color_ = button_color;
        combat_button_[3].fill_color_ = button_color;
        ent_list.push_back(&combat_button_[2]);
        ent_list.push_back(&combat_button_[3]);
        ent_list.push_back(&actions_text_[2]);
        ent_list.push_back(&actions_text_[3]);

      }
        
    }else{
      actions_text_[0].changeColor(text_color_grey);
    }

    // End Turn
    button_dst = {785, 570, 100, 40};
    if(SDL_PointInRect(&mouse_position, &button_dst)){

      actions_text_[1].changeColor(text_color_red);
      
      if(eve->type == SDL_MOUSEBUTTONDOWN &&
       eve->button.button == SDL_BUTTON_LEFT){

        gM.player_[num_turns_].turn_completed_ = 1;
        ++num_turns_;

      }
        
    }else{
      actions_text_[1].changeColor(text_color_grey);
    }

  }else{
    
    // Up-Left Attack
    SDL_Rect tmp_button[3];
    tmp_button[0] = {700, 495, 125, 50};
    tmp_button[1] = {700, 565, 125, 50};
    tmp_button[2] = {845, 495, 125, 50};

    for(int i = 0; i < 3; ++i){
      if(SDL_PointInRect(&mouse_position, &tmp_button[i])){

        actions_text_[i].changeColor(text_color_red);
        // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Prueba", "Hola", NULL);

        // Atack
        if(eve->type == SDL_MOUSEBUTTONDOWN &&
           eve->button.button == SDL_BUTTON_LEFT &&
           gM.player_[num_turns_].current_.mana >= gM.player_[num_turns_].char_attacks_[i].mana_cost){

            combat_button_[0].dst_rect_ = {760, 495, 150, 50};
            combat_button_[1].dst_rect_ = {760, 565, 150, 50};

            combat_button_[2].dst_rect_ = {7600, 495, 150, 50};
            combat_button_[3].dst_rect_ = {7600, 565, 150, 50};

            SDL_Rect tmp_dst = {10000, 10000, 0,0};
            actions_text_[2].setPosition(&tmp_dst);
            actions_text_[3].setPosition(&tmp_dst);

            tmp_dst = {785, 500, 100, 40};
            actions_text_[0].changeText("Attack");
            actions_text_[0].setPosition(&tmp_dst);

            tmp_dst = {785, 570, 100, 40};
            actions_text_[1].changeText("End Turn");
            actions_text_[1].setPosition(&tmp_dst);
            attacking_ = 0;
        }

      }else{

        actions_text_[i].changeColor(text_color_grey);

      }

    }

    // Down-Left Attack
    /*button_dst = {700, 565, 125, 50};
    if(SDL_PointInRect(&mouse_position, &button_dst)){
    
      actions_text_[1].changeColor(text_color_red);

    }else{

      actions_text_[1].changeColor(text_color_grey);

    }

    // Up-Right Attack
    button_dst = {845, 495, 125, 50};
    if(SDL_PointInRect(&mouse_position, &button_dst)){
    
      actions_text_[2].changeColor(text_color_red);

    }else{

      actions_text_[2].changeColor(text_color_grey);

    }*/

    // Return
    button_dst = {845, 565, 125, 50};
    if(SDL_PointInRect(&mouse_position, &button_dst)){
    
      actions_text_[3].changeColor(text_color_red);

      if(eve->type == SDL_MOUSEBUTTONDOWN &&
         eve->button.button == SDL_BUTTON_LEFT){

          combat_button_[0].dst_rect_ = {760, 495, 150, 50};
          combat_button_[1].dst_rect_ = {760, 565, 150, 50};

          combat_button_[2].dst_rect_ = {7600, 495, 150, 50};
          combat_button_[3].dst_rect_ = {7600, 565, 150, 50};

          SDL_Rect tmp_dst = {10000, 10000, 0,0};
          actions_text_[2].setPosition(&tmp_dst);
          actions_text_[3].setPosition(&tmp_dst);

          tmp_dst = {785, 500, 100, 40};
          actions_text_[0].changeText("Attack");
          actions_text_[0].setPosition(&tmp_dst);

          tmp_dst = {785, 570, 100, 40};
          actions_text_[1].changeText("End Turn");
          actions_text_[1].setPosition(&tmp_dst);
          attacking_ = 0;
      }

    }else{

      actions_text_[3].changeColor(text_color_grey);

    }

  }
  
  if(eve->type == SDL_KEYDOWN){ 
   
  } 
  if(eve->key.keysym.sym == SDLK_p){
    ++num_turns_;
    gM.combat_.initCombat(gM.player_[num_turns_]);
    gM.combat_.current_char_ = &gM.player_[num_turns_];
  }
  if(eve->key.keysym.sym == SDLK_l){
    
    gM.NPC_[0].endTile();
    gM.NPC_[0].current_.movement = 5 ;
    
  }
  if(num_turns_<4){
    gM.player_[num_turns_].movCharacterCombat(eve);
  }
  
}


void CombatScene::update(){
  GameManager& gM = GameManager::Instantiate();
  gM.combat_.updateStats();
  
  if(num_turns_<4){ 
    gM.player_[num_turns_].updateSpriteC();
  }
  else{
    gM.NPC_[num_turns_-4].iaBehaviour();
    gM.NPC_[num_turns_-4].updateSpriteC();
  }
 /*
  if(gM.NPC_[num_turns_-4].turn_completed_){
    ++num_turns_;
  }*/
  
  /*if(gM.player_[num_turn].turn_completed_){
    ++num_turns_;
  }*/
  //int a = gM.player_[0].mhDistance(&gM.player_[1].dst_rect_);
  
  //printf("distance:%d\n",a);
  /*
  if(num_turns_>=4){
    gM.NPC_[num_turns_].iaBehaviour();
    //gM.NPC_[num_turns_].iaMov();
  }*/
  if(num_turns_ >= total_turns_){
    num_turns_ = 0;
    gM.player_[0].reset();
    gM.player_[1].reset();
    gM.player_[2].reset();
    gM.player_[3].reset();
    for(int i= 0; i< total_turns_-4; ++i) {
      gM.NPC_[i].reset();
      printf("HOLAA\n")
    }      
    
  }
  
}

void CombatScene::drawImgui(SDL_Renderer* ren){
  
  // Character Stats Frame
  SDL_Rect stats_frame = {685, 60, 300, 370};

  SDL_SetRenderDrawColor(ren, 255,255,0,255);
  SDL_RenderDrawRect(ren, &stats_frame);

  // Actions Frame
  SDL_Rect actions_frame = {685, 480, 300, 150};

  SDL_SetRenderDrawColor(ren, 255,255,0,255);
  SDL_RenderDrawRect(ren, &actions_frame);

}