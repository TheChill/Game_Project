#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent * transform;
	SpriteComponent *sprite;

	SDL_Rect tile_rect;
	int tile_ID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tile_rect.x = x;
		tile_rect.y = y;
		tile_rect.w = w;
		tile_rect.h = h;
		tile_ID = id;

		switch (tile_ID)
		{
		case 0:
			path = "C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Water_shallow_mid.png";
			break;
		case 1:
			path = "C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Grass_mid.png";
			break;
		case 2:
			path = "C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Grass_south.png";
			break;
		case 3:
			path = "C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Tree_stomp.png";
			break;
		default:
			break;
		}
	}

	void init() override {
		entity->add_component<TransformComponent>((float)tile_rect.x, (float)tile_rect.y, tile_rect.w, tile_rect.h, 1);
		transform = &entity->get_component<TransformComponent>();

		entity->add_component<SpriteComponent>(path);
		sprite = &entity->get_component<SpriteComponent>();
	}
};