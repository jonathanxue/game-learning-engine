#pragma once
#include "SDL.h"

class Collision {
public:
	//Accessed ALligned Bouding Box - Box collision
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};
