#pragma once
#include "TransformComponent.hpp"

class ComponentHelper {
public:
	//Updates rectangle to the dimensions of entities' TransformComponent
	static void UpdateRectangleToTransform(SDL_Rect& rect, const TransformComponent& trans) {
		rect.x = static_cast<int>(trans.position.x);
		rect.y = static_cast<int>(trans.position.y);
		rect.w = trans.width;
		rect.h = trans.height;
	}

	//Checks whether the calling two rectangles are intersecting
	//Use mainly for camera culling
	//This is kinda the same as collision
	static bool CheckRectangleIntersection(SDL_Rect& rect1, SDL_Rect& rect2) {
		if ((
			rect1.x + rect1.w >= rect2.x &&
			rect1.x <= rect2.x + rect2.w &&
			rect1.y + rect2.h >= rect2.y &&
			rect1.y <= rect2.y + rect2.h)) {
			return true;
		}
		else {
			return false;
		}
	}
};