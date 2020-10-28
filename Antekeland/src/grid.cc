/*
* Antekeland 2077
* Author: Javier Benito Abolafio & Ricardo Beltrán Muriel
* Mail: benitoab@esat-alumni.com & beltranmu@esat-alumni.com
* University Development @ESAT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sprite.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

// Utility macros
#define CHECK_ERROR(test, message) \
  do { \
    if((test)) { \
      fprintf(stderr, "%s\n", (message)); \
      exit(1); \
    } \
  } while(0)

// Window dimensions
static const int kWindowWidth = 640;
static const int kWindowHeight = 640;

const unsigned char size = 32;
const unsigned char kNumRows = size;
const unsigned char kNumCols = size;
const unsigned char search_range = (size/4)*3; // rango de busqueda
const float concentration = 0.55f;
const int chance_to_move = 721;
const unsigned char view_size = 32;

unsigned int repeats = 0;

SDL_Texture* ricardo;
// Sprite tilemap;

struct SCharacter{
  SDL_Rect info_body;
  int is_moving;
  //int casilla;
  //int next_casilla;
};

struct STile{
  unsigned char state; // Cell State
  unsigned char type;  // Cell Type
  SDL_Rect info;       // Float x,y, w,h; // x,y ,  ancho y alto
};

STile board[kNumRows][kNumCols];
SCharacter Character;
unsigned char total_cells = 0;

void CreateBoard(){
  
  int x = kWindowWidth/kNumCols*(size/view_size); 
  int y = kWindowHeight/kNumRows*(size/view_size);
  
  for(int r = 0; r < kNumRows; ++r){
  
    for(int c = 0; c < kNumCols; ++c){
          
      board[r][c].info.x = c * x;
      board[r][c].info.y = r * y;
      board[r][c].info.w = x;
      board[r][c].info.h = y;
      board[r][c].type = 0;
      
      if(rand()%100 <= concentration *100){
        
        board[r][c].state = (rand()%7)+1;
         
      }else{
        
        board[r][c].state = 0;
        
      }
      
    }
  }

}

void InitCharacter(){
  
  int x = rand()%kNumCols;
  int y = rand()%kNumRows;
  
  Character.info_body.x = x;
  Character.info_body.y = y;
  
  Character.info_body.w = kWindowWidth/kNumCols-8;
  Character.info_body.h = kWindowHeight/kNumRows-8;
  
  Character.is_moving = 1;
  
}

void DrawBorad(SDL_Renderer *renderer){

  SDL_Rect rect_subsprite;
  
  for(int i = 0; i< kNumRows; ++i){
  
    for(int j = 0; j < kNumCols; ++j){

      rect_subsprite.x = board[i][j].type * 64;
      rect_subsprite.y = board[i][j].state * 64;
      rect_subsprite.w = 64;
      rect_subsprite.h = 64;

      SDL_RenderCopy(renderer, ricardo, &rect_subsprite, &board[i][j].info);
      
    }
    
  }
 
}

// Checks the left cell to a given one
unsigned char CheckSingleNeighbour(unsigned char pos, const signed char desp){
  
  unsigned char resul = pos + desp;
    
  resul %= kNumCols;
  
  return resul;
  
}

// Returns the number of neighbours in the same state as a given cell
unsigned char CheckNeighbours(STile board[size][size], unsigned char row, unsigned char col, unsigned char state){
    
  unsigned char num_neighbours = 0;
  
  if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].state == state){ ++num_neighbours; }   // Upper-Left
  if(board[CheckSingleNeighbour(row, -1)][col].state == state){ ++num_neighbours; }                             // Upper
  if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, +1)].state == state){ ++num_neighbours; }   // Upper-Right
  if(board[row][CheckSingleNeighbour(col, -1)].state == state){ ++num_neighbours; }                             // Left
  if(board[row][CheckSingleNeighbour(col, +1)].state == state){ ++num_neighbours; }                             // Right
  if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, -1)].state == state){ ++num_neighbours; }   // Lower-Left
  if(board[CheckSingleNeighbour(row, +1)][col].state == state){ ++num_neighbours; }                             // Lower
  if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, +1)].state == state){ ++num_neighbours; }   // Lower-Right
  
  return num_neighbours;
  
}

unsigned char CheckNeighboursType(STile board[size][size], unsigned char row, unsigned char col, unsigned char state, unsigned char check_type){
    
  unsigned char num_neighbours = 0;
  
  if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].state == state &&
     board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].type != check_type){ ++num_neighbours; }   // Upper-Left

  if(board[CheckSingleNeighbour(row, -1)][col].state == state &&
     board[CheckSingleNeighbour(row, -1)][col].type != check_type){ ++num_neighbours; }                             // Upper

  if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, +1)].state == state &&
     board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, +1)].type != check_type){ ++num_neighbours; }   // Upper-Right

  if(board[row][CheckSingleNeighbour(col, -1)].state == state &&
     board[row][CheckSingleNeighbour(col, -1)].type != check_type){ ++num_neighbours; }                             // Left

  if(board[row][CheckSingleNeighbour(col, +1)].state == state &&
     board[row][CheckSingleNeighbour(col, +1)].type != check_type){ ++num_neighbours; }                             // Right

  if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, -1)].state == state &&
     board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, -1)].type != check_type){ ++num_neighbours; }   // Lower-Left

  if(board[CheckSingleNeighbour(row, +1)][col].state == state &&
     board[CheckSingleNeighbour(row, +1)][col].type != check_type){ ++num_neighbours; }                             // Lower

  if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, +1)].state == state &&
     board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, +1)].type != check_type){ ++num_neighbours; }   // Lower-Right

  
  return num_neighbours;
  
}

unsigned char CheckCrossNeighbours(STile board[size][size], unsigned char row, unsigned char col, unsigned char state){

  unsigned char num_neighbours = 0;

  if(board[CheckSingleNeighbour(row, -1)][col].state == state){ ++num_neighbours; }                             // Upper
  if(board[row][CheckSingleNeighbour(col, -1)].state == state){ ++num_neighbours; }                             // Left
  if(board[row][CheckSingleNeighbour(col, +1)].state == state){ ++num_neighbours; }                             // Right
  if(board[CheckSingleNeighbour(row, +1)][col].state == state){ ++num_neighbours; }                             // Lower

  return num_neighbours;

}

void SwapCells(unsigned char row1, unsigned char col1, unsigned char state1, unsigned char row2, unsigned char col2, unsigned char state2){

  board[row1][col1].state = state2;
  board[row2][col2].state = state1;
    
}

signed char TemporalSwap(unsigned char row1, unsigned char col1, unsigned char state1, unsigned char row2, unsigned char col2, unsigned char state2){
  
  signed char tmp_gain;
  
  SwapCells(row1, col1, state1, row2, col2, state2);
  
  tmp_gain = CheckNeighbours(board, row2, col2, board[row2][col2].state);  
  
  SwapCells(row1, col1, state2, row2, col2, state1);
  
  return tmp_gain;
  
}

signed char CalculateGain(unsigned char row1, unsigned char col1, unsigned char row2, unsigned char col2){
  
  signed char orig_gain;
  signed char new_gain;
  
  orig_gain = CheckNeighbours(board, row2, col2, board[row2][col2].state);
  
  new_gain = TemporalSwap(row2, col2, board[row2][col2].state,
                          row1, col1, board[row1][col1].state);
  
  return new_gain - orig_gain;
  
}

void EraseTile(STile board[size][size], unsigned char row, unsigned char col, unsigned char state){

  if(CheckNeighbours(board, row, col, state) <= 3 || CheckNeighbours(board, row, col, state) == 0){

    board[row][col].state = 0;
    board[row][col].type = 0;

  }

}

void PickCell(unsigned char original_row, unsigned char original_col, unsigned char orig_gain){
  
  signed char horizontal_movement;
  signed char vertical_movement;
  
  unsigned char next_row;
  unsigned char next_col;
  
  signed char new_gain;
  signed char new_gain2;
  
  do{

    horizontal_movement = rand()%(search_range + 1);
    
    if(search_range - horizontal_movement == 0){
    
      vertical_movement = 0;
    
    }else{
      
      vertical_movement = rand()%(search_range - horizontal_movement);
      
    }
    
    if(rand()%2 == 0){
      
      horizontal_movement *= -1;
      
    }
    
    if(rand()%2 == 0){
      
      vertical_movement *= -1;
      
    }
    
    next_row = CheckSingleNeighbour(original_row, vertical_movement);
    next_col = CheckSingleNeighbour(original_col, horizontal_movement);
    
  }while(horizontal_movement == 0 && vertical_movement == 0); 
  
  if(8 != CheckNeighbours(board, next_row, next_col, board[next_row][next_col].state) &&
                          board[next_row][next_col].state != board[original_row][original_col].state){
    
    // Gain in the new cell position
    new_gain = TemporalSwap(original_row, original_col, board[original_row][original_col].state,
                            next_row, next_col, board[next_row][next_col].state);
      
    new_gain -= orig_gain;

    if(0 == board[next_row][next_col].state){

      if(new_gain >= 0 || (new_gain == -1 && rand()%chance_to_move == 21)){
        
        SwapCells(original_row, original_col, board[original_row][original_col].state,
                  next_row, next_col,
                  board[next_row][next_col].state);
                  
      }
      
    }else{

      new_gain2 = CalculateGain(original_row, original_col, next_row, next_col);
      
      new_gain += new_gain2;
      
      if(new_gain >= 0 || ((new_gain == -1 || new_gain == -2) && rand()%chance_to_move == 21)){
        
        SwapCells(original_row, original_col, board[original_row][original_col].state,
                  next_row, next_col,
                  board[next_row][next_col].state);
                  
      }
      
    }
    
  }
  
}

void ChangeTileType(STile board[size][size], unsigned char row, unsigned char col, unsigned char state){

  if(state == 1 || state == 2 || state == 3 || state == 5){

    switch(CheckCrossNeighbours(board, row, col, state)){

      case 4:

        if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].state != state){ board[row][col].type = 11; }   // Upper-Left
        if(board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, +1)].state != state){ board[row][col].type = 12; }   // Upper-Right
        if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, -1)].state != state){ board[row][col].type = 10; }   // Lower-Left
        if(board[CheckSingleNeighbour(row, +1)][CheckSingleNeighbour(col, +1)].state != state){ board[row][col].type = 9; }   // Lower-Right

      break;

      case 3:

      if(board[CheckSingleNeighbour(row, -1)][col].state != state){ board[row][col].type = 2; }                             // Upper
      if(board[row][CheckSingleNeighbour(col, -1)].state != state){ board[row][col].type = 8; }                             // Left
      if(board[row][CheckSingleNeighbour(col, +1)].state != state){ board[row][col].type = 4; }                             // Right
      if(board[CheckSingleNeighbour(row, +1)][col].state != state){ board[row][col].type = 6; }                             // Lower

      break;

      case 2:

      if(board[CheckSingleNeighbour(row, -1)][col].state != state &&
         board[row][CheckSingleNeighbour(col, -1)].state != state){ board[row][col].type = 1; }                             // Upper & Left
      if(board[CheckSingleNeighbour(row, -1)][col].state != state &&
         board[row][CheckSingleNeighbour(col, +1)].state != state){ board[row][col].type = 3; }                             // Upper & Right

      if(board[CheckSingleNeighbour(row, +1)][col].state != state &&
         board[row][CheckSingleNeighbour(col, -1)].state != state){ board[row][col].type = 7; }                             // Lower & Left
      if(board[CheckSingleNeighbour(row, +1)][col].state != state &&
         board[row][CheckSingleNeighbour(col, +1)].state != state){ board[row][col].type = 5; }                             // Lower & Right

      break;

    }

  }

   // Snow
  if(state == 3){

    // Stairs
    if(board[row][col].type == 6 && rand()%50 == 7){
      
      board[row][col].type = 13;
      
    }

    /*if(CheckNeighbours(board, row, col, state) == 8 && rand()%10 == 7 &&
       board[CheckSingleNeighbour(row, +1)][col].type != 6){ board[row][col].type = 14; }  */  

    if(board[row][col].type == 0 && board[CheckSingleNeighbour(row, +1)][col].type != 6 &&
       rand()%10 == 7){ board[row][col].type = 15; }

    if(CheckNeighbours(board, row, col, state) == 8 && 
       CheckNeighboursType(board, row, col, state, board[row][col].type) == 0 &&
       rand()%10 == 7){
     
      board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].type = 16;
      board[CheckSingleNeighbour(row, -1)][col].type = 17;
      board[row][CheckSingleNeighbour(col, -1)].type = 18;
      board[row][col].type = 19;
         
    }
       
  }

  // Deep Water
  if(state == 1){

    if(CheckNeighbours(board, row, col, state) == 8 && 
       CheckNeighboursType(board, row, col, state, 0) == 0 &&
       rand()%10 == 7){
     
      board[CheckSingleNeighbour(row, -1)][CheckSingleNeighbour(col, -1)].type = 13;
      board[CheckSingleNeighbour(row, -1)][col].type = 14;
      board[row][CheckSingleNeighbour(col, -1)].type = 15;
      board[row][col].type = 16;
         
    }

  }

  // Grass
  if(state == 4){

    if(rand()%50 == 7){ board[row][col].type = 2+(rand()%4); }

  }

}

