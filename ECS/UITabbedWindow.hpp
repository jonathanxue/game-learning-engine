#pragma once

#include "Components.hpp"

/*
*	This behaves like a component, but is not one.
	This way I don't have to create an entire entity just for this functionality, and I won't have to include it in the main manager or any associated groups
	Tab content will only exist inside the UITabbedWindow component
*/
class UITabContent {
private:
	TransformComponent* transform; //All tabs will share the same tranform component, as they all take the same space
	SDL_Texture* texture;
	SDL_Rect dest; //Maybe move this up to the window and have all the tabs share
public:
	std::string tabName;
	//std::vector<Entity*> entities;

	UITabContent(std::string s, SDL_Texture* tex, TransformComponent* trans, int tabHeight) : tabName(s), texture(tex) {
		transform = new TransformComponent(trans->position.x, trans->position.y + tabHeight, trans->width, trans->height - tabHeight, trans->scale);
	}

	void addEntity(Entity& e) {
		//entities.emplace_back(e);
	}

	void init() {
		ComponentHelper::UpdateRectangleToTransform(dest, *transform);
	}

	void update() {
		ComponentHelper::UpdateRectangleToTransform(dest, *transform);
		/*for (auto& e: entities) {
			e->update();
		}*/
	}

	void draw() {
		TextureManager::Draw(texture, dest, SDL_FLIP_NONE);
		/*for (auto& e : entities) {
			e->draw();
		}*/
	}
};

class UITabbedWindow : public Component {
private:
	std::vector<UITabContent*> tabs;
	std::vector<SDL_Texture*> labelTextures;
	
	TransformComponent* trans;
	SDL_Texture* activeTab, * passiveTab, * containerBG;
	SDL_Rect contentRect, headerRect, labelRect;

	UITabContent* selectedTab;
	int tabCount = 1;

	int tabHeight = 32;
	int tabWidth = 0;
public:
	bool isPressed = false;

	int checkMouseInBoundsTab(int xpos, int ypos) {
		//Not even in the tab
		if (xpos < trans->position.x || xpos >(trans->position.x + trans->width) || ypos < trans->position.y || ypos >(trans->position.y + tabHeight)) {
			return -1;
		}
		//X,Y coordinate must be in bounds at this point
		int relX = xpos - trans->position.x;
		return ((relX - (relX % tabWidth)) / tabWidth);
	}

	void updateSelectedTab(int i) {
		selectedTab = tabs[i];
	}

	void createTab(std::string tabName) {
		UITabContent* t = new UITabContent(tabName, containerBG, trans, tabHeight);
		tabs.emplace_back(t);
		t->init();
	}

	void init() override {
		trans = &entity->getComponent<TransformComponent>();

		activeTab = Game::assets->GetTexture("tabheader_active");
		passiveTab = Game::assets->GetTexture("tabheader_passive");
		containerBG = Game::assets->GetTexture("tabcontent");

		createTab("test");
		createTab("test2");
		createTab("test3");

		generateHeaderTextTextures();

		tabCount = tabs.size();

		updateSelectedTab(0);
	}

	void update() override {
		selectedTab->update();
	}

	void draw() override {
		drawHeader();
		selectedTab->draw();
	}

	void generateHeaderTextTextures() {
		for (auto& e : tabs) {
			SDL_Texture* text;
			SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(Game::defaultFont), e->tabName.c_str(), Game::defaultFontColour);
			text = SDL_CreateTextureFromSurface(Game::renderer, surf);
			SDL_FreeSurface(surf);
			

			labelTextures.emplace_back(text);
		}
	}

	void drawHeader() {
		tabWidth = static_cast<int>(trans->width / tabCount);
		headerRect = { static_cast<int>(trans->position.x), static_cast<int>(trans->position.y), tabWidth, tabHeight };
		for (int i = 0; i < tabCount; i++) {
			if (tabs[i]->tabName == selectedTab->tabName) {
				TextureManager::Draw(activeTab, headerRect, SDL_FLIP_NONE);
			}
			else {
				TextureManager::Draw(passiveTab, headerRect, SDL_FLIP_NONE);
			}
			SDL_QueryTexture(labelTextures[i], nullptr, nullptr, &labelRect.w, &labelRect.h);
			ComponentHelper::CenterLabelInRect(labelRect, headerRect);
			SDL_RenderCopy(Game::renderer, labelTextures[i], nullptr, &labelRect);
			headerRect.x += tabWidth;
		}
	}

};