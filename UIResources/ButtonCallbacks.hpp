#pragma once
#include <stdio.h>
#include <memory>
#include "../ECS/Components.hpp"

class ButtonCallbacks {
private:
	Entity* ent;
public:
	ButtonCallbacks() {}
	~ButtonCallbacks() {}

	void addEntity(Entity* entt) {
		ent = entt;
	}

	static void test1() {
		printf("Test 1 fired\n");
	}

	void test2() {
		TransformComponent* trans = &ent->getComponent<TransformComponent>();
		trans->position.x += 150;
		printf("Test 2 fired\n");
	}
};