#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class ColliderComponent;

class Game {
private:
	bool is_running;
	SDL_Window* window;
	//int count;
public:
	Game();
	void initiate(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	void handle_events();
	void update();
	void render();
	void clean();

	static void add_tile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event  event;
	bool running();

	static std::vector<ColliderComponent*> colliders;

	~Game();
};