/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include "gamemanager.h"
#include "customization.h"
#include "stdio.h"
#include "string.h"
#include "SDL_image.h"

#include <iostream>
#include <string>

/** @brief Process mouse events for the ImGuiSDL binding.
 *
 * @param Pointer to an SDL_Event captured this frame.
 */
void ImGuiSDLProcessEvent(SDL_Event* e) {
  if (e == nullptr) return;

  ImGuiIO& io = ImGui::GetIO();

  int wheel = 0;

  // SDL_StartTextInput();

  while (SDL_PollEvent(e))
  {
    if(e->type == SDL_TEXTINPUT){
      io.AddInputCharactersUTF8(e->text.text);
    }
    if(e->key.keysym.sym == SDLK_BACKSPACE){
      printf("Entro\n");
      io.ClearInputCharacters();
    }
    
    if (e->type == SDL_WINDOWEVENT)
    {
      if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
        io.DisplaySize.x = static_cast<float>(e->window.data1);
        io.DisplaySize.y = static_cast<float>(e->window.data2);
      }
    }
    else if (e->type == SDL_MOUSEWHEEL)
    {
      wheel = e->wheel.y;
    }
  }

  // SDL_StopTextInput();

  int mouseX, mouseY;
  const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

  // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or 
  // write to those fields from your Windows message loop handlers, etc.)

  io.DeltaTime = 1.0f / 60.0f;
  io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
  io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
  io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
  io.MouseWheel = static_cast<float>(wheel);
}

void InitCustomization(SDL_Renderer* ren){

  GameManager& gM = GameManager::Instantiate();

  /*gM.window_flags |= ImGuiWindowFlags_NoMove;
  gM.window_flags |= ImGuiWindowFlags_NoResize;
  gM.window_flags |= ImGuiWindowFlags_NoCollapse;*/

  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  newFont = io.Fonts->AddFontFromFileTTF("../data/fonts/BreathFire.ttf", 16.0f);  
  io.Fonts->Build();

	ImGuiSDL::Initialize(ren, gM.kWindowWidth, gM.kWindowHeight);

}

/*void SetClipTexture(Sprite* skin){

  *skin->snip_rect_ = (0, 64, 64, 64);

}*/

void DrawCharacter(SDL_Renderer* ren, Character c){
  
  // Body Path
  std::string tmp_dir = "../data/skins/body/male/body$.png";

  // Set Gender
  if(c.skin_id_.gender == 2){

    tmp_dir.replace(tmp_dir.find("male"), 4, "female");

  }

  // Set Body  
  tmp_dir.replace(tmp_dir.find("$"), 1, std::to_string(c.skin_id_.skin));
  std::cout << tmp_dir << "\n";
  int length = tmp_dir.length();

  char* skin_dir = (char*)malloc(tmp_dir.length());
  strcpy(skin_dir, tmp_dir.c_str());
  
  SDL_Surface* image = IMG_Load(skin_dir);
  
  SDL_Rect src_rect = {0,128,64,64};
  SDL_Rect dest_rect = {0,0,64,64};
  
  SDL_Texture* skins_to_draw = SDL_CreateTextureFromSurface(ren, image);
    
  SDL_RenderCopy(ren, skins_to_draw, &src_rect, &dest_rect);
  SDL_FreeSurface(image);
  SDL_DestroyTexture(skins_to_draw);

  // SDL_RenderCopy(ren, texure, &src_rect, &dest_rect);
}

