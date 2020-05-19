#include "game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include <sstream>

//Level controllers
Map* map;
Manager manager;

//engine components
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,800,640 };

//Asset manager
AssetManager* Game::assets = new AssetManager(&manager);

//Default values
std::string Game::defaultFont = "Fixedsys";
SDL_Color Game::defaultFontColour = { 255,255,255,255 }; //White

//Gamestate stuff
Game::gameState Game::state = Game::gameState::game_running;
bool Game::isRunning = false;

//Level entities
auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& button(manager.addEntity());
auto& button2(manager.addEntity());

Game::Game() {
	Game::window = nullptr;
}

Game::~Game() {
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	
	int flags = 0;
	
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		isRunning = true;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//assets->AddTexture("background", "assets/openSeas_texture.png");
	assets->AddTexture("terrain", "assets/grassmap_textures.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/testprojectile.png");

	assets->AddTexture("collider", "assets/hitbox.png");

	//UI textures
	assets->AddFont("Fixedsys", "assets/vgafix.fon", 16);
	assets->AddTexture("button_default", "assets/button_default.png");
	assets->AddTexture("button_pressed", "assets/button_pressed.png");

	map = new Map("terrain", 3, 32);
	map->LoadMap("assets/testmap.map",16,10);

	//ecs
	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<ColliderComponent>("player");
	player.addComponent<KeyboardController>();

	player.getComponent<ColliderComponent>().setVisible(false);

	player.addGroup(groupPlayers);

	label.addComponent<UILabel>(10, 10, "TestLabel", defaultFont, defaultFontColour);

	button.addComponent<UIButton>(10, 100, 100, 50, "Test1");
	button.addComponent<MouseController>();

	button2.addComponent<UIButton>(10, 200, 100, 50, "Test2");
	button2.addComponent<MouseController>();

	assets->CreateProjectile(Vector2D(100, 100), Vector2D(2, 0), 500, 2, "projectile");
	assets->CreateProjectile(Vector2D(100, 200), Vector2D(2, 0), 500, 2, "projectile");
	assets->CreateProjectile(Vector2D(100, 300), Vector2D(2, 0), 500, 2, "projectile");
	assets->CreateProjectile(Vector2D(100, 400), Vector2D(2, 0), 500, 2, "projectile");
	assets->CreateProjectile(Vector2D(100, 500), Vector2D(2, 0), 500, 2, "projectile");
}

auto& backgrounds(manager.getGroup(Game::groupBackgrounds)); //Background of window
auto& tiles(manager.getGroup(Game::groupMap)); //Environment tiles that interact with player
auto& players(manager.getGroup(Game::groupPlayers)); //Maybe add group for NPCs
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update() {

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "Fixedsys");

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}
	for (auto& p : projectiles) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
			p->destroy();
		}
	}

	//Camera following
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x) - 400;
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y) - 320;

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.x = camera.h;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//Add stuff to update here
	/*for (auto& t : backgrounds) {
		t->draw();
	}*/
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& c : colliders) {
		c->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& p : projectiles) {
		p->draw();
	}
	/*for (auto& e : enemies) {
		e->draw();
	}*/
	label.draw();
	button.draw();
	button2.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

