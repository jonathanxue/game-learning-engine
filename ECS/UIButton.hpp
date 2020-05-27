#pragma once
#include "Components.hpp"
#include <functional>
#include <string>
#include "../UIResources/ButtonCallbacks.hpp"

//TODO: Add instance-dependent method binding, prolly have to use std::bind()
//https://stackoverflow.com/questions/14189440/c-callback-using-class-member
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

	bool coordInBounds(int xpos, int ypos) {
		if (xpos <= (dest.x + dest.w) && xpos >= dest.x && ypos <= (dest.y + dest.h) && ypos >= dest.y) {
			return true;
		}
		return false;
	}

	void init() override {
		btnTexture = Game::assets->GetTexture("button_default");
		trans = &entity->getComponent<TransformComponent>();

		//Transform component dictates all
		if (trans != NULL) {
			dest.x = static_cast<int>(trans->position.x);
			dest.y = static_cast<int>(trans->position.y);
			dest.w = static_cast<int>(trans->width);
			dest.h = static_cast<int>(trans->height);
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
			dest.w = static_cast<int>(trans->width);
			dest.h = static_cast<int>(trans->height);
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