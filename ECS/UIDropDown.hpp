#pragma once
#include "Components.hpp"

class UIDropDown : public Component {
private:
	TransformComponent* trans;
	SDL_Rect dest, textDest;
	SDL_Texture* activeTexture, *passiveTexture;

	std::vector<SDL_Texture*> textTextures;
	std::vector<std::string> contents;

	std::string value = "";
	int selectedItem = 0; //This is index of contents

	int divHeight = 30;
	int minWidth = 50;

	bool inFocus = false;
	bool pressed = false;
public:
	UIDropDown() {}
	UIDropDown(std::string input[], int size) {
		setContents(input, size);
	}
	UIDropDown(std::vector<std::string> vec) : contents(vec) {}

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


	std::string getValue() {
		return value;
	}

	//TODO: Put this in ComponentHelper.hpp
	void centerLabel() {
		textDest.x = (dest.x + (dest.w / 2)) - ((textDest.w) / 2);
		textDest.y = (dest.y + (dest.h / 2)) - ((textDest.h) / 2);
	}

	void setContents(std::string in[], int size) {
		contents.clear();
		textTextures.clear();
		for (int i = 0; i < size; i++) {
			contents.push_back(in[i]);

			//Initialize textures
			SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), in[i].c_str(), Game::defaultFontColour);
			SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, surf);
			SDL_FreeSurface(surf);
			textTextures.push_back(text);
		}
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

		if (textTextures.size() > 0) {
			textTextures.clear();
		}

		for (auto s : contents) {
			SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), s.c_str(), Game::defaultFontColour);
			SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, surf);
			SDL_FreeSurface(surf);
			textTextures.push_back(text);
		}

		//temp
		drawFlag = true;
		inFocus = false;
	}

	void updateSelectedItem(int ypos) {
		if (contents.size() < 1) {
			return;
		}

		int relY = ypos - static_cast<int>(trans->position.y);
		selectedItem = (relY - (relY % divHeight)) / divHeight; //Retrieves the index associated with the click position
		value = contents[selectedItem];
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
		if (drawFlag) { //If visible
			if (!pressed) { //If did not press mouse down on control
				if (inFocus) { //If control is open (selected already)
					//Iteratively draw rectangle for each dropdown item
					for (int i = 0; i < contents.size(); i++) {
						if (i == selectedItem) { //Highlight the already selected value
							TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
							SDL_QueryTexture(textTextures[i], nullptr, nullptr, &textDest.w, &textDest.h);
							centerLabel();
							SDL_RenderCopy(Game::renderer, textTextures[i], nullptr, &textDest); //draw already existing label
						}
						else {
							TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE); //Draw container
							SDL_QueryTexture(textTextures[i], nullptr, nullptr, &textDest.w, &textDest.h);
							centerLabel();
							SDL_RenderCopy(Game::renderer, textTextures[i], nullptr, &textDest); //Draw label
						}
						dest.y += divHeight;
						textDest.y += divHeight;
					}
					dest.y -= divHeight * contents.size(); //Reset position
					textDest.y -= divHeight * contents.size();
				}
				else { //If control is closed DEFAULT CLOSED
					TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
					SDL_QueryTexture(textTextures[selectedItem], nullptr, nullptr, &textDest.w, &textDest.h);
					centerLabel();
					SDL_RenderCopy(Game::renderer, textTextures[selectedItem], nullptr, &textDest);
				}
			}
			else { //If mouse pressed down on control
				if (!inFocus) { //If control is closed
					TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE);
					SDL_QueryTexture(textTextures[selectedItem], nullptr, nullptr, &textDest.w, &textDest.h);
					centerLabel();
					SDL_RenderCopy(Game::renderer, textTextures[selectedItem], nullptr, &textDest);
				}
				//TODO: Refactor this mess
				else { //If control is opened
					for (int i = 0; i < contents.size(); i++) {
						if (i == selectedItem) {
							TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
							SDL_QueryTexture(textTextures[selectedItem], nullptr, nullptr, &textDest.w, &textDest.h);
							centerLabel();
							SDL_RenderCopy(Game::renderer, textTextures[selectedItem], nullptr, &textDest);
						}
						else {
							TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE); //Draw container
							SDL_QueryTexture(textTextures[i], nullptr, nullptr, &textDest.w, &textDest.h);
							centerLabel();
							SDL_RenderCopy(Game::renderer, textTextures[i], nullptr, &textDest); //Draw label
							
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
