#pragma once

#include "Components.hpp"

//This shit is mainly for sound effects
class AudioComponent : public Component {
private:
	Mix_Chunk* chunk;
	int repetitions = -1; //-1 default, one repetition
	int channel = -1; // -1 default, first available channel

public:
	AudioComponent() = default;

	AudioComponent(std::string id) {
		setAudio(id);
	}

	AudioComponent(std::string id, int rep, int chan) : channel(chan), repetitions(rep) {
		setAudio(id);
	}

	~AudioComponent();

	void init() override {

	}

	void setAudio(std::string id) {
		chunk = Game::assets->GetSoundEffect(id);
	}

	void play() {
		Mix_PlayChannel(channel, chunk, repetitions); // 1 makes one more loop (twice in total)
	}
};