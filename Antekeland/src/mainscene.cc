#include "mainscene.h"
#include "gamemanager.h"


MainScene::MainScene(){
  

  
}

MainScene::~MainScene(){

}



void MainScene::init(){

  GameManager& gM = GameManager::Instantiate();
  SDL_Color black = {0,0,0,50};
  
  gM.combat_.initCombat(gM.player_[0]);
  gM.combat_.current_char_ = &gM.player_[0];
  
  gM.over_world_scene_ = 1;
 
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
  

  
  
  // introduce all entities to draw
  
  for(int i = 0; i< Board::kBoardSize; ++i){
    for(int j = 0; j< Board::kBoardSize; ++j){    
      ent_list.push_back(&gM.layer1_.map_[i][j]); 
    }
  }

  gM.player_[4].dst_rect_.x = gM.kViewSize/2;
  gM.player_[4].dst_rect_.y = gM.kViewSize/2;
  gM.player_[4].dst_rect_.w = gM.layer1_.map_[0][0].dst_rect_.w ;
  gM.player_[4].dst_rect_.h = gM.layer1_.map_[0][0].dst_rect_.h ;
  ent_list.push_back(&gM.player_[4]);
  
  
  

  for(int i = 0; i<Board::kBoardSize; ++i){
    for(int j = 0; j<Board::kBoardSize; ++j){
      
      ent_list.push_back(&gM.layer2_.map_[i][j]);
    }
  }
  ent_list.push_back (&gM.ui_rects_[0]);
  ent_list.push_back (&gM.ui_rects_[1]);
  /*for(int i= 0; i<8; ++i){
    ent_list.push_back(&gM.combat_.stats_text_[i]);
  }
  for(int i = 0; i<6; ++i){
    ent_list.push_back(&gM.combat_.stats_rect_[i]);
  }*/

  // Menu Buttons
  SDL_Color button_color = {163, 143, 138, 60};
  SDL_Color text_color = {0, 0, 0, 255};
  char* font_path = "../data/fonts/BreathFire.ttf";
  int font_size = 25;
    // Save Game
  mainscene_button_[0].dst_rect_ = {720, 150, 200, 60};
  mainscene_button_[0].fill_color_ = button_color;
  
    // Inventory
  mainscene_button_[1].dst_rect_ = {720, 300, 200, 60};
  mainscene_button_[1].fill_color_ = button_color;

    // Quit Game
  mainscene_button_[2].dst_rect_ = {720, 450, 200, 60};
  mainscene_button_[2].fill_color_ = button_color;
  
  SDL_Rect dst_rect = {730, 160, 180, 40};
  mainscene_text_[0].init(font_path, (uint16_t)font_size, text_color, "Save Game", dst_rect);
  
  dst_rect = {730, 310, 180, 40};
  mainscene_text_[1].init(font_path, (uint16_t)font_size, text_color, "Inventory", dst_rect);
  
  dst_rect = {730, 460, 180, 40};
  mainscene_text_[2].init(font_path, (uint16_t)font_size, text_color, "Quit Game", dst_rect);

  ent_list.push_back(&mainscene_button_[0]);
  ent_list.push_back(&mainscene_button_[1]);
  ent_list.push_back(&mainscene_button_[2]);

  ent_list.push_back(&mainscene_text_[0]);  
  ent_list.push_back(&mainscene_text_[1]);  
  ent_list.push_back(&mainscene_text_[2]);
 
}

void MainScene::quit(){
  GameManager& gM = GameManager::Instantiate();
  gM.over_world_scene_ = 0;
  Scene::quit();
}

void MainScene::input(SDL_Event* eve){
  
  GameManager::Instantiate().player_[4].movCharacter(eve);
  SDL_Point mouse_position = {eve->button.x, eve->button.y};
  SDL_Rect button_dst = {720, 150, 200, 60};
  SDL_Color text_color_white = {255,255,255,255};
  SDL_Color text_color_black = {0,0,0,255};

  // Save Game
  if(SDL_PointInRect(&mouse_position, &button_dst)){

    mainscene_text_[0].changeColor(text_color_black);
    
    if(eve->type == SDL_MOUSEBUTTONDOWN &&
     eve->button.button == SDL_BUTTON_LEFT){

      /* Do stuff */

    }
      
  }else{
    mainscene_text_[0].changeColor(text_color_white);
  }
   
  // Inventory
  button_dst = {730, 310, 180, 40};
  if(SDL_PointInRect(&mouse_position, &button_dst)){

    mainscene_text_[1].changeColor(text_color_black);
    
    if(eve->type == SDL_MOUSEBUTTONDOWN &&
     eve->button.button == SDL_BUTTON_LEFT){

      /* Do stuff */

    }
      
  }else{
    mainscene_text_[1].changeColor(text_color_white);
  }
  
  // Quit Game
  button_dst = {730, 460, 180, 40};
  if(SDL_PointInRect(&mouse_position, &button_dst)){

    mainscene_text_[2].changeColor(text_color_black);
    
    if(eve->type == SDL_MOUSEBUTTONDOWN &&
     eve->button.button == SDL_BUTTON_LEFT){

      /* Do stuff */

    }
      
  }else{
    mainscene_text_[2].changeColor(text_color_white);
  }
  
  if(eve->type == SDL_KEYDOWN){
    if(eve->key.keysym.sym == SDLK_0){
      printf("Guardo\n");
      //GameManager::Instantiate().data_base_.saveBoardData();
      printf("Guardado\n");
    }
  }

}

void MainScene::update(){
  GameManager& gM = GameManager::Instantiate();
  
  gM.layer1_.reset0Position();
  gM.layer2_.reset0Position();
  
  gM.layer1_.update0Position();
  gM.layer2_.update0Position();
  gM.combat_.updateStats();
  
  gM.player_[4].updateSpriteC();

}

void MainScene::drawImgui(SDL_Renderer* ren){
  
}
