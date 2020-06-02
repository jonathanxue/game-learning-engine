#pragma once

#include "Components.hpp"

class TypingController : public Component {
private:
	std::string inputText;
	std::string oldText;
	bool renderText = false; //Update flag
	bool isEnabled = true; //Enable flag, might not be needed
	UILabel* label;
public:

	TypingController() {
		inputText = "";
	}
	~TypingController() {}

	bool checkEnabled() {
		return isEnabled;
	}

	//Start accepting SDL_TEXTINPUT Events
	//Save a copy of the original text
	//Start editing the original text as well
	void enableTyping() {
		SDL_StartTextInput();
		if (label != NULL) {
			oldText = label->getLabelText();
		}
		inputText = oldText;
	}

	void disableTyping() {
		SDL_StopTextInput();
	}

	void init() override {
		label = &entity->getComponent<UILabel>();
		disableTyping(); //Default is enabled
	}

	void update() override {
		//Game::event will not update if there is no new event. The old event will still trigger changes if not for this check
		if (Game::eventResult == 0) { return; }
			if (Game::event.type == SDL_KEYDOWN) {
				SDL_Keycode key = Game::event.key.keysym.sym;

				//Backspace
				if (key == SDLK_BACKSPACE && inputText.length() > 0) {
					inputText.pop_back();
					renderText = true;
				}
				//Copy
				else if (key == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
					SDL_SetClipboardText(inputText.c_str());
				}
				//Paste
				else if (key == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
					inputText += SDL_GetClipboardText();
					renderText = true;
				}
				//Confirm changes
				else if (key == SDLK_KP_ENTER || key == SDLK_RETURN) {
					renderText = true; //Render just incase
					disableTyping();
					oldText = inputText;
					//fire other events
				}
				//Cancel changes
				else if (key == SDLK_ESCAPE) {
					renderText = true;
					inputText = oldText;
					disableTyping();
				}
			}
			//General text input
			else if (Game::event.type == SDL_TEXTINPUT) {
				if (!(SDL_GetModState() & KMOD_CTRL && (Game::event.text.text[0] == 'c' || Game::event.text.text[0] == 'C'
					|| Game::event.text.text[0] == 'v' || Game::event.text.text[0] == 'V'))) {
					inputText += Game::event.text.text;
					renderText = true;
				}
			}

		//Update label if there are changes
		if (renderText) {
			if (label != NULL) {
				label->SetLabelText(inputText, Game::defaultFont); //Maybe change to allow for variable font
				//label->HighlightLabelText(inputText, Game::defaultFont);
				renderText = false;
			}
		}
	}

};
