#pragma once

#include "EntityComponentSystem.hpp"

#include <string>

class UILabel : public Component {
private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;

public:
	UILabel() {
		position.x = position.y = position.w = position.h = 0;
		textColour = {0,0,0,0};
		labelTexture = nullptr;
	}

	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) : labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		//Set to null first
		labelTexture = nullptr;
		SetLabelText(labelText, labelFont);
	}

	~UILabel() {
		//SDL_DestroyTexture(labelTexture);
	}

	std::string getLabelText() {
		return labelText;
	}

	//Everytime we update the texture, we make a new texture
	//This might be really expensive, so maybe optimize later
	void SetLabelText(const std::string& text, const std::string& font) {
		this->labelText = text;
		this->labelFont = font;

		if (this->labelTexture != nullptr) {
			SDL_DestroyTexture(this->labelTexture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), labelText.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void SetFontColor(SDL_Color newColour) {
		this->textColour = newColour;
	}

	//Place label in middle of button
	void updateLabelPos(int xpos, int ypos) {
		position.x = xpos - static_cast<int>(position.w / 2);
		position.y = ypos - static_cast<int>(position.h / 2);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}
};
