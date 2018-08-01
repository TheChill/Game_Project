#pragma once
#include "SDL.h"

class ColliderComponent;

class Collision {
public:
	static bool AABB(const SDL_Rect& rec_a, const SDL_Rect& rec_b);
	static bool AABB(const ColliderComponent& col_a, const ColliderComponent& col_b);
};