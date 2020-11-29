/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __CUSTOMIZATION_H__
#define __CUSTOMIZATION_H__

#include "SDL.h"
#include "gamemanager.h"
#include "imgui_internal.h"
#include <string>

static ImFont* newFont;

void ImGuiSDLProcessEvent(SDL_Event* e);
void InitCustomization(SDL_Renderer* ren);
void DrawCharacter(SDL_Renderer* ren, Character c);
void CustomizeCharacter(Character *c);
void DrawCustomization();
void QuitCustomization();

#endif  // __CUSTOMIZATION_H__