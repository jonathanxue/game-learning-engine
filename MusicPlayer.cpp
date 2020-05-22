#include "MusicPlayer.hpp"
#include "AssetManager.hpp"
#include "game.hpp"

extern Game game;

MusicPlayer::MusicPlayer() {}

MusicPlayer::MusicPlayer(std::string id) {
	setSong(id);
}

MusicPlayer::MusicPlayer(std::string id, int reps) {
	setSong(id);
	repetitions = reps;
}

MusicPlayer::~MusicPlayer() {
	Mix_FreeMusic(song);
}

void MusicPlayer::setRepetitions(int reps) {
	repetitions = reps;
}

void MusicPlayer::setSong(std::string id) {
	song = game.assets->GetMusic(id);
	//For debug
	if (song == NULL) {
		std::cout << Mix_GetError() << std::endl;
	}
}

void MusicPlayer::play() {
	Mix_PlayMusic(song, repetitions);
}