#pragma once

#include "Components.hpp"

//Not in use right now
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
