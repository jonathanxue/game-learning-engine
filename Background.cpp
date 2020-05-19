#include "Background.hpp"
#include "game.hpp"
#include <fstream>
#include "ECS/EntityComponentSystem.hpp"

Background::Background(std::string tID, int mapScale, int tileSize) : textureID(tID), mapScale(mapScale), tileSize(tileSize)
{}

void Background::LoadBackground(std::string path, int sizeX, int sizeY) {

}

void Background::AddTile(int srcX, int srcY, int xpos, int ypos) {

}
