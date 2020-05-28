#pragma once

#include "Components.hpp"

class TypingController : public Component {
private:
	std::string inputText;
	std::string oldText;
	bool renderText = false;
	UILabel* label;
public:

	TypingController() {
		inputText = "";
	}
	~TypingController() {}

	void enableTyping() {
		SDL_StartTextInput();
		oldText = inputText;
	}

	void disableTyping() {
		SDL_StopTextInput();
	}

	void init() override {
		label = &entity->getComponent<UILabel>();
	}

	//https://wiki.libsdl.org/Tutorials/TextInput
	//http://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php
	void update() override {
		//Need this loop to capture all key inputs
		while (SDL_PollEvent(&Game::event) != 0) {
			if (Game::event.type == SDL_KEYDOWN) {
				SDL_Keycode key = Game::event.key.keysym.sym;
				if (key == SDLK_BACKSPACE && inputText.length() > 0) {
					inputText.pop_back();
					renderText = true;
				}
				else if (key == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
					SDL_SetClipboardText(inputText.c_str());
				}
				else if (key == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
					inputText = SDL_GetClipboardText();
					renderText = true;
				}
				else if (key == SDLK_KP_ENTER) {
					renderText = true; //Render just incase
					disableTyping();
					//fire other events
				}
				else if (key == SDLK_ESCAPE) {
					inputText = oldText;
					disableTyping();
				}
			}
			else if (Game::event.type == SDL_TEXTINPUT) {
				if (!(SDL_GetModState() & KMOD_CTRL && (Game::event.text.text[0] == 'c' || Game::event.text.text[0] == 'C'
					|| Game::event.text.text[0] == 'v' || Game::event.text.text[0] == 'V'))) {
					inputText += Game::event.text.text;
					renderText = true;
				}
			}
		}
		if (renderText) {
			if (label != NULL) {
				label->SetLabelText(inputText, Game::defaultFont); //Maybe change to allow for variable font
				renderText = false;
			}
		}
	}

};
