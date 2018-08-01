#include "Game.h"

Game* game = nullptr;

int main(int argc, char* args[]){
	const int fps = 60;
	const int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;

	game = new Game();

	game->initiate("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, false);

	while (game->running()) {
		frame_start = SDL_GetTicks();

		game->handle_events();
		game->update();
		game->render();

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}
	}

	game->clean();

	//system("pause");
	return 0;
}