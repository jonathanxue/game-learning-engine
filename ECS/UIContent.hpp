#pragma once
#include "Components.hpp"

class UIContent : public Component {
private:
	SDL_Rect src, dest;
	SDL_Texture* texture;
public:
	UIContent();
	~UIContent();

	void draw() override {
		TextureManager::Draw(texture, src, dest, SDL_FLIP_NONE);
	}
};