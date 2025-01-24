#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "System.hpp"

/*
// Init
// Load texture
// Update
// WindowSizeListener

// Get refresh rate likely in 
// 
*/

class Event;

class RenderSystem : public System
{
public:
    void Init(SDL_Window* window);
    void LoadTextures(std::vector<std::tuple<std::string, unsigned int>> texture_data);
    void RenderTilemap(std::vector<std::vector<unsigned int>>);
    void Update(float dt);

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    void QuitListener(Event& event);
    void WindowSizeListener(Event& event);
    
    //std::unique_ptr<Shader> shader;
    Entity m_camera;

};
