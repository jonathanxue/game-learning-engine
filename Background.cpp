#include "Background.hpp"
#include "AssetManager.hpp"
#include "game.hpp"
#include "TextureManager.hpp"

extern Game game;

//Maybe refactor this into a component
Background::Background(std::string tID, bool scrolling) : textureID(tID), scrollFlag(scrolling)
{
	xOff = yOff = 0;
	//Maybe re-evaluate this, holding a 1920x1080 texture in memory is lame. Also rendering two copies of it is also lame
	texW = 1920;
	texH = 1080;
}

void Background::init() {
	LoadBackground(textureID);
	if (scrollFlag) {
		//Setup rectangles
		dest1.x = 0;
		dest1.y = 0;

		dest1.w = dest2.w = texW;
		dest1.h = dest2.h = texH;

		dest2.x = dest1.w;
		dest2.y = dest1.y;

		delta.x = 0;
		delta.y = 0;

		scrollSpeed = 5;
	}
	//static
	else {
		
	}
}

void Background::LoadBackground(std::string path) {
	textureID = path;
	texture = game.assets->GetTexture(path);
	//Reset offsets if new background
	xOff = yOff = 0;
}

//This will scroll the background without player movement. Renders two copies beside each other and scrolls through em.
//TODO:: add support for vertical scrolling as well
void Background::ScrollBackgroundHorizontal() {
	//Move background
	xOff -= scrollSpeed;

	//Reset offset for infinite looping
	if (xOff < -texW) {
		xOff = 0;
	}

	dest1.x = xOff;
	dest2.x = texW + xOff;
	dest2.y = dest1.y;
}

//This will scroll the background with camera movement
void Background::InvokeParallaxHorizontal() {
	//Move background relative to camera
	xOff += static_cast<int>((delta.x - Game::camera.x)/scrollSpeed);

	if (xOff < -texW) {
		xOff = 0;
	}

	dest1.x = xOff;
	dest2.x = texW + xOff;
	dest2.y = dest1.y;

	delta.x = Game::camera.x;
}

void Background::Draw() {
	TextureManager::Draw(texture, dest1, SDL_FLIP_NONE);
	TextureManager::Draw(texture, dest2, SDL_FLIP_NONE);
}


std::string Background::GetBackgroundID() {
	return textureID;
}
