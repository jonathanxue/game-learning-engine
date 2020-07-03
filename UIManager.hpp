#pragma once

#include <map>
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Components.hpp"
#include "TextureManager.hpp"

class UIManager {
private:
	Manager* manager;
public:
	void CreateButton();
	void CreateLabel();
	void CreateSlider();
	void CreateTextBox();
	void CreateDialogue();
	void CreateDropdown();
	void DestroyAll();
};