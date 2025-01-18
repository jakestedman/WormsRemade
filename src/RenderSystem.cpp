#include <iostream>
#include <SDL.h>

#include "RenderSystem.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

extern Coordinator g_coordinator; // ??

/*
    Initialise the event listeners

    Add all entities relating to rendering

    Later on this will be passed render screens (menus, levels etc) and told to render whatever is within it.

*/
void RenderSystem::Init(SDL_Window* window)
{
    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));
    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::QUIT, RenderSystem::QuitListener));


    // Add entities here
    m_camera = g_coordinator.CreateEntity();
    g_coordinator.AddComponent(
        m_camera,
        Transform{
            .position = Vec3(0.0f, 0.0f, 0.0f)
        });

    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(m_renderer)
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        std::cout << "RenderSystem::Init - Renderer Created!" << std::endl;
    }
}

void RenderSystem::Update(float dt)
{
    
}

/*
    Listens for quit events
*/
void RenderSystem::QuitListener(Event& event)
{
    SDL_DestroyRenderer(m_renderer);
    std::cout << "RenderSystem::QuitListener - SDL Renderer Destroyed!" << std::endl;
}

/*
    TODO
*/
void RenderSystem::WindowSizeListener(Event& event)
{
}
