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
};