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
#include "custoscene.h"

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

int Game::loadScene(int n_scene){
  
  int32_t last_scene = current_id_scene_;
  // current_scene[current_id_scene]->quit();
  current_id_scene_ = n_scene;
  //current_scene[current_id_scene]->init();
  
  return last_scene;
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
  
  //SDL_TEXT
  if(TTF_Init() == -1){
    printf("Error al cargar SDL_ttf\n"); 
  }

  GameManager& gM = GameManager::Instantiate();
  //IMGUI
  gM.window_flags |= ImGuiWindowFlags_NoMove;
  gM.window_flags |= ImGuiWindowFlags_NoResize;
  gM.window_flags |= ImGuiWindowFlags_NoCollapse;

  ImGui::CreateContext();
  

  ImGuiIO& io = ImGui::GetIO();
  newFont = io.Fonts->AddFontFromFileTTF("../data/fonts/BreathFire.ttf", 16.0f);  
  io.Fonts->Build();
  
  ImGuiSDL::Initialize(ren_, gM.kWindowWidth, gM.kWindowHeight);
	 

  srand((unsigned int)time(NULL));
  // Se modificará
  gM.map_texture_ = Texture::CreateTexture("../data/resources/tileset.png", ren_);
  gM.bg_texture_ = Texture::CreateTexture("../data/resources/bgc.png", ren_);

  CreateBoard();
  InitLogic();
  CreateMap();

  gM.player_[0].init();
  gM.player_[0].dst_rect_.x = gM.kViewSize/2;
  gM.player_[0].dst_rect_.y = gM.kViewSize/2;
  gM.player_[0].dst_rect_.w = gM.layer1_.map_[0][0].dst_rect_.w ;
  gM.player_[0].dst_rect_.h = gM.layer1_.map_[0][0].dst_rect_.h ;
  gM.combat_.initCombat(gM.player_[0]);
  gM.combat_.current_char_ = &gM.player_[0];

  RBM::Transform2 aux_tr = {{0.0f,0.0f},0.0f,{0.0f,0.0f}};
  RBM::Vec2 aux_v2 = {0.5f,0.0f};
  gM.bg_custo_.init(aux_tr,1,0,*gM.bg_texture_, &aux_v2);

  for(int i = 0; i < Board::kBoardSize; ++i){
    for(int j = 0; j < Board::kBoardSize; ++j){
      gM.layer1_.map_[i][j].initSubSprite();
      gM.layer2_.map_[i][j].initSubSprite();
    }
  }
  
  char* p = "../data/database/antekeland.db";
  gM.data_base_.init();
  gM.data_base_.openDB(p);
  gM.data_base_.readProfessionData();
  
  for(int i=0; i<7; ++i){
    
    printf("hp: %d\n mana: %d\n armor: %d\n crit: %d\n",
    (gM.data_base_.profession_ + i)->hp, 
    (gM.data_base_.profession_ + i)->mana, 
    (gM.data_base_.profession_ + i)->armor,
    (gM.data_base_.profession_ + i)->crit_chance);
  }
  
  
  
  

  //current_scene_[0] = new Customization();
  current_scene_[1] = new MainScene();
  current_scene_[1]->init();

  current_scene_[0] = new CustoScene();
  current_scene_[0]->init();

  
  current_id_scene_ = 1;

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
    if (event.type == SDL_QUIT ) {
      quit_ = true;      
    }
    if(event.key.keysym.sym == SDLK_1){ loadScene(0);}
    if(event.key.keysym.sym == SDLK_2){ loadScene(1);}
    // if(event.key.keysym.sym == SDLK_3){ ;}
    // if(event.key.keysym.sym == SDLK_4){ ;}
    // if(event.key.keysym.sym == SDLK_5){ ;}

    current_scene_[current_id_scene_]->input(&event);
  
    if (event.type == SDL_WINDOWEVENT && 
      event.window.event == SDL_WINDOWEVENT_CLOSE && 
      event.window.windowID == SDL_GetWindowID(win_)) {
      quit_ = true;
    }
    // Add the rest of input events here: keyboard, gamepad, etc...
  }
  
}

void Game::update(){

  //GameManager& gM = GameManager::Instantiate();
 
  current_scene_[current_id_scene_]->update();

}

void Game::draw(){

  //GameManager& gM = GameManager::Instantiate();
  
  SDL_SetRenderDrawColor(ren_,222,208,158,87);
  SDL_RenderClear(ren_);

  current_scene_[current_id_scene_]->draw(ren_);
  current_scene_[current_id_scene_]->drawImgui(ren_);
  


  


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