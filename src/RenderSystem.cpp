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
void RenderSystem::Init(SDL_Window* window, std::vector<std::vector<unsigned int>> const& tilemap, std::vector<const char*> const& texture_paths)
{
    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));
    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::QUIT, RenderSystem::QuitListener));

    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!m_renderer)
    {
#ifdef LOG_ENABLED
        std::cerr << "RenderSystem::Init - Error: " << SDL_GetError() << std::endl;
#endif

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

    if(SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0))
    {
#ifdef LOG_ENABLED
        std::cerr << "RenderSystem::Init - Error: " << SDL_GetError() << std::endl;
#endif

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

#ifdef LOG_ENABLED
    std::cout << "RenderSystem::Init - Renderer Created." << std::endl;
#endif

    LoadTextures(texture_paths);

    // Add entities here
    m_camera = g_coordinator.CreateEntity();
    g_coordinator.AddComponent(
        m_camera,
        Transform{
            .position = Vec3(0.0f, 0.0f, 0.0f)
        });

}

/*
    Because textures are only loaded once when the game launches, the speed of loading
    a texture and adding it to the vector does not matter.

    Only access speed matters.
*/
void RenderSystem::LoadTextures(std::vector<const char*> const& texture_paths)
{
    SDL_Texture* texture;
    std::string bin_fldr_path = std::filesystem::current_path();
    std::string workspace_path;
    std::string whole_texture_path;
    unsigned int last_backslash;
    unsigned int second_last_backslash;
    
    // load the textures and add them to the texture data vector
    for (const char* texture_path : texture_paths)
    {
#ifdef LOG_ENABLED
        std::cout << "RenderSystem::LoadTextures - Loading texture: " << texture_path << std::endl;
#endif
        // create the texture path
        last_backslash = bin_fldr_path.rfind('/');
        second_last_backslash = bin_fldr_path.rfind('/', last_backslash - 1);
        workspace_path = bin_fldr_path.substr(0, second_last_backslash);
        whole_texture_path = workspace_path.append(texture_path);

        texture = IMG_LoadTexture(m_renderer, whole_texture_path.c_str());
        if (!texture)
        {
#ifdef LOG_ENABLED
            std::cerr << "RenderSystem::LoadTextures - Error: " << IMG_GetError() << std::endl;
            std::cout << "RenderSystem::LoadTextures - Quitting.." << std::endl;
#endif 
            Quit();
            break;
        }
        m_texture_data.push_back(texture);
    }
}

void RenderSystem::Update(float dt)
{    
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

/*
    // get each tra
    for (auto const& entity : m_entities)
    {
        auto const& transform = g_coordinator.GetComponent<Transform>(entity);
        auto const& renderable = g_coordinator.GetComponent<Renderable>(entity);
    }
*/
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

void RenderSystem::Quit()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);

#ifdef LOG_ENABLED
        std::cout << "RenderSystem::QuitListener - SDL Renderer Destroyed." << std::endl;
#endif
        g_coordinator.SendEvent(Events::Window::QUIT);

#ifdef LOG_ENABLED
        std::cout << "RenderSystem::QuitListener - Sent quit event." << std::endl;
#endif
    }
    else
    {
        g_coordinator.SendEvent(Events::Window::QUIT);
#ifdef LOG_ENABLED
        std::cout << "RenderSystem::QuitListener - Sent quit event." << std::endl;
#endif
    }
}