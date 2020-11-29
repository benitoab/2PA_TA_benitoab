/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include "gamemanager.h"
#include "customization.h"
#include "stdio.h"
#include <stdlib.h>
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

void DrawCharacter(SDL_Renderer* ren, Character c){

  SDL_Rect fsrc_rect = {0,128,64,64};
  SDL_Rect fdest_rect = {310,637,64,64};

  SDL_Rect bsrc_rect = {0,0,64,64};
  SDL_Rect bdest_rect = {490,637,64,64};

  SDL_Rect lsrc_rect = {0,64,64,64};
  SDL_Rect ldest_rect = {666,637,64,64};

  SDL_Rect rsrc_rect = {0,192,64,64};
  SDL_Rect rdest_rect = {840,637,64,64};
  
  // Body Path
  std::string tmp_dir = "../data/skins/body/male/body$.png";

  // Set Gender
  if(c.skin_id_.gender == 2){

    tmp_dir.replace(tmp_dir.find("male"), 4, "female");

  }

  // Set Body  
  tmp_dir.replace(tmp_dir.find("$"), 1, std::to_string(c.skin_id_.skin)); 
  char* skin_dir = (char*)malloc(tmp_dir.length());
  strcpy(skin_dir, tmp_dir.c_str());

  // Set Hair
  std::string tmp_hair = "../data/skins/hair/hair ($).png";
  tmp_hair.replace(tmp_hair.find("$"), 1, std::to_string(c.skin_id_.hair));  
  char* hair_dir = (char*)malloc(tmp_hair.length());
  strcpy(hair_dir, tmp_hair.c_str());

  // Set Hair Color
  std::string tmp_hair_color = "../data/skins/hair/hairs/hair ($)/color (%).png";
  tmp_hair_color.replace(tmp_hair_color.find("$"), 1, std::to_string(c.skin_id_.hair));
  tmp_hair_color.replace(tmp_hair_color.find("%"), 1, std::to_string(c.skin_id_.hair_color));
  char* haircolor_dir = (char*)malloc(tmp_hair_color.length());
  strcpy(haircolor_dir, tmp_hair_color.c_str());  

  // Set Eyes Color
  std::string tmp_eyes = "../data/skins/body/male/eyes/$.png";
  tmp_eyes.replace(tmp_eyes.find("$"), 1, std::to_string(c.skin_id_.eyes));
  char* eyes_dir = (char*)malloc(tmp_eyes.length());
  strcpy(eyes_dir, tmp_eyes.c_str());

  // Set Nose
  std::string tmp_nose = "../data/skins/body/male/nose/$-%.png";
  tmp_nose.replace(tmp_nose.find("$"), 1, std::to_string(c.skin_id_.skin));
  tmp_nose.replace(tmp_nose.find("%"), 1, std::to_string(c.skin_id_.nose));
  char* nose_dir = (char*)malloc(tmp_nose.length());
  strcpy(nose_dir, tmp_nose.c_str());

  // Set Nose
  std::string tmp_ears = "../data/skins/body/male/ears/$-%.png";
  tmp_ears.replace(tmp_ears.find("$"), 1, std::to_string(c.skin_id_.skin));
  tmp_ears.replace(tmp_ears.find("%"), 1, std::to_string(c.skin_id_.ears));
  char* ears_dir = (char*)malloc(tmp_ears.length());
  strcpy(ears_dir, tmp_ears.c_str());

  // Set Beard
  std::string tmp_beard = "../data/skins/facial/beard/color ($).png";
  tmp_beard.replace(tmp_beard.find("$"), 1, std::to_string(c.skin_id_.beard));
  char* beard_dir = (char*)malloc(tmp_beard.length());
  strcpy(beard_dir, tmp_beard.c_str());

  // Set Mustache
  std::string tmp_mustache = "../data/skins/facial/mustache ($).png";
  tmp_mustache.replace(tmp_mustache.find("$"), 1, std::to_string(c.skin_id_.mustache));
  char* mustache_dir = (char*)malloc(tmp_mustache.length());
  strcpy(mustache_dir, tmp_mustache.c_str());

  // Set Mustache Color
  std::string tmp_mustachecolor = "../data/skins/facial/mustaches/mustache ($)/color (%).png";
  tmp_mustachecolor.replace(tmp_mustachecolor.find("$"), 1, std::to_string(c.skin_id_.mustache));
  tmp_mustachecolor.replace(tmp_mustachecolor.find("%"), 1, std::to_string(c.skin_id_.mustache_color));  
  char* mcolor_dir = (char*)malloc(tmp_mustachecolor.length());
  strcpy(mcolor_dir, tmp_mustachecolor.c_str());

  // Set Torso
  std::string tmp_torso = "../data/skins/torso/clothes/piece ($).png";
  tmp_torso.replace(tmp_torso.find("$"), 1, std::to_string(c.skin_id_.torso));
  char* torso_dir = (char*)malloc(tmp_torso.length());
  strcpy(torso_dir, tmp_torso.c_str());

  // Set Cape
  std::string tmp_cape = "../data/skins/torso/back/capes/piece ($).png";
  tmp_cape.replace(tmp_cape.find("$"), 1, std::to_string(c.skin_id_.cape));
  char* cape_dir = (char*)malloc(tmp_cape.length());
  strcpy(cape_dir, tmp_cape.c_str());

  // Set Legs
  std::string tmp_legs = "../data/skins/legs/clothes/piece ($).png";
  tmp_legs.replace(tmp_legs.find("$"), 1, std::to_string(c.skin_id_.legs));
  // std::cout << tmp_legs << "\n";
  char* legs_dir = (char*)malloc(tmp_legs.length());
  strcpy(legs_dir, tmp_legs.c_str());
  
  // Body
  SDL_Surface* image = IMG_Load(skin_dir);
  SDL_Texture* skins_to_draw = SDL_CreateTextureFromSurface(ren, image);  

  // Hair
  SDL_Surface* hair = IMG_Load(hair_dir);
  SDL_Texture* hair_to_draw = SDL_CreateTextureFromSurface(ren, hair);  

  // Hair Color
  SDL_Surface* hair_color = IMG_Load(haircolor_dir);
  SDL_Texture* haircolor_to_draw = SDL_CreateTextureFromSurface(ren, hair_color);  

  // Eyes Color
  SDL_Surface* eyes = IMG_Load(eyes_dir);
  SDL_Texture* eyes_to_draw = SDL_CreateTextureFromSurface(ren, eyes);

  // Nose
  SDL_Surface* nose = IMG_Load(nose_dir);
  SDL_Texture* nose_to_draw = SDL_CreateTextureFromSurface(ren, nose);

  // Ears
  SDL_Surface* ears = IMG_Load(ears_dir);
  SDL_Texture* ears_to_draw = SDL_CreateTextureFromSurface(ren, ears);

  // Beard
  SDL_Surface* beard = IMG_Load(beard_dir);
  SDL_Texture* beard_to_draw = SDL_CreateTextureFromSurface(ren, beard);

  // Mustache
  SDL_Surface* mustache = IMG_Load(mustache_dir);
  SDL_Texture* mustache_to_draw = SDL_CreateTextureFromSurface(ren, mustache);

  // Mustache
  SDL_Surface* mustache_color = IMG_Load(mcolor_dir);
  SDL_Texture* mcolor_to_draw = SDL_CreateTextureFromSurface(ren, mustache_color);

  // Torso
  SDL_Surface* torso = IMG_Load(torso_dir);
  SDL_Texture* torso_to_draw = SDL_CreateTextureFromSurface(ren, torso);

  // Cape
  SDL_Surface* cape = IMG_Load(cape_dir);
  SDL_Texture* cape_to_draw = SDL_CreateTextureFromSurface(ren, cape);

  // Legs
  SDL_Surface* legs = IMG_Load(legs_dir);
  SDL_Texture* legs_to_draw = SDL_CreateTextureFromSurface(ren, legs);
  
  // Front View
  SDL_RenderCopy(ren, skins_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, hair_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, haircolor_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, eyes_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, nose_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, ears_to_draw, &fsrc_rect, &fdest_rect);
  SDL_RenderCopy(ren, beard_to_draw, &fsrc_rect, &fdest_rect); 
  SDL_RenderCopy(ren, mustache_to_draw, &fsrc_rect, &fdest_rect); 
  SDL_RenderCopy(ren, mcolor_to_draw, &fsrc_rect, &fdest_rect); 
  SDL_RenderCopy(ren, torso_to_draw, &fsrc_rect, &fdest_rect); 
  SDL_RenderCopy(ren, legs_to_draw, &fsrc_rect, &fdest_rect); 
  SDL_RenderCopy(ren, cape_to_draw, &fsrc_rect, &fdest_rect); 

  // Back View
  SDL_RenderCopy(ren, skins_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, hair_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, haircolor_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, eyes_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, nose_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, ears_to_draw, &bsrc_rect, &bdest_rect);
  SDL_RenderCopy(ren, beard_to_draw, &bsrc_rect, &bdest_rect); 
  SDL_RenderCopy(ren, mustache_to_draw, &bsrc_rect, &bdest_rect); 
  SDL_RenderCopy(ren, mcolor_to_draw, &bsrc_rect, &bdest_rect); 
  SDL_RenderCopy(ren, torso_to_draw, &bsrc_rect, &bdest_rect); 
  SDL_RenderCopy(ren, legs_to_draw, &bsrc_rect, &bdest_rect); 
  SDL_RenderCopy(ren, cape_to_draw, &bsrc_rect, &bdest_rect); 

  // Left View
  SDL_RenderCopy(ren, skins_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, hair_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, haircolor_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, eyes_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, nose_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, ears_to_draw, &lsrc_rect, &ldest_rect);
  SDL_RenderCopy(ren, beard_to_draw, &lsrc_rect, &ldest_rect); 
  SDL_RenderCopy(ren, mustache_to_draw, &lsrc_rect, &ldest_rect); 
  SDL_RenderCopy(ren, mcolor_to_draw, &lsrc_rect, &ldest_rect); 
  SDL_RenderCopy(ren, torso_to_draw, &lsrc_rect, &ldest_rect); 
  SDL_RenderCopy(ren, legs_to_draw, &lsrc_rect, &ldest_rect); 
  SDL_RenderCopy(ren, cape_to_draw, &lsrc_rect, &ldest_rect); 

  // Right View
  SDL_RenderCopy(ren, skins_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, hair_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, haircolor_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, eyes_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, nose_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, ears_to_draw, &rsrc_rect, &rdest_rect);
  SDL_RenderCopy(ren, beard_to_draw, &rsrc_rect, &rdest_rect); 
  SDL_RenderCopy(ren, mustache_to_draw, &rsrc_rect, &rdest_rect); 
  SDL_RenderCopy(ren, mcolor_to_draw, &rsrc_rect, &rdest_rect); 
  SDL_RenderCopy(ren, torso_to_draw, &rsrc_rect, &rdest_rect); 
  SDL_RenderCopy(ren, legs_to_draw, &rsrc_rect, &rdest_rect); 
  SDL_RenderCopy(ren, cape_to_draw, &rsrc_rect, &rdest_rect); 

  SDL_FreeSurface(image);
  SDL_FreeSurface(hair);
  SDL_FreeSurface(hair_color);
  SDL_FreeSurface(eyes);
  SDL_FreeSurface(nose);
  SDL_FreeSurface(ears);
  SDL_FreeSurface(beard);
  SDL_FreeSurface(mustache);
  SDL_FreeSurface(mustache_color);
  SDL_FreeSurface(torso);
  SDL_FreeSurface(legs);
  SDL_FreeSurface(cape);

  SDL_DestroyTexture(skins_to_draw);
  SDL_DestroyTexture(hair_to_draw);
  SDL_DestroyTexture(haircolor_to_draw);
  SDL_DestroyTexture(eyes_to_draw);
  SDL_DestroyTexture(nose_to_draw);
  SDL_DestroyTexture(ears_to_draw);
  SDL_DestroyTexture(beard_to_draw);
  SDL_DestroyTexture(mustache_to_draw);
  SDL_DestroyTexture(mcolor_to_draw);
  SDL_DestroyTexture(torso_to_draw);
  SDL_DestroyTexture(legs_to_draw);
  SDL_DestroyTexture(cape_to_draw);
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
    if(c->skin_id_.hair < 0){ c->skin_id_.hair = 30; c->skin_id_.hair%=31; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair %d", c->skin_id_.hair);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righthair", ImGuiDir_Right)) { ++c->skin_id_.hair%=31; }
  ImGui::Text("\n");

  // Hair Color
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Hair Color");
  if (ImGui::ArrowButton("##leftcolor", ImGuiDir_Left)) {
    --c->skin_id_.hair_color;
    if(c->skin_id_.hair_color < 0){ c->skin_id_.hair_color = 29; c->skin_id_.hair_color%=30; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair Color %d", c->skin_id_.hair_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightcolor", ImGuiDir_Right)) { ++c->skin_id_.hair_color%=30; }
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
    if(c->skin_id_.beard < 0){ c->skin_id_.beard = 29; c->skin_id_.beard%=30; }
  }
  ImGui::SameLine();
  ImGui::Text("Beard %d", c->skin_id_.beard);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightbeard", ImGuiDir_Right)) { ++c->skin_id_.beard%=30; }
  ImGui::Text("\n");

  // Mustache
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Mustache");
  if (ImGui::ArrowButton("##leftmustache", ImGuiDir_Left)) {
    --c->skin_id_.mustache;
    if(c->skin_id_.mustache < 0){ c->skin_id_.mustache = 4; c->skin_id_.mustache%=5; }
  }
  ImGui::SameLine();
  ImGui::Text("Mustache %d", c->skin_id_.mustache);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightmustache", ImGuiDir_Right)) { ++c->skin_id_.mustache%=5; }
  ImGui::Text("\n");

  // Mustache Color
  ImGui::TextColored(ImVec4(0.79f, 0.63f, 0.96f, 1.0f), "Select Mustache Color");
  if (ImGui::ArrowButton("##leftmustachecolor", ImGuiDir_Left)) {
    --c->skin_id_.mustache_color;
    if(c->skin_id_.mustache_color < 0){ c->skin_id_.mustache_color = 29; c->skin_id_.mustache_color%=30; }
  }
  ImGui::SameLine();
  ImGui::Text("Mustache %d", c->skin_id_.mustache_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightmustachecolor", ImGuiDir_Right)) { ++c->skin_id_.mustache_color%=30; }
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
    if(c->skin_id_.legs < 0){ c->skin_id_.legs = 10; c->skin_id_.legs%=11; }
  }
  ImGui::SameLine();
  ImGui::Text("Pants %d", c->skin_id_.legs);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightleg", ImGuiDir_Right)) { ++c->skin_id_.legs%=11; }
  ImGui::Text("\n");

  // Randomize
  if(ImGui::Button("Randomize Character")){

    c->skin_id_.gender = 1+(rand()%2);
    c->skin_id_.skin = 1+ (rand()%7);
    c->skin_id_.hair = rand()%31;
    c->skin_id_.hair_color = rand()%30;
    c->skin_id_.ears = rand()%3;
    c->skin_id_.nose = rand()%4;
    c->skin_id_.eyes = rand()%9;
    c->skin_id_.beard = rand()%30;
    c->skin_id_.mustache = rand()%5;
    c->skin_id_.mustache_color = 1+(rand()%29);
    c->skin_id_.torso = rand()%39;
    c->skin_id_.cape = rand()%24;
    c->skin_id_.legs = rand()%11;

  } 

  ImGui::EndColumns();

  ImGui::End();

  ImGui::SetNextWindowSize(ImVec2(150, 150));
  ImGui::Begin("Preview Front", NULL, gM.window_flags);
  ImGui::End();

  ImGui::SetNextWindowSize(ImVec2(150, 150));
  ImGui::Begin("Preview Back", NULL, gM.window_flags);
  ImGui::End();

  ImGui::SetNextWindowSize(ImVec2(150, 150));
  ImGui::Begin("Preview Left", NULL, gM.window_flags);
  ImGui::End();

  ImGui::SetNextWindowSize(ImVec2(150, 150));
  ImGui::Begin("Preview Right", NULL, gM.window_flags);
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