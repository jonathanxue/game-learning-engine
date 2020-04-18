#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

#include <vector>
#include <iostream>

class ColliderComponent;

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

	static void addTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	bool isRunning = false;
	SDL_Window *window;
};

//#endif //game_hpp