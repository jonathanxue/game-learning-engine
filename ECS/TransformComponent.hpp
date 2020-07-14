#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 6;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int sc) {
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	/*
	* Args float x, float y
	*/
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	/*
	* Comprehensive constructor
	* Args float x, float y, int w, int h, int sc
	*/
	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	~TransformComponent() {}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += (velocity.x * speed);
		position.y += (velocity.y * speed);
	}

	void updateProperties(float dx, float dy, int dw, int dh) {
		position.x += dx;
		position.y += dy;
		width += dw;
		height += dh;
	}
};