#pragma once
#include "Components.hpp"
#include <functional>
#include <string>

//TODO: Add instance-dependent method binding, prolly have to use std::bind()
//https://stackoverflow.com/questions/14189440/c-callback-using-class-member
class UIButton : public Component {
private:
	SDL_Rect dest, src;
	UILabel btnText;
	SDL_Texture* btnTexture;
	bool isPressed = false;
	//This is what the button does
	std::function<void()> callBack;

public:
	UIButton(int xpos, int ypos, int width, int height, std::string buttonText) {
		dest.x = xpos;
		dest.y = ypos;
		dest.w = width;
		dest.h = height;

		src.x = src.y = 0;
		src.h = 32;
		src.w = 32;

		//Set font to default font
		btnText = UILabel::UILabel(xpos, ypos, buttonText, Game::defaultFont, Game::defaultFontColour);
		btnText.updateLabelPos(static_cast<int>(xpos + dest.w / 2), static_cast<int>(ypos + dest.h / 2));
		btnTexture = Game::assets->GetTexture("button_default");
	}

	~UIButton() {}

	bool coordInBounds(int xpos, int ypos) {
		if (xpos <= (dest.x + dest.w) && xpos >= dest.x && ypos <= (dest.y + dest.h) && ypos >= dest.y) {
			return true;
		}
		return false;
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

	void draw() override {
		TextureManager::Draw(btnTexture, src, dest, SDL_FLIP_NONE);
		btnText.draw();
	}
};