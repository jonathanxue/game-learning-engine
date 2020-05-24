#pragma once
#include "Components.hpp"

class UIContent : public Component {
/*private:
	SDL_Rect src, dest;
	TransformComponent* transform;
	SDL_Texture* texture;
	std::vector<Entity*> entities;
	bool autoFormat = false;
public:
	UIContent();
	~UIContent();

	void addEntity(Entity& ent) {
		entities.emplace_back(ent);
	}

	void updateComponentPositions() {
		for (auto& e : entities) {
			e->getComponent<TransformComponent>();
		}
	}

	void update() override {
		
	}

	void draw() override {
		TextureManager::Draw(texture, src, dest, SDL_FLIP_NONE);
		for (auto& i : entities) {
			i->draw();
		}
	}*/
};