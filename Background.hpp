#pragma once
#include <string>
#include "SDL.h"

class Background {
private:
	std::string textureID;
	SDL_Rect delta, dest1, dest2;
	SDL_Texture* texture;
	int texW, texH;
	int xOff, yOff;
	int scrollSpeed;
	bool scrolling = true;
public:
	Background(std::string tID, bool parallax);
	~Background();

	void init();
	void LoadBackground(std::string path);
	void ScrollBackgroundHorizontal();
	void ScrollBackgroundVertical(); //TODO
	void InvokeParallaxHorizontal();
	void InvokeParallaxVertical(); //TODO
	void Draw();
	std::string GetBackgroundID();
};
