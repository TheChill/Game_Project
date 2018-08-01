#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& new_player(manager.add_entity());
auto& wall(manager.add_entity());

enum group_labels : std::size_t {
	group_map,
	group_players,
	group_enemies,
	group_colliders
};

Game::Game() {
	//count = 0;
}

void Game::initiate(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen == true) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL_Init" << std::endl;

		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
		if (window) {
			std::cout << "SDL_CreateWindow" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "SDL_CreateRenderer" << std::endl;
		}

		is_running = true;
	}
	else {
		is_running = false;
	}

	map = new Map();

	Map::load("C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Simple_map_16x16.txt", 16, 16);

	new_player.add_component<TransformComponent>();
	//new_player.add_component<TransformComponent>(0.0f, 0.0f, 32, 32, 2);
	//new_player.add_component<SpriteComponent>("C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Player_walking.png", 4, 150);
	new_player.add_component<SpriteComponent>("C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Charecter/Animated_knight_walking_south.png", 4, 200);
	//new_player.add_component<SpriteComponent>("C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Charecter/Knight_outline_color.png");
	new_player.add_component<KeyboardController>();
	new_player.add_component<ColliderComponent>("player");
	new_player.add_group(group_players);

	//wall
	wall.add_component<TransformComponent>(320.0f, 320.0f, 32, 32, 1);
	wall.add_component<SpriteComponent>("C:/Users/krist/source/repos/Game_project/Game_project/Tilemap/Grass_rock.png");
	wall.add_component<ColliderComponent>("wall");
	wall.add_group(group_map);
}

void Game::handle_events() {
	

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	//count++;
	//std::cout << count << std::endl;
	
	manager.refresh();
	manager.update();

	for (auto cc : colliders) {
		Collision::AABB(new_player.get_component<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.get_group(group_map));
auto& players(manager.get_group(group_players));
auto& enemies(manager.get_group(group_enemies));

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Cleaned" << std::endl;
}

void Game::add_tile(int id, int x, int y) {
	auto& tile(manager.add_entity());
	tile.add_component<TileComponent>(x, y, 32, 32, id);
	tile.add_group(group_map);
}

bool Game::running() {
	return is_running;
}

Game::~Game() {

}
