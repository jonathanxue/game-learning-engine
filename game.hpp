#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include <iostream>

class Game {
public:
	Game();
	~Game();

	int cnt = 0;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
private:
	bool isRunning = false;
	SDL_Window *window;
};

//#endif //game_hpp