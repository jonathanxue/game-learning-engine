#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "../AssetManager.hpp"
#include "../ECS/EntityComponentSystem.hpp"

class Scene;
class SceneManager;

class Scene {
private:

public:
	bool permanent = false;
	std::string tag;
	Manager* manager;
	virtual void update() {}
	virtual void draw() {}
	virtual ~Scene() {}
};

class SceneManager {
public:
	AssetManager* assets;

	int currentIndex, oldIndex;
	Scene* currentScene, *oldScene;
	std::vector<Scene*> scenes;

	SceneManager(AssetManager* ass) : assets(ass) {
		currentIndex = oldIndex = 0;
		currentScene = oldScene = nullptr;
	}

	void AddScene(Scene *sc) {
		if (scenes.empty()) {
			currentIndex = 0;
		}
		scenes.emplace_back(sc);
	}

	//chooses which scene to load/focus
	//Fix pointers here
	void SelectScene(std::string t) {
		int counter = 0;
		for (Scene* s : scenes) {
			if (s->tag == t) {
				oldScene = currentScene;
				currentScene = s;

				oldIndex = currentIndex;
				currentIndex = counter;

				break;
			}
			counter++;
		}
	}

	void CleanScene() {
		if (!oldScene->permanent) {
			scenes.erase(scenes.begin() + oldIndex);
			free(oldScene);
		}
	}

	void LoadAssets() {
		//Load new assets into assetmanager
	}

	void LoadEntities() {
		//Load new entities into manager
	}

	void CleanAssets() {
		//Remove unused assets
	}

	void CleanEntities() {
		//Remove assets that are not in the scene
		//Maybe cal lthis eright before CleanScene()
	}

	void update() {
		currentScene->update();
	}

	void draw() {
		currentScene->draw();
	}
};