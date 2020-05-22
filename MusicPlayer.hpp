#pragma once

#include "SDL_mixer.h"
#include <string>

class MusicPlayer {
private:
	Mix_Music* song;
	int repetitions = -1;
public:
	MusicPlayer();
	MusicPlayer(std::string id);
	MusicPlayer(std::string, int repetitions);
	~MusicPlayer();

	void setRepetitions(int reps);
	void setSong(std::string id);
	void play();
};