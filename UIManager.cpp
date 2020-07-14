#include "UIManager.hpp"

UIManager::UIManager(Manager* man) : manager(man) {}

UIManager::~UIManager(){}

void UIManager::CreateButton(int x, int y, int w, int h, std::string buttonText,std::function<void()> callback) {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>(x, y, w, h, 1);
	entity.addComponent<UIButton>();
	entity.addComponent<UILabel>(buttonText, Game::defaultFont, Game::defaultFontColour, 0);
	entity.getComponent<UIButton>().setCallBack(callback);
	entity.addComponent<SoundEffectComponent>("spellhit", 0); //temp
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
	lastEntityID = entity.getID();
}

void UIManager::CreateLabel(int x, int y, std::string text) {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>(x, y);
	entity.addComponent<UILabel>(text, Game::defaultFont, Game::defaultFontBackgroundColour, -1);
	entity.addGroup(Game::groupUI);
	lastEntityID = entity.getID();
}

void UIManager::CreateSlider(int x, int y, int w, int h, std::string text) {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>(x, y, w, h, 1);
	entity.addComponent<UILabel>(text, Game::defaultFont, Game::defaultFontColour, 0);
	entity.addComponent<UISlider>();
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
	lastEntityID = entity.getID();
}

void UIManager::CreateTextBox(int x, int y, int w, int h, std::string text) {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>(x, y, w, h, 1);
	entity.addComponent<UILabel>(text, Game::defaultFont, Game::defaultFontColour, -1);
	entity.addComponent<TypingController>();
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
	lastEntityID = entity.getID();
}

void UIManager::CreateDropdown(int x, int y, int w, int h, std::string inputs[], int size) {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>(x, y, w, h, 1);
	entity.addComponent<UIDropDown>(inputs, size);
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
	lastEntityID = entity.getID();
}

void UIManager::CreateDialogue() {

}
