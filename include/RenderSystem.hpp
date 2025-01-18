#pragma once

#include <SDL.h>
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
    // void LoadTexture();
    void Update(float dt);

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_is_running;

    void QuitListener(Event& event);
    void WindowSizeListener(Event& event);
    
    //std::unique_ptr<Shader> shader;
    Entity m_camera;

};
