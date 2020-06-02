#pragma once

#include "Components.hpp"


class MouseController : public Component {
private:
	UIButton* button;
	TypingController* keyboard;
	TransformComponent* transform;
public:

	~MouseController() {}

	void init() override {
		button = &entity->getComponent<UIButton>();
		keyboard = &entity->getComponent<TypingController>();
		transform = &entity->getComponent<TransformComponent>();
	}

	bool coordInBounds() {
		if (transform == NULL) {
			return false;
		}
		if (Game::event.button.x <= (transform->position.x + transform->width) && Game::event.button.x >= (transform->position.x)
			&& Game::event.button.y <= (transform->position.y + transform->height) && Game::event.button.y >= (transform->position.y)) {
			return true;
		}
		return false;
	}

	void update() override {
		if (Game::eventResult == 0) { return; }
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (coordInBounds()) {
					if (button != NULL) { button->buttonPressHandler(); }
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
					if (coordInBounds()) {
						button->buttonFunction();
					}
				}
				if (coordInBounds()) {
					if (keyboard != NULL) {
						if (keyboard->checkEnabled()) {
							keyboard->enableTyping();
							std::cout << "AAAAAAAA\n" << std::endl;
						}
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