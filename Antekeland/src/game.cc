/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "imgui.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "game.h"
#include "gamemanager.h"
#include "grid.h"
#include "customization.h"
#include "mainscene.h"

#include "imgui.h"
#include "imgui_sdl.h"

Game::Game(){
  win_ = nullptr;
  ren_ = nullptr;
  current_scene_[0] = nullptr;
  current_scene_[1] = nullptr;
  current_scene_[2] = nullptr;
  current_scene_[3] = nullptr;
  //previous_scene_ = nullptr;
  quit_ = 0;
  current_time_ = 0;
  last_time_ = 0;
}

Game::~Game(){

  if(nullptr != win_){ SDL_DestroyWindow(win_); }
  if(nullptr != ren_){ SDL_DestroyRenderer(ren_); }
}

void Game::loadScene(int n_scene){
  if(n_scene < 4){
    current_scene_[n_scene]->init();
  }
 
}


int Game::init(){
  //SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

  win_ = SDL_CreateWindow("Antekeland", 100, 100, GameManager::kWindowWidth,
                          GameManager::kWindowHeight, SDL_WINDOW_SHOWN);
  if (win_ == nullptr){
    //std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  ren_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren_ == nullptr){
    SDL_DestroyWindow(win_);
    // std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  //SDL_IMG
  int flags= IMG_INIT_PNG;
  IMG_Init(flags);
  if(TTF_Init() == -1){
    printf("Error al cargar SDL_ttf\n"); 
  }

  GameManager& gM = GameManager::Instantiate();

  InitCustomization(ren_);

  srand((unsigned int)time(NULL));

  gM.map_texture_ = Texture::CreateTexture("../data/resources/tileset.png", ren_);

  CreateBoard();
  InitLogic();
  CreateMap();
  gM.initsAttacks();
  gM.player_[0].init();
  gM.player_[0].dst_rect_.x = gM.kViewSize/2;
  gM.player_[0].dst_rect_.y = gM.kViewSize/2;
  gM.player_[0].dst_rect_.w = gM.layer1_.map_[0][0].dst_rect_.w ;
  gM.player_[0].dst_rect_.h = gM.layer1_.map_[0][0].dst_rect_.h ;
  gM.combat_.initCombat(gM.player_[0]);
  gM.combat_.current_char_ = &gM.player_[0];

  for(int i = 0; i < Board::kBoardSize; ++i){
    for(int j = 0; j < Board::kBoardSize; ++j){
      gM.layer1_.map_[i][j].initSubSprite();
      gM.layer2_.map_[i][j].initSubSprite();
    }
  }
  /*
  current_scene_[0] = new MainScene();
  current_scene_[0]->init();
  gM.over_world_scene_ = 1;*/
  return 0;
}

void Game::quit(){
  
  // Rest of the other quit functions
  // Clean up our objects and quit
  
  SDL_DestroyRenderer(ren_);
  SDL_DestroyWindow(win_);
  
  // Cleanup
  QuitCustomization();
  IMG_Quit();
  SDL_Quit();
  TTF_Quit();
  
  printf("Me he cerrado perfe. Adioh");
  
}

void Game::input(){
  
  last_time_ = SDL_GetTicks();
  GameManager& gM = GameManager::Instantiate();
  
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    ImGuiSDLProcessEvent(&event);
    if (/*event.key.keysym.sym == SDLK_ESCAPE || */event.type == SDL_QUIT ) {
      quit_ = true;      
    }
    if(event.key.keysym.sym == SDLK_1){ ++gM.player_[0].current_.hp;}
    if(event.key.keysym.sym == SDLK_2){ --gM.player_[0].current_.hp;}

    //current_scene_[0]->input(&event);
    /*if(event.key.keysym.sym == SDLK_SPACE){

      SDL_SetWindowSize(win_, 300, 300);

    }*/

    if (event.type == SDL_WINDOWEVENT && 
      event.window.event == SDL_WINDOWEVENT_CLOSE && 
      event.window.windowID == SDL_GetWindowID(win_)) {
      quit_ = true;
    }
    // Add the rest of input events here: keyboard, gamepad, etc...
  }
  
}

void Game::update(){

  GameManager& gM = GameManager::Instantiate();
  
  CustomizeCharacter(&gM.player_[0]);
   //current_scene_[0]->update();
  //UpdateImGui();

   //gM.layer1_.reset0Position();
   //gM.layer2_.reset0Position();
  
   //gM.layer1_.update0Position();
   //gM.layer2_.update0Position();

  // printf("%d %d\n", Board::x_origin_, Board::y_origin_);

}

void Game::draw(){

  GameManager& gM = GameManager::Instantiate();
  
  SDL_SetRenderDrawColor(ren_,222,208,158,87);
  SDL_RenderClear(ren_);

  //current_scene_[0]->draw(ren_);
  
  if(gM.over_world_scene_){
    gM.layer1_.drawMap(ren_);
    gM.layer2_.drawMap(ren_);
  }
  //ImGui
  DrawCustomization();
  DrawCharacter(ren_, gM.player_[0]);
  /* Layer 1 */
  // gM.layer1_.drawMap(ren_);
  /* Character */
  // gM.player.draw(ren_);
  //gM.playerombat_.drawMark(ren_);
  /* Layer 2 */
  // gM.layer2_.drawMap(ren_);
  /* Layer3 */
  // gM.drawBlackRects(ren_);
  // gM.playerombat_.drawAttacks(ren_);
  // gM.playerombat_.drawStats(ren_, gM.player);

  //Update the screen
  SDL_RenderPresent(ren_);
  
  do{
    current_time_ = SDL_GetTicks();
  }while((current_time_ - last_time_) <= (1000.0/fps));
}

void Game::mainGame(){
  
  init();
 
  while(!quit_){
    
    input();    
    update();    
    draw();
    
  }

  quit();
}