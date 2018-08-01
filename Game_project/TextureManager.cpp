#include "TextureManager.h"

SDL_Texture* TextureManager::load_texture(const char* texture_name) {
	SDL_Surface* temporary_surface = IMG_Load(texture_name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporary_surface);
	SDL_FreeSurface(temporary_surface);

	return texture;
}

void TextureManager::draw(SDL_Texture * texture, SDL_Rect source, SDL_Rect destination)
{
	SDL_RenderCopy(Game::renderer, texture, &source, &destination);
}
