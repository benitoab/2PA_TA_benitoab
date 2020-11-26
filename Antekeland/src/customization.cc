/**
 * Antekeland 2020
 * Author: Javier Benito Abolafio
 * Mail: benitoab@esat-alumni.com
 * University Development @ESAT
 */

#include "gamemanager.h"
#include "customization.h"
#include "stdio.h"

/** @brief Process mouse events for the ImGuiSDL binding.
 *
 * @param Pointer to an SDL_Event captured this frame.
 */
void ImGuiSDLProcessEvent(SDL_Event* e) {
  if (e == nullptr) return;

  ImGuiIO& io = ImGui::GetIO();

  int wheel = 0;

  while (SDL_PollEvent(e))
  {
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

void InitImGui(SDL_Renderer* ren){

  GameManager& gM = GameManager::Instantiate();

  /*gM.window_flags |= ImGuiWindowFlags_NoMove;
  gM.window_flags |= ImGuiWindowFlags_NoResize;
  gM.window_flags |= ImGuiWindowFlags_NoCollapse;*/

  ImGui::CreateContext();
	ImGuiSDL::Initialize(ren, gM.kWindowWidth, gM.kWindowHeight);

}

void UpdateImGui(){

  GameManager& gM = GameManager::Instantiate();
  float size;  
  
  // Start the Dear ImGui frame
  ImGui::NewFrame();
  // ImGui::SetNextWindowPos(ImVec2(gM.kWindowWidth/2, gM.kWindowHeight/2), 0, ImVec2(0.5, 0.5));
  ImGui::SetNextWindowSize(ImVec2(gM.kImGuiWidth, gM.kImGuiHeight));
  ImGui::Begin("Antekeland", NULL, gM.window_flags);
  size = ImGui::GetWindowWidth();
  // ImGui::ShowDemoWindow();

  ImGui::SameLine(100);
  // Gender
  ImGui::Text("Select Gender");
  ImGui::RadioButton("Male", &gender, 1); ImGui::SameLine();
  ImGui::RadioButton("Female", &gender, 2);

  // Skins
  ImGui::Text("Select Skin");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##leftskin", ImGuiDir_Left)) {
    --skin_index;
    if(skin_index <= 0){ skin_index = 9; skin_index%=10; }
  }
  ImGui::SameLine();
  ImGui::Text("Skin %d", skin_index);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightskin", ImGuiDir_Right)) { skin_index%=9; ++skin_index; }
  ImGui::Text("\n");

  // Hair
  ImGui::Text("Select Hair");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##lefthair", ImGuiDir_Left)) {
    --hair_index;
    if(hair_index < 0){ hair_index = 31; hair_index%=32; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair %d", hair_index);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righthair", ImGuiDir_Right)) { ++hair_index%=32; }
  ImGui::Text("\n");

  // Hair Color
  ImGui::Text("Select Hair Color");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##leftcolor", ImGuiDir_Left)) {
    --hair_color;
    if(hair_color < 0){ hair_color = 31; hair_color%=32; }
  }
  ImGui::SameLine();
  ImGui::Text("Hair Color %d", hair_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightcolor", ImGuiDir_Right)) { ++hair_color%=32; }
  ImGui::Text("\n");

  // Ears Type
  ImGui::Text("Select Ears");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##leftear", ImGuiDir_Left)) {
    --ears_index;
    if(ears_index < 0){ ears_index = 2; ears_index%=3; }
  }
  ImGui::SameLine();
  ImGui::Text("Ears %d", ears_index);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightear", ImGuiDir_Right)) { ++ears_index%=3; }
  ImGui::Text("\n");

  // Nose Type
  ImGui::Text("Select Nose");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##leftnose", ImGuiDir_Left)) {
    --nose_index;
    if(nose_index < 0){ nose_index = 3; nose_index%=4; }
  }
  ImGui::SameLine();
  ImGui::Text("Nose %d", nose_index);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##rightnose", ImGuiDir_Right)) { ++nose_index%=4; }
  ImGui::Text("\n");

  // Eyes Color
  ImGui::Text("Select Eyes Color");
  ImGui::AlignTextToFramePadding();
  if (ImGui::ArrowButton("##lefteye", ImGuiDir_Left)) {
    --eyes_color;
    if(eyes_color < 0){ eyes_color = 9; eyes_color%=10; }
  }
  ImGui::SameLine();
  ImGui::Text("Eyes Color %d", eyes_color);
  ImGui::SameLine();
  if(ImGui::ArrowButton("##righteye", ImGuiDir_Right)) { ++eyes_color%=10; }
  ImGui::Text("\n");

  ImGui::End();

}

void DrawImGui(){

  //ImGui
  ImGui::Render();  
  ImGuiSDL::Render(ImGui::GetDrawData());

}

void QuitImGui(){

  ImGuiSDL::Deinitialize();
  ImGui::DestroyContext();

}