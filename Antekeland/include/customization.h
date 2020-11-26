/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __CUSTOMIZATION_H__
#define __CUSTOMIZATION_H__

#include "SDL.h"

static int gender = 0;
static int skin_index = 1;
static int hair_index = 1;
static int hair_color = 1;
static int ears_index = 0;
static int nose_index = 0;
static int eyes_color = 0;

void ImGuiSDLProcessEvent(SDL_Event* e);
void InitImGui(SDL_Renderer* ren);
void UpdateImGui();
void DrawImGui();
void QuitImGui();

#endif  // __CUSTOMIZATION_H__