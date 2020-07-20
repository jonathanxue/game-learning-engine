#pragma once
#include "Components.hpp"
#include <functional>
#include "../UIResources/ButtonCallbacks.hpp"
#include "ComponentHelper.hpp"

class UIButton : public Component {
private:
	TransformComponent* trans;
	SDL_Rect dest;
	SDL_Texture* btnTexture;
	bool isPressed = false;
	//This is what the button does
	std::function<void()> callBack;
	int padding = 15;

public:
	UIButton() : dest({ 0,0,0,0 }), btnTexture(nullptr) {}

	~UIButton() {}

	
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

	void init() override {
		btnTexture = Game::assets->GetTexture("button_default");
		trans = &entity->getComponent<TransformComponent>();

		//Transform component dictates all
		if (trans != NULL) {
			ComponentHelper::UpdateRectangleToTransform(dest, *trans);
		}
		drawFlag = true;
	}

	void update() override {
		if (trans != NULL) {
			ComponentHelper::UpdateRectangleToTransform(dest, *trans);
		}
	}

	void draw() override {
		if (drawFlag) {
			TextureManager::Draw(btnTexture, dest, SDL_FLIP_NONE);
		}
	}
};