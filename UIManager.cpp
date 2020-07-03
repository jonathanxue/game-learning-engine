#include "UIManager.hpp"

void UIManager::CreateButton() {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>();
	entity.addComponent<UIButton>();
	entity.addComponent<UILabel>();
	entity.addComponent<SoundEffectComponent>("spellhit", 0); //temp
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
}

void UIManager::CreateLabel() {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>();
	entity.addComponent<UILabel>();
	entity.addGroup(Game::groupUI);
}

void UIManager::CreateSlider() {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>();
	entity.addComponent<UILabel>();
	entity.addComponent<UISlider>();
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
}

void UIManager::CreateTextBox() {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>();
	entity.addComponent<UILabel>();
	entity.addComponent<TypingController>();
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
}

void UIManager::CreateDropdown() {
	auto& entity(manager->addEntity());
	entity.addComponent<TransformComponent>();
	entity.addComponent<UIDropDown>();
	entity.addComponent<MouseController>();
	entity.addGroup(Game::groupUI);
}

void UIManager::CreateDialogue() {

}
