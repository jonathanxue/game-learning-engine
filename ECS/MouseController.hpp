#pragma once

#include "Components.hpp"


class MouseController : public Component {
private:
	UIButton* button;
	UISlider* slider;
	TypingController* keyboard;
	TransformComponent* transform;
public:

	~MouseController() {}

	void init() override {
		//TODO Find a more scalable solution than this stuff
		button = &entity->getComponent<UIButton>();
		slider = &entity->getComponent<UISlider>();
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

	Vector2D getRelativeCursorPosition() {
		Vector2D ret;
		ret.x = Game::event.button.x - transform->position.x;
		ret.y = Game::event.button.y - transform->position.y;
		return ret;
	}

	//TODO: Maybe add enum for operation modes depending on type of entity this is attached to
	void update() override {
		if (Game::eventResult == 0) { return; }
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (coordInBounds()) {
					if (button != NULL) { button->buttonPressHandler(); }
					if (slider != NULL) {
						slider->updateValueOnClick(getRelativeCursorPosition().x);
						slider->setFocus(true);
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
				//For Buttons
				if (button != NULL) {
					button->buttonReleaseHandler();
					if (coordInBounds()) {
						button->buttonFunction();
					}
				}
				//For typing
				if (coordInBounds()) {
					if (keyboard != NULL) {
						if (keyboard->checkEnabled()) {
							keyboard->enableTyping();
						}
					}
				}
				if (slider != NULL) {
					slider->setFocus(false);
				}
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_MOUSEMOTION) {
			if (slider != NULL) {
				if (slider->checkFocus()) {
					//Maybe want to lose focus when leaving bounds
					//if (coordInBounds()) {
						slider->updateValueOnClick(getRelativeCursorPosition().x);
					//}
					//else {
					//	slider->setFocus(false);
					//}
				}
			}
		}
	}
};