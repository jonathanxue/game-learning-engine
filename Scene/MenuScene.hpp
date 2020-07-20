#pragma once
#include "Scenes.hpp"
#include "../UIManager.hpp"

#include "../UIResources/ButtonCallbacks.hpp"

class MenuScene : public Scene {
private:
public:
	Background* background;

	MenuScene(std::string t, std::string path) {
		tag = t;
		sceneFilePath = path;
		init();
	}

	~MenuScene(){}

	//Figure out loading from file integration

	void init() {
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