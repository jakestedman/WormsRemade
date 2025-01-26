#pragma once

#include <SDL_image.h>
#include "Vec2.hpp"

struct Renderable
{
	SDL_Texture* texture;
	std::string path;
};
