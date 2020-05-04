#include "game.hpp"


Game* game = nullptr;

int main(int argc, char *argv[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	game = new Game();
	game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	Uint32 frameStart;
	int frameTime;

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		if (Game::state == Game::gameState::game_menu) {

		}
		else if (Game::state == Game::gameState::game_running){

			game->render();
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}