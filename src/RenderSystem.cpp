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
bool RenderSystem::Init(SDL_Window* window)
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

    if(!m_renderer)
    {
#ifdef LOG_ENABLED
        std::cerr << "RenderSystem::Init - Error: " << SDL_GetError() << std::endl;
#endif

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

    if(SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255))
    {
#ifdef LOG_ENABLED
        std::cerr << "RenderSystem::Init - Error: " << SDL_GetError() << std::endl;
#endif

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

#ifdef LOG_ENABLED
    std::cout << "RenderSystem::Init - Renderer Created." << std::endl;
#endif

    return true;
}

void RenderSystem::LoadTextures(std::vector<std::tuple<std::string, unsigned int>> texture_data)
{
    // loop through textures and
}

void RenderSystem::Update(float dt)
{    
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    // update user position
    // update tilemap for example any explosions

    SDL_RenderPresent(m_renderer);
}



/*
    Listens for quit events
*/
void RenderSystem::QuitListener(Event& event)
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);

#ifdef LOG_ENABLED
        std::cout << "RenderSystem::QuitListener - SDL Renderer Destroyed." << std::endl;
#endif
    }
    
#ifdef LOG_ENABLED
    else
    {
        std::cout << "RenderSystem::QuitListener - Nothing to do, renderer was not initialized." << std::endl;
    }
#endif
}

/*
    TODO
*/
void RenderSystem::WindowSizeListener(Event& event)
{
}
