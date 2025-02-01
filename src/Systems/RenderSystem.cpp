#include <iostream>
#include <SDL.h>

#include "RenderSystem.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Renderable.hpp"
#include "Coordinator.hpp"
#include "Logger.hpp"

extern Coordinator g_coordinator; // ??
 
/*
    Initialise the event listeners

    Add all entities relating to rendering

    Later on this will be passed render screens (menus, levels etc) and told to render whatever is within it.

*/
void RenderSystem::Init(SDL_Window* window, std::vector<std::vector<unsigned int>> const& tilemap, std::vector<const char*> const& texture_paths)
{
    DEFINE_CLASS_NAME("RenderSystem")

    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));
    g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::QUIT, RenderSystem::QuitListener));

    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!m_renderer)
    {
        LOGERR(SDL_GetError());

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

    if(SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0))
    {
        LOGERR(SDL_GetError());

        g_coordinator.SendEvent(Events::Window::QUIT);
    }

    LOG("Renderer created.");

    LoadTextures(texture_paths);

    // Add entities here
    m_camera = g_coordinator.CreateEntity();
    g_coordinator.AddComponent(
        m_camera,
        Transform{
            .position = Vec2(0.0f, 0.0f)
        });

    LoadTilemap(tilemap, texture_paths);
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
        LOG(std::string("Loading texture: ") + texture_path);

        // create the texture path
        last_backslash = bin_fldr_path.rfind('/');
        second_last_backslash = bin_fldr_path.rfind('/', last_backslash - 1);
        workspace_path = bin_fldr_path.substr(0, second_last_backslash);
        whole_texture_path = workspace_path.append(texture_path);

        texture = IMG_LoadTexture(m_renderer, whole_texture_path.c_str());
        if (!texture)
        {
            LOGERR(IMG_GetError());
            LOG("Qutting..");

            Quit();

            break;
        }
        m_texture_data.push_back(texture);
    }
}

void RenderSystem::LoadTilemap(std::vector<std::vector<unsigned int>> const& tilemap, std::vector<const char*> const& texture_paths)
{
    LOG("Loading tilemap..");

    // Create tilemap entities
    for (size_t y = 0; y < tilemap.size(); y++)
    {
        for (size_t x = 0; x < tilemap[0].size(); x++)
        {
            // if we are not rendering anything in this tile skip
            if (tilemap[y][x] == 0)
            {
                continue;
            }

            // loop through all of the tile id's we have and check if this tile id matches
            for (size_t m_texture_data_index = 0; m_texture_data_index < m_texture_data.size(); m_texture_data_index++)
            {
                unsigned int tile_id = m_texture_data_index + 1;

                // if they match create a new tile component
                if (tilemap[y][x] == tile_id)
                {
                    Entity tile = g_coordinator.CreateEntity();

                    g_coordinator.AddComponent(
                        tile,
                        Transform{
                            .position = Vec2(x * 32.0f, y * 32.0f)
                        });

                    g_coordinator.AddComponent(
                        tile,
                        Renderable{
                            .texture = m_texture_data[m_texture_data_index],
                            .path = texture_paths[m_texture_data_index]
                        });
                }
            }
        }
    }

    LOG("Tilemap loaded.");
}

void RenderSystem::Update(float dt)
{    
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);


    // get each tra
    for (auto const& entity : m_entities)
    {
        auto const& transform = g_coordinator.GetComponent<Transform>(entity);
        auto const& renderable = g_coordinator.GetComponent<Renderable>(entity);

        //std::cout << "RenderSystem::Update - " << renderable.path << " to position: x " << transform.position.x << ", y " << transform.position.y << std::endl;

        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 32;
        src.h = 32;

        SDL_Rect dest;
        dest.x = transform.position.x;
        dest.y = transform.position.y;
        dest.w = 32;
        dest.h = 32;

        // SDL_Rect dst;
        // dst.x
        SDL_RenderCopy(m_renderer, renderable.texture, &src, &dest);
    }

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

        LOG("SDL renderer destroyed.");
    }
    else
    {
        LOG("Nothing to do, renderer was not initialized.");
    }
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

        LOG("SDL renderer Destroyed.");
        g_coordinator.SendEvent(Events::Window::QUIT);

        LOG("Sent quit event.");
    }
    else
    {
        g_coordinator.SendEvent(Events::Window::QUIT);
        LOG("Sent quit event.");
    }
}