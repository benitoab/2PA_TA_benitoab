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

#include "imgui.h"
#include "imgui_sdl.h"

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

/** @brief Process mouse events for the ImGuiSDL binding.
 *
 * @param Pointer to an SDL_Event captured this frame.
 */
void ImGuiSDLProcessEvent(SDL_Event* e) {
  if (e == nullptr) return;

  ImGuiIO& io = ImGui::GetIO();

  int wheel = 0;

  while (SDL_PollEvent(e))
  {
    if (e->type == SDL_WINDOWEVENT)
    {
      if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
        io.DisplaySize.x = static_cast<float>(e->window.data1);
        io.DisplaySize.y = static_cast<float>(e->window.data2);
      }
    }
    else if (e->type == SDL_MOUSEWHEEL)
    {
      wheel = e->wheel.y;
    }
  }

  int mouseX, mouseY;
  const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

  // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or 
  // write to those fields from your Windows message loop handlers, etc.)

  io.DeltaTime = 1.0f / 60.0f;
  io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
  io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
  io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
  io.MouseWheel = static_cast<float>(wheel);
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

  /*gM.window_flags |= ImGuiWindowFlags_NoMove;
  gM.window_flags |= ImGuiWindowFlags_NoResize;
  gM.window_flags |= ImGuiWindowFlags_NoCollapse;*/

  ImGui::CreateContext();
	ImGuiSDL::Initialize(ren_, gM.kWindowWidth, gM.kWindowHeight);

  srand((unsigned int)time(NULL));

  gM.map_texture_ = Texture::CreateTexture("../data/resources/tileset.png", ren_);

  CreateBoard();
  InitLogic();
  CreateMap();
  gM.c.init();
  gM.c.dst_rect_.x = gM.kViewSize/2;
  gM.c.dst_rect_.y = gM.kViewSize/2;
  gM.c.dst_rect_.w = gM.layer1_.map_[0][0].dst_rect_.w ;
  gM.c.dst_rect_.h = gM.layer1_.map_[0][0].dst_rect_.h ;         

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

  ImGuiSDL::Deinitialize();
  
  SDL_DestroyRenderer(ren_);
  SDL_DestroyWindow(win_);
  
  // Cleanup

  // Cleanup
  ImGui::DestroyContext();

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

    /*if(event.key.keysym.sym == SDLK_SPACE){

      SDL_SetWindowSize(win_, 300, 300);

    }*/

    gM.c.movCharacter(&event);
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
  float size;
  
  // Start the Dear ImGui frame
  ImGui::NewFrame();
  // ImGui::SetNextWindowPos(ImVec2(gM.kWindowWidth/2, gM.kWindowHeight/2), 0, ImVec2(0.5, 0.5));
  ImGui::SetNextWindowSize(ImVec2(gM.kImGuiWidth, gM.kImGuiHeight));
  ImGui::Begin("Antekeland", NULL, gM.window_flags);
  size = ImGui::GetWindowWidth();
  // ImGui::ShowDemoWindow();
  printf("%f\n", size);
  ImGui::SameLine(100);
  ImGui::Text("Select Skin:");
  ImGui::AlignTextToFramePadding();
  ImGui::ArrowButton("##left", ImGuiDir_Left);
  ImGui::SameLine();
  ImGui::Text("Skin");
  ImGui::SameLine();
  ImGui::ArrowButton("##right", ImGuiDir_Right);

  // gM.layer1_.reset0Position();
  // gM.layer2_.reset0Position();
  
  // gM.layer1_.update0Position();
  // gM.layer2_.update0Position();

  // printf("%d %d\n", Board::x_origin_, Board::y_origin_);

  ImGui::End();

}

void Game::draw(){

  GameManager& gM = GameManager::Instantiate();
  
  SDL_SetRenderDrawColor(ren_,0,0,0,0);
  SDL_RenderClear(ren_);

  //ImGui
  ImGui::Render();  
  ImGuiSDL::Render(ImGui::GetDrawData());

  /* Layer 1 */
  // gM.layer1_.drawMap(ren_);
  /* Character */
  // gM.c.draw(ren_);
  // gM.combat_.drawMark(ren_);
  /* Layer 2 */
  // gM.layer2_.drawMap(ren_);
  /* Layer3 */
  // gM.drawBlackRects(ren_);

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