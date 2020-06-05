#pragma once
#include "Components.hpp"
#include <memory>
#include "ComponentHelper.hpp"

class UIContent : public Component {
private:
	SDL_Rect src, dest;
	TransformComponent* transform;
	SDL_Texture* texture;
	std::vector<std::unique_ptr<Entity>> entities;
	Vector2D deltaPos = {0.0f,0.0f};
	int deltaH = 0, deltaW = 0;
	bool autoFormat = false;

public:
	UIContent() {}
	UIContent(bool format) : autoFormat(format) {

	}
	~UIContent() {
		
		for (auto& ent : entities) {
			ent.release();
		}
	}

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
			ComponentHelper::UpdateRectangleToTransform(dest, *transform);
		}

		src.x = src.y = 0;
		src.h = 32;
		src.w = 32;
		drawFlag = true;
	}

	void update() override {
		if (transform != NULL) {
			//Keep delta to update child components
			deltaPos.x = static_cast<int>(transform->position.x) - dest.x;
			deltaPos.y = static_cast<int>(transform->position.y) - dest.y;
			deltaW = transform->width - dest.w;
			deltaH = transform->height - dest.h;

			ComponentHelper::UpdateRectangleToTransform(dest, *transform);
		}

		for (auto& e : entities) {
			//Move child components with parent
			e->getComponent<TransformComponent>().updateProperties(deltaPos.x, deltaPos.y, deltaW, deltaH);
			e->update(); //This is redundant but reduces latency between updates of diff entities, TODO: Refactor so this isn't useful
		}
	}

	void draw() override {
		if (drawFlag) {
			TextureManager::Draw(texture, src, dest, SDL_FLIP_NONE);
			for (auto& i : entities) {
				i->draw();
			}
		}
	}
};