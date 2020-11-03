#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#include "rect.h"

/** @brief Process mouse events for the ImGuiSDL binding.
 *
 * @param Pointer to an SDL_Event captured this frame.
 */

void Input(int* quit, SDL_Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_QUIT) {
            *quit = true;
        }
        if (event.type == SDL_WINDOWEVENT && 
            event.window.event == SDL_WINDOWEVENT_CLOSE && 
            event.window.windowID == SDL_GetWindowID(window)) {
            *quit = true;
        }
        // Add the rest of input events here: keyboard, gamepad, etc...
    }
}

// Init Rectangles
void InitRects(Rect r[]){  

  for(int i = 0; i < 12; ++i){

    r[i].init(50, 50);
    r[i].setPosition(1280, rand()%650);    
    r[i].setSolid();

    if(i < 4){

      r[i].setFillColor(rand()%85, rand()%85, rand()%85, rand()%255);
      r[i].setSpeed(1+rand()%5);

    }else if(4 <= i && i < 8){

      r[i].setFillColor(85+rand()%85, 85+rand()%85, 85+rand()%85, rand()%255);
      r[i].setSpeed(5+rand()%5);

    }else{

      r[i].setFillColor(170+rand()%85, 170+rand()%85, 170+rand()%85, rand()%255);
      r[i].setSpeed(10+rand()%5);

    }

  }

}

// Move Rectangles
void MoveRects(Rect r[]){

  for(int i = 0; i < 12; ++i){

    r[i].transform_.position.x -= r[i].speed_;

    if(r[i].transform_.position.x + r[i].width_ <= 0){

      r[i].transform_.position.x = 1280;

    }
    
  }
}

// Draw Rectangles
void DrawRects(Rect r[], SDL_Renderer* rend){

  for(int i = 0; i < 12; ++i){

    r[i].draw(rend);

  }

}

int main(int argc, char* argv[]){

  srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

  SDL_Window *win = SDL_CreateWindow("Ejercicio 10", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
  if (win == nullptr){
    //std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr){
    SDL_DestroyWindow(win);
    //std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  Rect r1[12], r2[4], r3[4];

  InitRects(r1);

  int quit = 0;
  while (!quit) {
    Input(&quit, win);

    // Move Rects
    MoveRects(r1);
      
    //First clear the renderer
    SDL_SetRenderDrawColor(ren, 0,0,0,0);
    SDL_RenderClear(ren);

    DrawRects(r1, ren);
    
    /* DrawRects(r2, ren);
    DrawRects(r3, ren); */

    //Update the screen
    SDL_RenderPresent(ren);
  }

  // Clean up our objects and quit
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

	return 0;
}