#pragma once
#include "Components.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UIButton : public Component {
public:

	UIButton(int xpos, int ypos, int width, int height, std::string buttonText) {
		position.x = xpos;
		position.y = ypos;
		position.w = width;
		position.h = height;

		src.x = src.y = 0;
		src.h = 32;
		src.w = 32;

		//Set font to default font
		btnText = UILabel::UILabel(xpos, ypos, buttonText, Game::defaultFont, Game::defaultFontColour);
		btnText.updateButtonPos(static_cast<int>(xpos + position.w / 2), static_cast<int>(ypos + position.h / 2));

		btnTexture = Game::assets->GetTexture("button_default");
	}

	~UIButton() {}


	bool coordInBounds(int xpos, int ypos) {
		if (xpos <= (position.x + position.w) && xpos >= position.x && ypos <= (position.y + position.h) && ypos >= position.y) {
			return true;
		}
		return false;
	}

	//Darken button to show button pressed
	void buttonPressHandler() {
		btnTexture = Game::assets->GetTexture("button_pressed");
		isPressed = true;
	}

	//Actually fire event, return button to normal
	void buttonReleaseHandler() {
		btnTexture = Game::assets->GetTexture("button_default");
		buttonFunction();
	}

	//Logic for button function, refactor later
	void buttonFunction() {
		printf("Button pressed!\n");
	}

	void draw() override {
		TextureManager::Draw(btnTexture, src, position, SDL_FLIP_NONE);
		btnText.draw();
	}

private:
	SDL_Rect position, src;
	UILabel btnText;
	SDL_Texture* btnTexture;
	bool isPressed = false;
};