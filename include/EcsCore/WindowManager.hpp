#pragma once

#include "Logger.hpp"
#include <SDL.h>

class WindowManager
{
public:
    void Init(const char* title, const unsigned int x_pos, const unsigned int y_pos, const unsigned int width, const unsigned int height, bool fullscreen);
    void HandleEvents();
    void Quit();

    SDL_Window* GetWindow() {return m_window;}

private:
    SDL_Window* m_window = nullptr;
};