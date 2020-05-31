#pragma once

#include "Components.hpp"

class KeyboardController : public Component {
public:
	TransformComponent* transform = nullptr;
	SpriteComponent* sprite = nullptr;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::eventResult == 0) { return; }
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_p:
				if (Game::state == Game::gameState::game_menu) { Game::state = Game::gameState::game_running; }
				else if (Game::state == Game::gameState::game_running) { Game::state = Game::gameState::game_menu; }
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}

};