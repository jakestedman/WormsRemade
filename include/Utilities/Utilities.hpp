#pragma once

#include <SDL.h>

namespace
{
    inline float hire_time_in_seconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001f;

        return t;
    } 
}