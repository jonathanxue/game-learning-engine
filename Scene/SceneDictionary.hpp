#pragma once

#include <map>
#include <string>
#include <functional>

#include "SceneManager.hpp"
#include "../UIResources/MainMenuCallBacks.hpp"
#include "../UIResources/ButtonCallbacks.hpp"

class SceneDictionary {
private:
public:
	std::map<std::string, Scene::groubLabels> Groups;
	std::map<std::string, std::function<void()>> Callbacks;
	std::map<std::string, int> AssetTracker;
	std::map<std::string, std::string> AssetNames;

	SceneDictionary();
};