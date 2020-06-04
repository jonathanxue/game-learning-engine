#pragma once

#include "Components.hpp"
#include "ComponentHelper.hpp"

class UISlider : public Component {
private:
	SDL_Texture* emptyTexture;
	SDL_Texture* fillTexture;
	SDL_Rect src, destFill, destEmpty;
	TransformComponent* transform; //
	bool inFocus;
	float percentValue;
public:
	UISlider() {}
	~UISlider() {}

	float getValue() {
		return percentValue;
	}

	void setValue(float f) {
		percentValue = f;
	}

	void setFocus(bool b) {
		inFocus = b;
	}

	bool checkFocus() {
		return inFocus;
	}

	void updateValueOnClick(float mousexpos) {
		if (mousexpos <= 0) { 
			percentValue = 0.0f;
		}
		else if (mousexpos > transform->width) {
			percentValue = 100.0f;
		}
		else {
			//Move to cursor position
			percentValue = (mousexpos / transform->width) * 100;
		}
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		emptyTexture = Game::assets->GetTexture("slider_empty");
		fillTexture = Game::assets->GetTexture("slider_full");
		percentValue = 50.0f;
		inFocus = false;

		src.x = 0;
		src.y = 0;
		src.w = src.h = 32;

		ComponentHelper::UpdateRectangleToTransform(destFill, *transform);
		ComponentHelper::UpdateRectangleToTransform(destEmpty, *transform);
	}

	void update() override {
		if (transform == NULL) { return; }
		
		//Maybe add movement to sliders

		//Update fill rect
		destFill.w = static_cast<int>((percentValue * destEmpty.w) / 100); //Fills the specified 
	}

	void draw() override {
		TextureManager::Draw(emptyTexture, src, destEmpty, SDL_FLIP_NONE);
		TextureManager::Draw(fillTexture, src, destFill, SDL_FLIP_NONE);
	}
};