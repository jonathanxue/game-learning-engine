#pragma once

#include "Components.hpp"

class ProjectileComponent : public Component {
private:
	TransformComponent* transform;
	//SpriteComponent* sprite;

	int range = 0;
	int speed = 0;
	int distance = 0;

	std::string startSound = "";
	std::string mainSound = "spellmoving";
	std::string endSound = "spellhit";

	Vector2D velocity;

public:
	ProjectileComponent(int range, int speed, Vector2D vel) : speed(speed), range(range), velocity(vel)
	{}

	~ProjectileComponent() {}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override {

		distance += speed;

		if (distance > range) {
			entity->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w || transform->position.x < Game::camera.x 
			|| transform->position.y > Game::camera.y + Game::camera.h || transform->position.y < Game::camera.y)	{
			entity->destroy();
		}
	}
};
