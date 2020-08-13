#include "Map.hpp"
#include "game.hpp"
#include <fstream>
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Components.hpp"
#include "Scene/SceneManager.hpp"

//extern Manager manager;

Map::Map(std::string tID, int mapScale, int tileSize) : textureID(tID), mapScale(mapScale), tileSize(tileSize)
{
	scaledSize = mapScale * tileSize;
}

Map::Map(Manager* m, std::string tID, int mapScale, int tileSize) : man(m), textureID(tID), mapScale(mapScale), tileSize(tileSize) {
	scaledSize = mapScale * tileSize;
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale));
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	//Colliders
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(man->addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				//I'm not totally sure why this works
				tcol.addGroup(Scene::groupColliders);
			}
			//else {
				mapFile.ignore();
			//}

		}
	}

	mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(man->addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);
	tile.addGroup(Scene::groupMap);
}

