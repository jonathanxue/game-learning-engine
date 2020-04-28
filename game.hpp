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

	static SDL_Renderer* renderer;
	static SDL_Event event;
	//static std::vector<ColliderComponent*> colliders;
	static bool isRunning;

	static SDL_Rect camera;

	enum groubLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders
	};

private:
	
	SDL_Window *window;
};

//#endif //game_hpp