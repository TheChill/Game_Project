#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect sorce_rect;
	SDL_Rect destination_rect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:


	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		set_texture(path);
	}

	SpriteComponent(const char* path, int frames, int speed) {
		animated = true;
		this->frames = frames;
		this->speed = speed;
		set_texture(path);
	}

	void set_texture(const char* path) {
		texture = TextureManager::load_texture(path);
	}

	void init() override {

		transform = &entity->get_component<TransformComponent>();

		sorce_rect.x = 0;
		sorce_rect.y = 0;
		sorce_rect.w = transform->width;
		sorce_rect.h = transform->height;
		//destination_rect.w = 32; //*2
		//destination_rect.h = 32; //*2

	}

	void update() override {
		if (animated) {
			sorce_rect.x = sorce_rect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		destination_rect.x = static_cast<int>(transform->position.x);
		destination_rect.y = static_cast<int>(transform->position.y);
		destination_rect.w = transform->width * transform->scale;
		destination_rect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::draw(texture, sorce_rect, destination_rect);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
};