#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texture_sheet, int x, int y) {
	object_texture = TextureManager::load_texture(texture_sheet);

	x_pos = x;
	y_pos = y;
}

void GameObject::update() {
	x_pos++;
	y_pos++;

	sorce_rect.h = 32;
	sorce_rect.w = 32;
	sorce_rect.x = 0;
	sorce_rect.y = 0;

	destination_rect.x = x_pos;
	destination_rect.y = y_pos;
	destination_rect.w = sorce_rect.w;
	destination_rect.h = sorce_rect.h;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, object_texture, &sorce_rect, &destination_rect);
}

GameObject::~GameObject() {

}