#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rec_a, const SDL_Rect& rec_b) {
	if (rec_a.x + rec_a.w >= rec_b.x &&
		rec_b.x + rec_b.w >= rec_a.x &&
		rec_a.y + rec_a.h >= rec_b.y &&
		rec_b.y + rec_b.h >= rec_a.y) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::AABB(const ColliderComponent& col_a, const ColliderComponent& col_b) {
	if (AABB(col_a.collider, col_b.collider)) {
		std::cout << col_a.tag << "hit: " << col_b.tag << std::endl;
		return true;
	}
	else {
		return false;
	}
}
