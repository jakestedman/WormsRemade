#pragma once

#include <SDL.h>

class WindowManager
{
public:
    void Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Quit();

    SDL_Window* GetWindow() {return m_window;}

private:
    SDL_Window* m_window = nullptr;
};