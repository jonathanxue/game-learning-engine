#pragma once
#include "Scenes.hpp"
#include "../UIManager.hpp"

#include "../UIResources/ButtonCallbacks.hpp"

class MenuScene : public Scene {
private:
public:
	Manager manager;
	UIManager* uimanager;
	Background* background;

	MenuScene(std::string t) {
		tag = t;
		init();
	}

	~MenuScene(){}

	//Figure out loading from file integration

	void init() {
		uimanager = new UIManager(&manager);
		uimanager->CreateButton(10, 50, 100, 50, "Scene Test", ButtonCallbacks::test1);
		background = new Background("background", true);
		background->init();
	}

	void update() override {
		manager.refresh();
		manager.update();
		background->InvokeParallaxHorizontal();
	}

	void draw() override {
		background->Draw();
		manager.draw();
	}
};