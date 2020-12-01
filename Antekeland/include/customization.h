/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __CUSTOMIZATION_H__
#define __CUSTOMIZATION_H__ 1

#include "SDL.h"
#include "SDL_image.h"
#include "gamemanager.h"
#include "imgui_internal.h"
#include <string>

static ImFont* newFont;
static unsigned char id_[13];
static SDL_Surface* images_[11];
static SDL_Texture* textures_[11];

void ImGuiSDLProcessEvent(SDL_Event* e);
void InitCustomization(SDL_Renderer* ren);
void SetImage(SDL_Surface** img, char* dir, unsigned char* id, int32_t skin_id, SDL_Texture** texture, SDL_Renderer* ren);
void DrawCharacter(SDL_Renderer* ren, Character c);
void CustomizeCharacter(Character *c);
void DrawCustomization();
void QuitCustomization();

#endif  // __CUSTOMIZATION_H__
