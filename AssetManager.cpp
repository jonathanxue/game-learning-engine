#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager() { free(manager); }

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id) {
	return fonts[id];
}

void AssetManager::AddMusic(std::string id, const char* path) {
	soundtracks.emplace(id, Mix_LoadMUS(path));
}

Mix_Music* AssetManager::GetMusic(std::string id) {
	return soundtracks[id];
}

void AssetManager::AddSoundEffect(std::string id, const char* path) {
	soundEffects.emplace(id, Mix_LoadWAV(path));
}

Mix_Chunk* AssetManager::GetSoundEffect(std::string id) {
	return soundEffects[id];
}
