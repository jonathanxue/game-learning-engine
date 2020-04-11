#pragma once

#include "game.hpp"

class GameObject {
public:
	GameObject(const char* textureSheet, int xpos, int ypos);
	~GameObject();

	void Update();
	void Render();
private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};