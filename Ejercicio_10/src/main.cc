#include <stdio.h>

#include <SDL.h>

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

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

  SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
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


  int quit = 0;
  while (!quit) {
    Input(&quit, win);
    
    //First clear the renderer
    SDL_RenderClear(ren);

    //Update the screen
    SDL_RenderPresent(ren);
  }

  // Clean up our objects and quit
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

	return 0;
}

