/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>

class Game {
  public:   
    //Methods
    Game();    
    ~Game();    
    
    void game();
    void input();
    void update();
    void draw();
    
    int init();
    void quit();    

    void ImGuiSDLProcessEvent1(SDL_Event* e);
    //Factory
    //static GameManager* Instantiate();
    
    // Attributes
    SDL_Window *win_;
    SDL_Renderer *ren_;
    int quit_;
    double current_time_, last_time_;
 
  private: //Methods
    //static GameManager* instance_gm;
    //GameManager();
    //Atributes
  

};

#endif  // __GAME_H__