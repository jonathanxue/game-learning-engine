#pragma once

#include "ComponentHelper.hpp"


class TileComponent : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}


	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
		texture = Game::assets->GetTexture(id);

		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override {
		destRect.x = static_cast<int>(position.x - Game::camera.x);
		destRect.y = static_cast<int>(position.y - Game::camera.y);
		//This tells us to not render anything outside of the camera
		drawFlag = ComponentHelper::CheckRectangleIntersection(destRect, Game::camera);
	}

	void draw() override {
		if (drawFlag) {
			TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
		}
	}

};