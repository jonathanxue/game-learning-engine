#pragma once

#include "EntityComponentSystem.hpp"
#include "../AssetManager.hpp"
#include "../game.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) : labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel(){}

	void SetLabelText(const std::string& text, const std::string& font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}
	void draw() override {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
		SDL_DestroyTexture(this->labelTexture);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
