#pragma once
#include "Components.hpp"

class PositionComponent : public Component {
private:
	int xpos, ypos;
public:
	int x() { return xpos; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void x(int x) { xpos = x; }

	PositionComponent() {
		xpos = 0;
		ypos = 0;
	}

	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}

	void update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};