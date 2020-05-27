#pragma once
#include "Components.hpp"
#include <memory>

class UIContent : public Component {
private:
	SDL_Rect src, dest;
	TransformComponent* transform;
	SDL_Texture* texture;
	std::vector<std::unique_ptr<Entity>> entities;
	bool autoFormat = false;
public:
	UIContent() {}
	UIContent(bool format) : autoFormat(format) {

	}
	~UIContent() {}

	void addEntity(Entity* ent) {
		if (transform != NULL) {
			// Make the child entities' position relative to the parent
			ent->getComponent<TransformComponent>().position += transform->position;
		}
		std::unique_ptr<Entity> uPtr{ ent };
		entities.emplace_back(std::move(uPtr));
	}

	void init() override {
		texture = Game::assets->GetTexture("menu");
		transform = &entity->getComponent<TransformComponent>();
		//Transform component dictates all
		if (transform != NULL) {
			dest.x = static_cast<int>(transform->position.x);
			dest.y = static_cast<int>(transform->position.y);
			dest.w = static_cast<int>(transform->width);
			dest.h = static_cast<int>(transform->height);
		}
		else {
			dest.x = 0;
			dest.y = 0;
			dest.w = 0;
			dest.h = 0;
		}

		src.x = src.y = 0;
		src.h = 32;
		src.w = 32;
	}

	void update() override {
		if (transform != NULL) {
			dest.x = static_cast<int>(transform->position.x);
			dest.y = static_cast<int>(transform->position.y);
			dest.w = static_cast<int>(transform->width);
			dest.h = static_cast<int>(transform->height);
		}
		else {
			dest.x = 0;
			dest.y = 0;
			dest.w = 0;
			dest.h = 0;
		}
		for (auto& e : entities) {
			//Move child components with parent
			//Add some sort of delta or something
			e->update();
		}
	}

	void draw() override {
		TextureManager::Draw(texture, src, dest, SDL_FLIP_NONE);
		for (auto& i : entities) {
			i->draw();
		}
	}
};