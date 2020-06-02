#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include <vector>
#include <iostream>
#include <string>

class AssetManager;
class ColliderComponent;
class MusicPlayer;

class Game {
private:
	SDL_Window* window;

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

	enum groubLabels : std::size_t {
		groupBackgrounds,
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupUI
	};

	enum class gameState {
		game_running,
		game_menu,
		debug
	};

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static int eventResult;
	static bool isRunning;

	static SDL_Rect camera;
	static AssetManager* assets;
	static gameState state;

	static std::string defaultFont;
	static SDL_Color defaultFontColour;
	static SDL_Color defaultFontBackgroundColour;

};