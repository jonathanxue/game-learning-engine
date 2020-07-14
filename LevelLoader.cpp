#include "LevelLoader.hpp"

LevelLoader::LevelLoader() {

}


void LevelLoader::LoadFile(const char *path) {
	xml_document<> doc;
	xml_node<>* root_node;
	xml_node<>* entity_node;

	std::ifstream file(path);
	buffer = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("Level");
	entity_node = root_node->first_node("Entities");
	for (xml_node<>* levelNode = entity_node->first_node("Entity"); levelNode; levelNode = levelNode->next_sibling()) {
		printf("%s\n", levelNode->first_attribute("type")->value());
	}
}