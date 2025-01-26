#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <filesystem>

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
    void Init(SDL_Window* window, std::vector<std::vector<unsigned int>> const& tilemap, std::vector<const char*> const& texture_data);
    void LoadTextures(std::vector<const char*> const& texture_data);
    void RenderTilemap(std::vector<std::vector<unsigned int>>);
    void Update(float dt);

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::vector<SDL_Texture*> m_texture_data;

    void QuitListener(Event& event);
    void WindowSizeListener(Event& event);
    void Quit();

    //std::unique_ptr<Shader> shader;
    Entity m_camera;

};
