#pragma once
#include <string>

class Map {
public:
	Map(const char* mapPath, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
private:
	const char* mapPath;
	int mapScale;
	int tileSize;
	int scaledSize;
};