#pragma once

#include "Game.h"

class TextureManager {
private:
public:
	static SDL_Texture* load_texture(const char* file_name);
	static void draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination);
};