void SelectCasilla(){
  
  unsigned int max_repeats = size*size;
  unsigned char rand_row;
  unsigned char rand_col;
  unsigned char gain;
  int c = size;
  
  while(repeats < max_repeats * 1024){
    
    rand_row = rand()%kNumRows;
    rand_col = rand()%kNumCols;
    
    gain = CheckNeighbours(board, rand_row, rand_col, board[rand_row][rand_col].state);
    
      if(gain != 8 && board[rand_row][rand_col].state != 0){       
        PickCell(rand_row, rand_col, gain);
      
      }

    ++repeats;
    
  }

  for(int n = 0; n < 2; ++n){

    for(int i = 0; i < size; ++i){

      for(int j = 0; j < size; ++j){

        EraseTile(board, i, j, board[i][j].state);

      }

    }

  }

  for(int n = 0; n < 1; ++n){

    for(int i = 0; i < size; ++i){

      for(int j = 0; j < size; ++j){

        ChangeTileType(board, i, j, board[i][j].state);

      }

    }

  }
  
}

void DrawCharacter(SDL_Renderer *renderer){
 
  SDL_SetRenderDrawColor(renderer,0,255,0,255);
  
  SDL_Rect aux_rect = Character.info_body;
  
  aux_rect.x = Character.info_body.x * kWindowWidth/kNumCols + 4;
  aux_rect.y = Character.info_body.y * kWindowHeight/kNumRows + 4;
  
  SDL_RenderFillRect(renderer, &aux_rect);
  SDL_RenderDrawRect(renderer, &aux_rect);
  
}

