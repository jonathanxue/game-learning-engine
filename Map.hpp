#pragma once
#include <string>

class Manager;

class Map {
private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
	Manager* man;
public:
	Map(std::string tID, int mapScale, int tileSize);
	Map(Manager* m, std::string tID, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
};