#pragma once

#include "Components.hpp"

//This shit is mainly for sound effects
class SoundEffectComponent : public Component {
private:
	Mix_Chunk* chunk;
	int repetitions = -1; //-1 default, one repetition
	int channel = -1; // -1 default, first available channel

public:
	SoundEffectComponent() = default;

	SoundEffectComponent(std::string id) {
		setAudio(id);
	}
	
	SoundEffectComponent(std::string id, int rep) :  repetitions(rep) {
		setAudio(id);
	}

	SoundEffectComponent(std::string id, int rep, int chan) : channel(chan), repetitions(rep) {
		setAudio(id);
	}

	~SoundEffectComponent() {
		//Mix_FreeChunk(chunk);
	}

	void init() override {

	}

	void setAudio(std::string id) {
		chunk = Game::assets->GetSoundEffect(id);
	}

	void play() {
		Mix_PlayChannel(channel, chunk, repetitions); // 1 makes one more loop (twice in total)
	}

	void stop() {
		Mix_HaltChannel(channel);
	}
};