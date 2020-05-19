#pragma once
#include <string>



class Background {
public:
	Background(std::string tID, int mapScale, int tileSize);
	~Background();

	void LoadBackground(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};
