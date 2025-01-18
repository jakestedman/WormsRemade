#include <iostream>
#include <SDL_image.h>

#include "Coordinator.hpp"
#include "WindowManager.hpp"

/*
std::unique_ptr<GameObject> player; // cannot be changed so could be shared
std::unique_ptr<Map> map;
*/

extern Coordinator g_coordinator;

void WindowManager::Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
    // To update to resize, for now, always fullscreen
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "WindowManager::Init - SDL Initialized!" << std::endl;

        m_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);  

        if(m_window)
        {
            std::cout << "WindowManager::Init - Window Created!" << std::endl;
        }
        else
        {
            std::cerr << "WindowManager::Init - There was an error creating the SDL window." << std::endl;
        }
    }
}

void WindowManager::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        std::cout << "WindowManager::HandleEvents - Quitting game.." << std::endl;
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
    // Destroy the window and send a quit event
    SDL_DestroyWindow(m_window);

    std::cout << "WindowManager::Quit - SDL Window Destroyed!" << std::endl;

    g_coordinator.SendEvent(Events::Window::QUIT);
    SDL_Quit();

    std::cout << "WindowManager::Quit - SDL Cleaned up!" << std::endl;

}