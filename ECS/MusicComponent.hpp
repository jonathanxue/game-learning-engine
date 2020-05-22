#pragma once

#include "Components.hpp"

//Maybe use an independent class to play music
//Depends on if we can play multiple songs at once
//If cant, we do that, if not, keep this implementation
class MusicComponent : public Component {
private:
	Mix_Music* song;
	int repetitions = -1;
public:

	MusicComponent() = default;

	MusicComponent(std::string id) {
		setSong(id);
	}

	MusicComponent(std::string id, int reps) : repetitions(reps) {
		setSong(id);
	}

	~MusicComponent() {}

	void setSong(std::string id) {
		song = Game::assets->GetMusic(id);
	}

	void play() {
		Mix_PlayMusic(song, repetitions);
	}
};
