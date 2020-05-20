#include "Background.hpp"
#include "game.hpp"
#include <fstream>
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Components.hpp"

extern Manager manager;

Background::Background(std::string tID, int mapScale, int tileSize) : textureID(tID), mapScale(mapScale), tileSize(tileSize)
{
	scaledSize = mapScale * tileSize;
}

void Background::LoadBackground(std::string path, int sizeX, int sizeY) {
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
	mapFile.close();
}

void Background::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);
	tile.addGroup(Game::groupBackgrounds);
}
