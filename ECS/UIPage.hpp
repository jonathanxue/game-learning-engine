#pragma once
#include "EntityComponentSystem.hpp"

#include <string>

class UIPage : public Component {
public:
	UIPage();
	~UIPage();

	void draw() override {
		printf("lul");
	}
private:

};