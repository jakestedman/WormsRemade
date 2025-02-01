#include <iostream>
#include <SDL_image.h>

#include "Coordinator.hpp"
#include "WindowManager.hpp"
#include "Logger.hpp"

/*
std::unique_ptr<GameObject> player; // cannot be changed so could be shared
std::unique_ptr<Map> map;
*/

extern Coordinator g_coordinator;

void WindowManager::Init(const char* title, const unsigned int x_pos, const unsigned int y_pos, const unsigned int width, const unsigned int height, bool fullscreen)
{
    // To update to resize, for now, always fullscreen
    unsigned int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        LOGERR(SDL_GetError());

        Quit();
    }
    LOG("SDL initialized.");

    m_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);  

    if(!m_window)
    {
        LOGERR(SDL_GetError());

        Quit();
    }

    LOG("Window created.");
}

void WindowManager::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        LOG("Quitting..");

        Quit();
        break;
    
    default:
        break;
    }
}

void WindowManager::Quit()
{
    if (!m_window)
    {
        g_coordinator.SendEvent(Events::Window::QUIT);
        SDL_Quit();

        LOG("SDL cleaned up.");
    }
    else
    {
        // Destroy the window and send a quit event
        SDL_DestroyWindow(m_window);

        LOG("SDL window destroyed.");
        g_coordinator.SendEvent(Events::Window::QUIT);
        SDL_Quit();

        LOG("SDL cleaned up.");
    }
}