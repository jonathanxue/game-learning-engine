#pragma once
#include "Components.hpp"

class UIDropDown : public Component {
private:
	TransformComponent* trans;
	SDL_Rect dest, textDest;
	SDL_Texture* activeTexture, *passiveTexture, *labelTexture;
	std::string value = "";
	std::vector<std::string> contents = {"a", "b", "c", "d", "e"};
	int selectedItem = 0; //This is index of contents
	int divHeight = 30;
	int minWidth = 50;
	bool inFocus = false;
	bool pressed = false;
public:
	UIDropDown() {}
	~UIDropDown() {}

	void setPressed(bool b) {
		pressed = b;
	}

	bool isPressed() {
		return pressed;
	}

	void setFocus(bool b) {
		inFocus = b;
		//Update trans height to accomodate changing size
		if (b) {
			trans->height = divHeight * contents.size();
		}
		else {
			trans->height = divHeight;
		}
	}

	bool checkFocus() {
		return inFocus;
	}

	//TODO: Put this in ComponentHelper.hpp
	void centerLabel() {
		textDest.x = (dest.x + (dest.w / 2)) - ((textDest.w) / 2);
		textDest.y = (dest.y + (dest.h / 2)) - ((textDest.h) / 2);
	}

	void init() {
		trans = &entity->getComponent<TransformComponent>();
		if (trans != NULL) {
			trans->height = divHeight; //TODO refactor this
			ComponentHelper::UpdateRectangleToTransform(dest, *trans);
			ComponentHelper::UpdateRectangleToTransform(textDest, *trans);
		}
		activeTexture = Game::assets->GetTexture("dropdown_active");
		passiveTexture = Game::assets->GetTexture("dropdown_passive");

		//Initialize selcted value and texture
		value = contents[selectedItem];
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), value.c_str(), Game::defaultFontColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &textDest.w, &textDest.h);

		//temp
		drawFlag = true;
		inFocus = false;
	}
	
	std::string getValue() {
		return value;
	}

	void updateSelectedItem(int ypos) {
		int temp = selectedItem;
		int relY = ypos - static_cast<int>(trans->position.y);
		selectedItem = (relY - (relY % divHeight)) / divHeight; //Retrieves the index associated with the click position
		value = contents[selectedItem];

		TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);

		//Update label texture to new value
		if (labelTexture != nullptr) {
			SDL_DestroyTexture(labelTexture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), value.c_str(), Game::defaultFontColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &textDest.w, &textDest.h);

	}

	void update() override {
		//TODO maybe add support for tracking movement of dropdowns?
		/*if (trans != NULL) {
			ComponentHelper::UpdateRectangleToTransform(dest, *trans);
		}*/
	}

	//Alternative
	//Draw one large empty dropdown
	//Draw individual active component on top
	void draw() override {
		if (drawFlag) {
			if (!pressed) {
				if (inFocus) {
					//Iteratively draw rectangle for each dropdown item
					for (int i = 0; i < contents.size(); i++) {
						if (i == selectedItem) { //Highlight the already selected value
							TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
							SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &textDest); //draw already existing label
						}
						else {
							//We create temporary texture for each non-selected entry
							SDL_Texture* tempTexture;
							SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), contents[i].c_str(), Game::defaultFontColour);
							tempTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
							SDL_FreeSurface(surf);
							SDL_QueryTexture(tempTexture, nullptr, nullptr, &textDest.w, &textDest.h);

							centerLabel();

							TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE); //Draw container
							SDL_RenderCopy(Game::renderer, tempTexture, nullptr, &textDest); //Draw label

							SDL_DestroyTexture(tempTexture);
						}
						dest.y += divHeight;
						textDest.y += divHeight;
					}
					dest.y -= divHeight * contents.size(); //Reset position
					textDest.y -= divHeight * contents.size();
				}
				else {
					centerLabel();
					TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
					SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &textDest);
				}
			}
			else {
				if (!inFocus) {
					TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE);
				}
				//TODO: Refactor this mess
				else {
					for (int i = 0; i < contents.size(); i++) {
						if (i == selectedItem) { //Highlight the already selected value
							TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
							SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &textDest); //draw already existing label
						}
						else {
							//We create temporary texture for each non-selected entry
							SDL_Texture* tempTexture;
							SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), contents[i].c_str(), Game::defaultFontColour);
							tempTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
							SDL_FreeSurface(surf);
							SDL_QueryTexture(tempTexture, nullptr, nullptr, &textDest.w, &textDest.h);

							centerLabel();

							TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE); //Draw container
							SDL_RenderCopy(Game::renderer, tempTexture, nullptr, &textDest); //Draw label

							SDL_DestroyTexture(tempTexture);
						}
						dest.y += divHeight;
						textDest.y += divHeight;
					}
					dest.y -= divHeight * contents.size(); //Reset position
					textDest.y -= divHeight * contents.size();
				}
			}

		}
	}
};
