#pragma once
#include <map>
#include <string>
#include "Vector2D.hpp"
#include "ECS/EntityComponentSystem.hpp"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "TextureManager.hpp"

class AssetManager {
private:
	//Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Mix_Music*> soundtracks;
	std::map<std::string, Mix_Chunk*> soundEffects;
	std::map<std::string, TTF_Font*> fonts;

public:
	//AssetManager(Manager* man);
	AssetManager();
	~AssetManager();

	//Game objects
	//void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);


	//Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//Text Management
	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

	//Audio Management
	//Music
	void AddMusic(std::string id, const char* path);
	Mix_Music* GetMusic(std::string id);
	//SFX
	void AddSoundEffect(std::string id, const char* path);
	Mix_Chunk* GetSoundEffect(std::string id);
};