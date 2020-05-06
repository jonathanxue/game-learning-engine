#pragma once

#include "../AssetManager.hpp"
#include "../game.hpp"
#include "EntityComponentSystem.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

//https://stackoverflow.com/questions/39133873/how-to-set-a-gui-button-in-the-win32-window-using-sdl-c

class UIPage : public Component {
public:
	UIPage();
	~UIPage();

	void draw() override {
		printf("lul");
	}
private:

};