#pragma once

#include "Components.hpp"
#include "Animation.hpp"

#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animationIndex = 0;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	std::map<const char*, Animation> animations;

	SpriteComponent() = default;

	SpriteComponent(std::string id) {
		setTexture(id);
	}

	//TODO animate more than just player
	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("idle", idle);
		animations.emplace("walk", walk);

		play("idle");
		setTexture(id);
	}

	~SpriteComponent() {
		
	}

	void setTexture(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		//TODO change this, it will clip if we change the dimensions of hitbox
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override {

		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animationIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName) {
		animationIndex = animations[animName].index;
		frames = animations[animName].frames;
		speed = animations[animName].speed;
	}

};