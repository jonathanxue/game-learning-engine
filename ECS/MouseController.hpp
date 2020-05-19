#pragma once

#include "../game.hpp"
#include "Components.hpp"


class MouseController : public Component {
public:

	UIButton* button;
	TransformComponent* trans;

	void init() override {
		button = &entity->getComponent<UIButton>();
		trans = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (button->coordInBounds(Game::event.button.x, Game::event.button.y)) {
					button->buttonPressHandler();
				}
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_MOUSEBUTTONUP) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				button->buttonReleaseHandler();
				if (button->coordInBounds(Game::event.button.x, Game::event.button.y)) {
					button->buttonFunction();
				}
				break;
			default:
				break;
			}
		}
		/*if (Game::event.type == SDL_MOUSEMOTION) {
			if (!button->coordInBounds(Game::event.button.x, Game::event.button.y)) {
				button->buttonReleaseHandler();
			}
		}*/
	}
};