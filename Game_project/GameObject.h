#pragma once
#include "Game.h"

class GameObject {
private:
	int x_pos;
	int y_pos;

	SDL_Texture* object_texture;
	SDL_Rect sorce_rect;
	SDL_Rect destination_rect;
	
public:
	GameObject(const char* texture_sheet, int x, int y);

	void update();
	void render();

	~GameObject();
};