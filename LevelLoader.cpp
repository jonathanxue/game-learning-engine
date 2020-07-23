#include "LevelLoader.hpp"
#include "UIManager.hpp"
#include "Scene/SceneManager.hpp"

LevelLoader::LevelLoader() {

}


void LevelLoader::LoadScene(Scene* sce) {

	std::ifstream file(sce->sceneFilePath);
	buffer = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	sc = sce;
	//Keep this just in case
	levelType = atoi(doc.first_node("Level")->first_attribute("type")->value());
}

void LevelLoader::PopulateEntities() {
	UIManager* uman = new UIManager(&sc->manager);

	xml_node<>* root_node;
	xml_node<>* entity_node;

	root_node = doc.first_node("Level");
	entity_node = root_node->first_node("Entities");
	for (xml_node<>* levelNode = entity_node->first_node("Entity"); levelNode; levelNode = levelNode->next_sibling()) {
		auto& entity(sc->manager.addEntity());
		xml_node<>* componentsNode = levelNode->first_node("Components");
		for (xml_node<>* comNode = componentsNode->first_node("Component"); comNode; comNode = comNode->next_sibling()) {
			std::string type = comNode->first_attribute("type")->value();
			if (type == "transform") {
				entity.addComponent<TransformComponent>(atoi(comNode->first_attribute("x")->value()), atoi(comNode->first_attribute("y")->value()),
					atoi(comNode->first_attribute("w")->value()), atoi(comNode->first_attribute("h")->value()), 1);
			}
			else if (type == "button") {
				entity.addComponent<UIButton>();
				entity.getComponent<UIButton>().setCallBack(ButtonCallbacks::test1); //TODO, change
			}
			else if (type == "label") {
				entity.addComponent<UILabel>(comNode->first_attribute("value")->value(), Game::defaultFont, Game::defaultFontColour, 0);
			}
			else if (type == "soundeffect") {
				entity.addComponent<SoundEffectComponent>(comNode->first_attribute("sound")->value(), atoi(comNode->first_attribute("repetitions")->value()));
			}
			else if (type == "mousecontroller") {
				entity.addComponent<MouseController>();
			}
			else if (type == "dropdown") {
				int counter = 0;
				std::string values = comNode->value();
				std::vector<std::string> inputs;
				std::stringstream ss(values);
				while (ss.good()) {
					std::string substr;
					std::getline(ss, substr, ',');
					inputs.push_back(substr);
				}
				entity.addComponent<UIDropDown>(inputs);
			}
			else if (type == "slider") {
				entity.addComponent<UISlider>();
			}
		}
		entity.addGroup(Game::groupUI);
	}
	delete(uman);
}

void LevelLoader::PopulateLevelVars() {

	xml_node<>* root_node;

	root_node = doc.first_node("Level");

	if (levelType == 1) {
		sc->map->LoadMap(root_node->first_node("MapFile")->value(), 16, 10);
	}


}

void LevelLoader::CreateEntity(std::string st) {

}