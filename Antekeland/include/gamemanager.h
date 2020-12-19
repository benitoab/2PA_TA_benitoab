/**
 * Antekeland 2020
 * Author: Ricardo Beltrán Muriel
 * Mail: beltranmu@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__ 1

#include "SDL.h"
#include "database.h"
#include "texture.h"
#include "background.h"
#include "board.h"
#include "logic.h"
#include "character.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "combat.h"
#include "rect.h"

class GameManager{
  public:  
    //Constant
    static const int kWindowWidth = 1024;
    static const int kWindowHeight = 768;
    static const int kBoardWidth = 640;
    static const int kBoardHeight = 640;    
    static const unsigned char kViewSize = 16;
    static const int kImGuiWidth = 500;
    static const int kImGuiHeight = 500;
    ImGuiWindowFlags window_flags = 0;
   
    //Methods  
    ~GameManager();
    //It has to be change of .h
   

    //Factory
    static GameManager& Instantiate();
    
    // Atributes
    Board layer1_;
    Board layer2_;     // Graphic map
    Logic board_[Board::kBoardSize][Board::kBoardSize];
    Logic units_[Board::kBoardSize][Board::kBoardSize]; // Logical map
    Logic logic_board_[16][16]; // Logical Combat map
    Character player_[4];
    Character NPC_[10];
    Texture* map_texture_;
    Texture* bg_texture_;
    Texture *ground_cave_, *frozen_cave_;
    Background bg_custo_;
    Combat combat_;
    DataBase data_base_;
 
    int32_t over_world_scene_;
    Rect ui_rects_[2];
    
  private:
    //Methods
    GameManager();
    static GameManager* instance_gm_;      

};

#endif  // __GAMEMANAGER_H__