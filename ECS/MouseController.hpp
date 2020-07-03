#pragma once

#include "Components.hpp"


class MouseController : public Component {
private:
	UIButton* button;
	UISlider* slider;
	UIDropDown* dropdown;
	TypingController* keyboard;
	TransformComponent* transform;
	bool clickable = true;
public:

	~MouseController() {}

	void init() override {
		//TODO Find a more scalable solution than this stuff
		//Maybe add logic to the individual components
		//And just have clickListener here
		button = &entity->getComponent<UIButton>();
		slider = &entity->getComponent<UISlider>();
		keyboard = &entity->getComponent<TypingController>();
		transform = &entity->getComponent<TransformComponent>();
		dropdown = &entity->getComponent<UIDropDown>();
	}

	void setStatus(bool val) {
		clickable = val;
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
	//TODO: Refactor this garbage
	void update() override {
		if (!clickable) { return; }
		if (Game::eventResult == 0) { return; }
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (coordInBounds()) {
					//Check for which kind of UI component we are clicking
					if (button != NULL) { button->buttonPressHandler(); }
					if (slider != NULL) {
						slider->updateValueOnClick(getRelativeCursorPosition().x);
						slider->setFocus(true);
					}
					if (dropdown != NULL) {
						dropdown->setPressed(true); //Press mouse
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
				if (coordInBounds()) {
					//For typing
					if (keyboard != NULL) {
						if (keyboard->checkEnabled()) {
							keyboard->enableTyping();
						}
					}
					if (dropdown != NULL) {
						//Check if we pressed on the dropdown
						if (dropdown->isPressed()) {
							//Check if the dropdown is open or closed
							//If open
							if (dropdown->checkFocus()) {
								dropdown->updateSelectedItem(Game::event.button.y); //Update item
								dropdown->setFocus(false); //Close item, shrink transform
								dropdown->setPressed(false); //Release mouse click
							}
							//If closed, we open (enlarge the transform component)
							else {
								dropdown->setFocus(true);
							}
						}
					}
				}
				if (slider != NULL) {
					slider->setFocus(false);
				}
				if (dropdown != NULL) {
					if (!coordInBounds() && !dropdown->isPressed()) {
						dropdown->setFocus(false);
					}
					dropdown->setPressed(false); //Release mouse

				}
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_MOUSEMOTION) {
			if (slider != NULL) {
				if (slider->checkFocus()) {
					slider->updateValueOnClick(getRelativeCursorPosition().x);
				}
			}
		}
	}
};