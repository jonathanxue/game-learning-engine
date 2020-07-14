#pragma once

#include <map>
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Components.hpp"

class UIManager {
private:
	Manager* manager;
	int lastEntityID = -1;
public:
	UIManager(Manager* man);
	~UIManager();

	int getLastEntityID() {
		return lastEntityID;
	}

	void CreateButton(int x, int y, int w, int h, std::string buttonText, std::function<void()> callback);
	void CreateLabel(int x, int y, std::string text);
	void CreateSlider(int x, int y, int w, int h, std::string text);
	void CreateTextBox(int x, int y, int w, int h, std::string text);
	void CreateDialogue();
	void CreateDropdown(int x, int y, int w, int h, std::string inputs[], int size);
	void DestroyAll();
};