bool ExitWindow(SDL_Event event_key){

  if (event_key.key.keysym.sym == SDLK_ESCAPE)
  {
    return true;
  }
  return false;
}

int main(int argc, char **argv) {

  
  CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
  srand(time(NULL));

  // Create an SDL window
  SDL_Window *window = SDL_CreateWindow("Antekeland 2077", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWindowWidth, kWindowHeight, SDL_WINDOW_OPENGL);
  CHECK_ERROR(window == NULL, SDL_GetError());

  // Create a renderer (accelerated and in sync with the display refresh rate)
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
  CHECK_ERROR(renderer == NULL, SDL_GetError());

  // Initial renderer color
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  //Init Funcs 
  TTF_Init();
  int flags= IMG_INIT_PNG;
  IMG_Init(flags);

  // SDL_Surface* image = IMG_Load("../data/resources/tilemap1.png");
  SDL_Surface* image = IMG_Load("../data/resources/tileset.png");
  ricardo = SDL_CreateTextureFromSurface(renderer, image);
  
  // tilemap.loadTexture("../data/resources/tilemap1.png", renderer);

 // SDL_Surface* image = IMG_Load("../data/skins/body/male/dark.png");
  // ¡;

  const unsigned char fps=60;
  double current_time,last_time;
  bool ordenar = false;

  CreateBoard();
  InitCharacter();
  
  bool running = true;
  SDL_Event event;
  while(running) {

    last_time = SDL_GetTicks();


    // Inputs events
    while(SDL_PollEvent(&event)) {
      running = !((event.type == SDL_QUIT) || ExitWindow(event));
      if(event.key.keysym.sym == SDLK_SPACE){ ordenar = true; }
      //ChangeOutfit(&menu_level,&char_outfit, renderer);
    }

    DrawBorad(renderer);
    //Update
    if(ordenar){
    SelectCasilla();
    ordenar = false;
    }
    

    // Clear screen

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    // Draw Events
    DrawBorad(renderer);  
    //DrawCharacter(renderer);
      
    // Show what was drawn
    SDL_RenderPresent(renderer);

    do{
      current_time = SDL_GetTicks();
    }while((current_time - last_time) <= (1000.0/fps));
  }

  // Release resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}