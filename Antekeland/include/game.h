/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"

class Game {
  public:   
    //Methods
    Game();    
    ~Game();    
    
    Scene* LoadScene(Scene* new_scene);
    
    
    void game();
    void input();
    void update();
    void draw();
    
    int init();
    void quit();    

    void ImGuiSDLProcessEvent1(SDL_Event* e);
    
    // Attributes
    SDL_Window *win_;
    SDL_Renderer *ren_;
    Scene* current_scene_;
    Scene* previous_scene_;
    int quit_;
    double current_time_, last_time_;
    const unsigned char fps = 60;
    bool show = true;

};

#endif  // __GAME_H__