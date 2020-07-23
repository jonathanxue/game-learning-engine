#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <streambuf>

#include <sstream>

#include "UIResources/ButtonCallbacks.hpp"

#include "XML/rapidxml.hpp"

using namespace rapidxml;

class Scene;

/*
* This class is used exclusively to load files into scenes
*/
class LevelLoader {
private:
	int levelType = 0;
	std::vector<char> buffer;
	Scene* sc;
	xml_document<> doc;
public:
	LevelLoader();
	~LevelLoader();
	void LoadScene(Scene* sc);
	void PopulateEntities();
	void PopulateLevelVars();
	void CreateEntity(std::string st);
};