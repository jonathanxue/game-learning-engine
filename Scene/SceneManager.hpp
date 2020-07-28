#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "../AssetManager.hpp"
#include "../ECS/EntityComponentSystem.hpp"
#include "../Map.hpp"
#include "../Background.hpp"

class Scene;
class SceneManager;

class Scene {
private:

public:
	enum groubLabels : std::size_t {
		groupBackgrounds,
		groupMap,
		groupColliders,
		groupProjectiles,
		groupUI
	};

	bool permanent = false;
	std::string tag;
	std::string sceneFilePath;
	Manager manager;

	Background* background;
	bool scrolling = false;
	Map* map;

	//Groups belonging to scene
	//TODO: Refactor later
	std::vector<Entity*> backgrounds;
	std::vector<Entity*> tiles;
	std::vector<Entity*> colliders;
	std::vector<Entity*> projectiles;
	std::vector<Entity*> uiItems;

	Scene(std::string t, std::string path) {
		tag = t;
		sceneFilePath = path;

		
		
		init();
	}

	void init() {
		background = new Background("background", true);
		background->init();
		map = new Map(&manager, "terrain", 3, 32);
	}

	void update() {
		manager.refresh();
		manager.update();

		//TODO: Refactor so we dont have to do this all the time
		backgrounds = manager.getGroup(groupBackgrounds);
		tiles = manager.getGroup(groupMap);
		colliders = manager.getGroup(groupColliders);
		projectiles = manager.getGroup(groupProjectiles);
		uiItems = manager.getGroup(groupUI);

		if (scrolling) {
			background->InvokeParallaxHorizontal();
		}

	}
	void draw() {
		background->Draw();
		for (auto& e : backgrounds) {
			e->draw();
		}
		for (auto& e : tiles) {
			e->draw();
		}
		for (auto& e : colliders) {
			e->draw();
		}
		for (auto& e : projectiles) {
			e->draw();
		}
		for (auto& e : uiItems) {
			e->draw();
		}
		//Might need to include player group i dunno
		//manager.draw();
	}
	~Scene() {}
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