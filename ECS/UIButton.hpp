#pragma once
#include "Components.hpp"
#include <functional>
#include <string>
#include "../UIResources/ButtonCallbacks.hpp"

class UIButton : public Component {
private:
	TransformComponent* trans;
	SDL_Rect dest, src;
	SDL_Texture* btnTexture;
	bool isPressed = false;
	//This is what the button does
	std::function<void()> callBack;

public:
	UIButton() {}

	~UIButton() {}

	void init() override {
		btnTexture = Game::assets->GetTexture("button_default");
		trans = &entity->getComponent<TransformComponent>();

		//Transform component dictates all
		if (trans != NULL) {
			dest.x = static_cast<int>(trans->position.x);
			dest.y = static_cast<int>(trans->position.y);
			dest.w = trans->width;
			dest.h = trans->height;
		}
		else {
			dest.x = 0;
			dest.y = 0;
			dest.w = 0;
			dest.h = 0;
		}

		src.x = src.y = 0;
		src.h = 32;
		src.w = 32;
	}

	void update() override {
		if (trans != NULL) {
			dest.x = static_cast<int>(trans->position.x);
			dest.y = static_cast<int>(trans->position.y);
			dest.w = trans->width;
			dest.h = trans->height;
		}
	}

	void draw() override {
		TextureManager::Draw(btnTexture, src, dest, SDL_FLIP_NONE);
	}

	//This kinda has to be called
	void setCallBack(std::function<void()> callback) {
		callBack = callback;
	}

	//Darken button to show button pressed
	void buttonPressHandler() {
		//Prevent multiple firing events
		if (!isPressed) { isPressed = true; }
		btnTexture = Game::assets->GetTexture("button_pressed");
	}

	//Return button to normal
	void buttonReleaseHandler() {
		btnTexture = Game::assets->GetTexture("button_default");
	}

	//Logic for button function, refactor later
	void buttonFunction() {
		if (isPressed) {
			entity->getComponent<SoundEffectComponent>().play();
			isPressed = false;
			if (callBack != NULL) {
				callBack();
			}
		}
	}
};