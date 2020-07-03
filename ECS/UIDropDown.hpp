#pragma once
#include "Components.hpp"

class UIDropDown : public Component {
private:
	TransformComponent* trans;
	SDL_Rect dest;
	SDL_Texture* activeTexture, *passiveTexture;
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

	void init() {
		trans = &entity->getComponent<TransformComponent>();
		if (trans != NULL) {
			trans->height = divHeight; //TODO refactor this
			ComponentHelper::UpdateRectangleToTransform(dest, *trans);
		}
		activeTexture = Game::assets->GetTexture("dropdown_active");
		passiveTexture = Game::assets->GetTexture("dropdown_passive");
		value = contents[selectedItem];
		drawFlag = true;
		inFocus = false;
	}

	void updateSelectedItem(int ypos) {
		int temp = selectedItem;
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

	void draw() override {
		//This won't draw the original dropdown, but will only show the contents
		//Maybe want to show the original dropdown too
		if (drawFlag) {
			if (!pressed) {
				if (inFocus) {
					//Iteratively draw rectangle for each dropdown item
					for (int i = 0; i < contents.size(); i++) {
						if (i == selectedItem) { //Highlight the already selected value
							TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
						}
						else {
							TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE);
						}
						dest.y += divHeight;
					}
					dest.y -= divHeight * contents.size(); //Reset position
				}
				else {
					TextureManager::Draw(activeTexture, dest, SDL_FLIP_NONE);
				}
			}
			else {
				TextureManager::Draw(passiveTexture, dest, SDL_FLIP_NONE);
			}

		}
	}
};
