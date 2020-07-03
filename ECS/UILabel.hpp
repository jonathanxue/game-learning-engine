#pragma once

#include "EntityComponentSystem.hpp"

#include <string>



class UILabel : public Component {
private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Color textBackground; //for highlighted text
	SDL_Texture* labelTexture;
	TransformComponent* trans;
	//Do text allignment
	int allign = -1; //-1 = top left, 0 = centered
	int minWidth = 50; //This makes the label clickable even if empty
	bool detached = false; //This will bind/unbind the label to the transform component

public:
	UILabel() {
		position.x = position.y = position.w = position.h = 0;
		textColour = {255,255,255,255};
		textBackground = { 0,0,0,0, };
		trans = nullptr;
		labelTexture = nullptr;
	}

	UILabel(std::string text, std::string font, SDL_Color& colour, int ali) : labelText(text), labelFont(font), textColour(colour), allign(ali)
	{
		//Set to null first
		labelTexture = nullptr;
		textBackground = { 0,0,0,0 };
		SetLabelText(labelText, labelFont);
	}

	~UILabel() {}

	std::string getLabelText() {
		return labelText;
	}

	//Create texture for normal text
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

	//Create texture for highlighted text
	void HighlightLabelText(const std::string& text, const std::string& font) {
		this->labelText = text;
		this->labelFont = font;

		if (this->labelTexture != nullptr) {
			SDL_DestroyTexture(this->labelTexture);
		}

		SDL_Surface* surf = TTF_RenderText_Shaded(Game::assets->GetFont(labelFont), labelText.c_str(), textBackground,textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void updateLabelText(const std::string& text) {
		this->labelText = text;

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

	void init() override {
		trans = &entity->getComponent<TransformComponent>();
		drawFlag = true;
	}

	//Place label in middle of transform
	void update() override {
		if (trans != NULL) {
			if (detached) {
				//TODO
			}
			else {
				//Left allignment
				if (allign == -1) {
					position.x = static_cast<int>(trans->position.x);
					position.y = static_cast<int>(trans->position.y);
				}
				//Center allignment
				else if (allign == 0) {
					position.x = static_cast<int>((trans->position.x + (trans->width / 2)) - (position.w / 2));
					position.y = static_cast<int>((trans->position.y + (trans->height / 2)) - (position.h / 2));
				}
				//Update dimensions according to text length
				if (trans->width < position.w) {
					trans->width = position.w;
				}
				/*if (trans->height < position.h) {
					trans->height = position.h;
				}*/
				if (trans->width < minWidth) {
					trans->width = minWidth;
				}
			}
		}
		
	}

	void draw() override {
		if (drawFlag) {
			SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
		}
	}
};
