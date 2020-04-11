#pragma once
#include "EntityComponentSystem.hpp"

class PositionComponent : public Component {
private:
	int xpos, ypos;
public:
	int x() { return xpos; }
	int y() { return ypos; }

	void init() override {
		xpos = 0;
		ypos = 0;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};
