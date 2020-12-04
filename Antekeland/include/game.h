/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"


class Scene;

class Game {
  public:   
    //Methods
    Game();    
    ~Game();    
    
    int loadScene(int n_scene);
    
    
    void mainGame();
    void input();
    void update();
    void draw();
    
    int init();
    void quit();    

    //void ImGuiSDLProcessEvent1(SDL_Event* e);
    
    // Attributes
    SDL_Window *win_;
    SDL_Renderer *ren_;
    Scene* current_scene_[4];
    int32_t current_id_scene_;
    //int32_t previous_id_scene_;
    
  
    int quit_;
    double current_time_, last_time_;
    const unsigned char fps = 60;
    


};

#endif  // __GAME_H__