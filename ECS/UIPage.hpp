#pragma once

#include "../AssetManager.hpp"
#include "../game.hpp"
#include "EntityComponentSystem.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UIPage : public Component {
public:
	UIPage();
	~UIPage();

	void draw() override {
		printf("lul");
	}
private:

};