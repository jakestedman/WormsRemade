#include <iostream>
#include <SDL_image.h>

#include "Coordinator.hpp"
#include "WindowManager.hpp"

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
#ifdef LOG_ENABLED
        std::cerr << "WindowManager::Init - Error: " << SDL_GetError() << std::endl;
#endif

        Quit(); // No window or renderer has been initialized so use SDL_Quit instead of quit
    }

#ifdef LOG_ENABLED
    std::cout << "WindowManager::Init - SDL Initialized." << std::endl;
#endif

    m_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);  

    if(!m_window)
    {

#ifdef LOG_ENABLED
        std::cerr << "WindowManager::Init - Error: " << SDL_GetError() << std::endl;
#endif

        Quit(); // No window or renderer has been initialized so use SDL_Quit instead of quit
    }

#ifdef LOG_ENABLED
    std::cout << "WindowManager::Init - Window Created." << std::endl;
#endif
}

void WindowManager::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:

#ifdef LOG_ENABLED
        std::cout << "WindowManager::HandleEvents - Quitting.." << std::endl;
#endif 

        Quit();
        
        break;
    
    default:
        break;
    }
}

void WindowManager::Update()
{
    // player->Update();
    // manager.Update();
    // std::cout << new_player.GetComponent<PositionComponent>.GetX() << ", " << 
    // new_player.GetComponent<PositionComponent>.GetY() << std::endl;
}

void WindowManager::Render()
{
    // SDL_RenderClear(renderer);
    // map->DrawMap();
    // player->Render();
    // // this is where you add stuff to render
    // SDL_RenderPresent(renderer);
}

void WindowManager::Quit()
{
    if (!m_window)
    {
        g_coordinator.SendEvent(Events::Window::QUIT);
        SDL_Quit();

#ifdef DBG_ENABLED
        std::cout << "WindowManager::Quit - SDL Cleaned up." << std::endl;
#endif 

    }
    else
    {
        // Destroy the window and send a quit event
        SDL_DestroyWindow(m_window);

#ifdef LOG_ENABLED
        std::cout << "WindowManager::Quit - SDL Window Destroyed." << std::endl;
#endif
        g_coordinator.SendEvent(Events::Window::QUIT);
        SDL_Quit();

#ifdef LOG_ENABLED
        std::cout << "WindowManager::Quit - SDL Cleaned up." << std::endl;
#endif
    }
}