void CustomizeCharacter(Character *c){

  GameManager& gM = GameManager::Instantiate();
  const char* profession[] = {"Warrior", "Archer", "Sorceress", "Berserker", "Valkyrie", "Dark Knight",
                              "Healer", "Guardian", "Hashashin", "Mage"};

  // Start the Dear ImGui frame
  ImGui::NewFrame();
  // ImGui::SetNextWindowPos(ImVec2(gM.kWindowWidth/2, gM.kWindowHeight/2), 0, ImVec2(0.5, 0.5));
  ImGui::SetNextWindowSize(ImVec2(gM.kImGuiWidth/2, 320));

  ImGui::Begin("Create Character", NULL, gM.window_flags);
  ImGui::Indent(25.0f);
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Character Name");
  
  ImGui::InputText("", c->name_, 128);
  ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Choose Class");
  ImGui::ListBox("", &c->profession_, profession, IM_ARRAYSIZE(profession), 10);
  // ImGui::Combo("Class", &c->profession_, profession, IM_ARRAYSIZE(profession));

  ImGui::End();

  ImGui::SetNextWindowSize(ImVec2(gM.kImGuiWidth, gM.kImGuiHeight));
  ImGui::Begin("Antekeland", NULL, gM.window_flags);

  // Gender
  ImGui::BeginColumns("Character Creation", 2, ImGuiColumnsFlags_NoResize);  
  ImGui::Indent(15.0f);
  // ImGui::Columns(2, NULL, true);
  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Select Gender");  
  ImGui::Text("\n");
  ImGui::SameLine(10);
  ImGui::RadioButton("Male", &c->skin_id_.gender, 1); ImGui::SameLine();
  ImGui::RadioButton("Female", &c->skin_id_.gender, 2);
  ImGui::Text("\n");

  // Skins
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Skin");
  if (ImGui::ArrowButton("##leftskin", ImGuiDir_Left)) {
    --c->skin_id_.skin;
    if(c->skin_id_.skin <= 0){ c->skin_id_.skin = 7; c->skin_id_.skin%=8; }
  }
  ImGui::SameLine();
  ImGui::Text("Skin %d", c->skin_id_.skin);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightskin", ImGuiDir_Right)) { c->skin_id_.skin%=7; ++c->skin_id_.skin; }
  ImGui::Text("\n");

  // Hair
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Hair");
  if (ImGui::ArrowButton("##lefthair", ImGuiDir_Left)) {
    --c->skin_id_.hair;
    if(c->skin_id_.hair < 0){ c->skin_id_.hair = 31; c->skin_id_.hair%=32; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair %d", c->skin_id_.hair);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righthair", ImGuiDir_Right)) { ++c->skin_id_.hair%=32; }
  ImGui::Text("\n");

  // Hair Color
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Hair Color");
  if (ImGui::ArrowButton("##leftcolor", ImGuiDir_Left)) {
    --c->skin_id_.hair_color;
    if(c->skin_id_.hair_color < 0){ c->skin_id_.hair_color = 31; c->skin_id_.hair_color%=32; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair Color %d", c->skin_id_.hair_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightcolor", ImGuiDir_Right)) { ++c->skin_id_.hair_color%=32; }
  ImGui::Text("\n");

  // Ears Type
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Ears");
  if (ImGui::ArrowButton("##leftear", ImGuiDir_Left)) {
    --c->skin_id_.ears;
    if(c->skin_id_.ears < 0){ c->skin_id_.ears = 2; c->skin_id_.ears%=3; }
  }
  ImGui::SameLine();
  ImGui::Text("Ears %d", c->skin_id_.ears);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightear", ImGuiDir_Right)) { ++c->skin_id_.ears%=3; }
  ImGui::Text("\n");

  // Nose Type
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Nose");
  if (ImGui::ArrowButton("##leftnose", ImGuiDir_Left)) {
    --c->skin_id_.nose;
    if(c->skin_id_.nose < 0){ c->skin_id_.nose = 3; c->skin_id_.nose%=4; }
  }
  ImGui::SameLine();
  ImGui::Text("Nose %d", c->skin_id_.nose);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightnose", ImGuiDir_Right)) { ++c->skin_id_.nose%=4; }
  ImGui::Text("\n");

  // Eyes Color
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Eyes Color");
  if (ImGui::ArrowButton("##lefteye", ImGuiDir_Left)) {
    --c->skin_id_.eyes;
    if(c->skin_id_.eyes < 0){ c->skin_id_.eyes = 8; c->skin_id_.eyes%=9; }
  }
  ImGui::SameLine();
  ImGui::Text("Eyes Color %d", c->skin_id_.eyes);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righteye", ImGuiDir_Right)) { ++c->skin_id_.eyes%=9; }

  ImGui::NextColumn();
  ImGui::Indent(20.0f);
  // Beard
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Beard");
  if (ImGui::ArrowButton("##leftbeard", ImGuiDir_Left)) {
    --c->skin_id_.beard;
    if(c->skin_id_.beard < 0){ c->skin_id_.beard = 30; c->skin_id_.beard%=31; }
  }
  ImGui::SameLine();
  ImGui::Text("Beard %d", c->skin_id_.beard);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightbeard", ImGuiDir_Right)) { ++c->skin_id_.beard%=31; }
  ImGui::Text("\n");

  // Mustache
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Mustache");
  if (ImGui::ArrowButton("##leftmustache", ImGuiDir_Left)) {
    --c->skin_id_.mustache;
    if(c->skin_id_.mustache < 0){ c->skin_id_.mustache = 5; c->skin_id_.mustache%=6; }
  }
  ImGui::SameLine();
  ImGui::Text("Mustache %d", c->skin_id_.mustache);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightmustache", ImGuiDir_Right)) { ++c->skin_id_.mustache%=6; }
  ImGui::Text("\n");

  // Mustache Color
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Mustache Color");
  if (ImGui::ArrowButton("##leftmustachecolor", ImGuiDir_Left)) {
    --c->skin_id_.mustache_color;
    if(c->skin_id_.mustache_color < 0){ c->skin_id_.mustache_color = 30; c->skin_id_.mustache_color%=31; }
  }
  ImGui::SameLine();
  ImGui::Text("Mustache %d", c->skin_id_.mustache_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightmustachecolor", ImGuiDir_Right)) { ++c->skin_id_.mustache_color%=31; }
  ImGui::Text("\n");

  // Torso
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Top Clothes");
  if (ImGui::ArrowButton("##lefttorso", ImGuiDir_Left)) {
    --c->skin_id_.torso;
    if(c->skin_id_.torso < 0){ c->skin_id_.torso = 38; c->skin_id_.torso%=39; }
  }
  ImGui::SameLine();
  ImGui::Text("Torso %d", c->skin_id_.torso);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righttorso", ImGuiDir_Right)) { ++c->skin_id_.torso%=39; }
  ImGui::Text("\n");

  // Cape
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Cape");
  if (ImGui::ArrowButton("##leftcape", ImGuiDir_Left)) {
    --c->skin_id_.cape;
    if(c->skin_id_.cape < 0){ c->skin_id_.cape = 23; c->skin_id_.cape%=24; }
  }
  ImGui::SameLine();
  ImGui::Text("Cape %d", c->skin_id_.cape);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightcape", ImGuiDir_Right)) { ++c->skin_id_.cape%=24; }
  ImGui::Text("\n");

  // Legs
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Pants");
  if (ImGui::ArrowButton("##leftleg", ImGuiDir_Left)) {
    --c->skin_id_.legs;
    if(c->skin_id_.legs < 0){ c->skin_id_.legs = 6; c->skin_id_.legs%=7; }
  }
  ImGui::SameLine();
  ImGui::Text("Pants %d", c->skin_id_.legs);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightleg", ImGuiDir_Right)) { ++c->skin_id_.legs%=7; }
  ImGui::Text("\n");

  ImGui::EndColumns();

  ImGui::End();

}

void DrawCustomization(){

  //ImGui
  ImGui::Render();  
  ImGuiSDL::Render(ImGui::GetDrawData());

}

void QuitCustomization(){

  ImGuiSDL::Deinitialize();
  ImGui::DestroyContext();

}