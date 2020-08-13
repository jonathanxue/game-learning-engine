#pragma once
#include <string.h>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component {
private:
public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int width, int height) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = height;
		collider.w = width;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		setDrawFlag(true);

		tex = TextureManager::LoadTexture("assets/hitbox.png");
		srcRect = { 0, 0, 32, 32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };

	}

	void update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;

			destRect.w = collider.w;
			destRect.h = collider.h;
		}

		//This is for non tile entities, they will not have an initialized destRect or collider rectangle. So we do it here. This makes entities more flexible as we add them
		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;

	}

	void draw() override {
		if (drawFlag) {
			TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
		}
	}

	void setDrawFlag(bool b) {
		drawFlag = b;
	}
};