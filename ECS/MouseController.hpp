#pragma once

#include "Components.hpp"


class MouseController : public Component {
private:
	UIButton* button;
public:

	~MouseController() {
		free(button);
	}

	void init() override {
		button = &entity->getComponent<UIButton>();
	}

	void update() override {
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (button != NULL) {
					if (button->coordInBounds(Game::event.button.x, Game::event.button.y)) {
						button->buttonPressHandler();
					}
				}
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_MOUSEBUTTONUP) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (button != NULL) {
					button->buttonReleaseHandler();
					if (button->coordInBounds(Game::event.button.x, Game::event.button.y)) {
						button->buttonFunction();
					}
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