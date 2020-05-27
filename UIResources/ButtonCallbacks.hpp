#pragma once
#include <stdio.h>
#include "game.hpp"
#include <memory>
#include "../ECS/Components.hpp"

class ButtonCallbacks {
private:
	Entity* ent;
	int fuk = -1;
public:
	ButtonCallbacks() {}
	ButtonCallbacks(int i) { fuk = 1; }
	~ButtonCallbacks() {}

	//Memory properly allocated here
	void addEntity(Entity* entt) {
		ent = entt;
	}

	static void test1() {
		printf("Test 1 fired\n");
	}

	//Memory deallocated somewhere here
	void test2() {
		TransformComponent* trans = &ent->getComponent<TransformComponent>();
		trans->position.x += 150;
		printf("Test 2 fired\n");
	}
};