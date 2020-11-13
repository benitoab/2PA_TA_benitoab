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

Game::Game(){
  win_ = nullptr;
  ren_ = nullptr;
  quit_ = 0;
  current_time_ = 0;
  last_time_ = 0;
}

Game::~Game(){

  if(nullptr != win_){ SDL_DestroyWindow(win_); }
  if(nullptr != ren_){ SDL_DestroyRenderer(ren_); }
   
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

  srand(time(NULL));

  GameManager& gM = GameManager::Instantiate();

  gM.map_texture_ = Texture::CreateTexture("../data/resources/tileset.png", ren_);

  CreateBoard();
  InitLogic();
  CreateMap();

  for(int i = 0; i < Board::kBoardSize; ++i){
    for(int j = 0; j < Board::kBoardSize; ++j){
      gM.layer1_.map_[i][j].initSubSprite();
      gM.layer2_.map_[i][j].initSubSprite();
    }
  }
 
  return 0;
}

void Game::quit(){
  
  // Rest of the other quit functions
  // Clean up our objects and quit
  
  SDL_DestroyRenderer(ren_);
  SDL_DestroyWindow(win_);
  
  // Cleanup

  IMG_Quit();
  SDL_Quit();
  TTF_Quit();
  printf("Me he cerrado perfe. Adioh");
  
}

void Game::input(){
  
  last_time_ = SDL_GetTicks();

  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT ) {
      quit_ = true;
      
    }

    if(event.key.keysym.sym == SDLK_UP){
      show = false;
    }

    if(event.key.keysym.sym == SDLK_DOWN){
      show = true;
    }
   
    if (event.type == SDL_WINDOWEVENT && 
      event.window.event == SDL_WINDOWEVENT_CLOSE && 
      event.window.windowID == SDL_GetWindowID(win_)) {
      quit_ = true;
    }
    // Add the rest of input events here: keyboard, gamepad, etc...
  }
  
}

void Game::update(){
}

void Game::draw(){

  GameManager& gM = GameManager::Instantiate();
  
  SDL_SetRenderDrawColor(ren_,0,0,0,0);
  SDL_RenderClear(ren_);

  gM.layer1_.drawMap(ren_);
  /* Character */
  if(show){
    gM.layer2_.drawMap(ren_);
  }

  //Update the screen
  SDL_RenderPresent(ren_);
  
  do{
    current_time_ = SDL_GetTicks();
  }while((current_time_ - last_time_) <= (1000.0/fps));
}

void Game::game(){
  
  init();
 
  while(!quit_){
    
    input();
    update();
    draw();
    
  }

  quit();
}