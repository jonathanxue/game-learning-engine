#include "game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Background.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include "MusicPlayer.hpp"
#include <sstream>

#include "UIResources/ButtonCallbacks.hpp"

//Level controllers
Map* map;
Background* background;
Manager manager;

//engine components
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
int Game::eventResult = 0; //event can't be null, so we use this
SDL_Rect Game::camera = { 0,0,800,640 };
SDL_Rect temp = { 0,0,800,640 };

//Asset manager
AssetManager* Game::assets = new AssetManager(&manager);

//Default values
std::string Game::defaultFont = "Fixedsys";
SDL_Color Game::defaultFontColour = { 255,255,255,255 }; //White
SDL_Color Game::defaultFontBackgroundColour = { 0,0,0,0 }; //Black

//Gamestate stuff
Game::gameState Game::state = Game::gameState::game_running;
bool Game::isRunning = false;

//Other globals
MusicPlayer* musicplayer;

//Level entities
auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& button(manager.addEntity());
auto& button2(manager.addEntity());
auto& ui(manager.addEntity());
auto& slider(manager.addEntity());

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

		//Default shit, maybe change
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		musicplayer = new MusicPlayer();

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

	//Music Assets
	assets->AddMusic("defaultBGM", "assets/testBGM.mp3");
	assets->AddSoundEffect("spellmoving", "assets/spell.wav");
	assets->AddSoundEffect("spellhit", "assets/interface4.wav");

	musicplayer->setSong("defaultBGM");
	//musicplayer->play();

	assets->AddTexture("terrain", "assets/grassmap_textures.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/testprojectile.png");
	assets->AddTexture("background", "assets/testBG.png");

	assets->AddTexture("collider", "assets/hitbox.png");

	//UI textures
	assets->AddFont("Fixedsys", "assets/UITextures/vgafix.fon", 16);
	assets->AddTexture("button_default", "assets/UITextures/button_default.png");
	assets->AddTexture("button_pressed", "assets/UITextures/button_pressed.png");
	assets->AddTexture("menu", "assets/UITextures/menutexture.png");
	assets->AddTexture("slider_empty", "assets/UITextures/sliderEmpty.png");
	assets->AddTexture("slider_full", "assets/UITextures/sliderFull.png");

	map = new Map("terrain", 3, 32);
	map->LoadMap("assets/testmap.map",16,10);

	background = new Background("background", true);
	background->init();

	//ecs
	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<ColliderComponent>("player");
	player.addComponent<KeyboardController>();
	player.getComponent<ColliderComponent>().setVisible(true);
	player.addGroup(groupPlayers);

	label.addComponent<TransformComponent>(10,5);
	label.addComponent<UILabel>("TestLabel", defaultFont, defaultFontColour, -1);
	label.addComponent<TypingController>();
	label.addComponent<MouseController>();
	//label.getComponent<TypingController>().enableTyping();

	ButtonCallbacks bck = ButtonCallbacks();
	bck.addEntity(&ui);

	slider.addComponent<TransformComponent>(500, 700, 150, 30, 1);
	slider.addComponent<UILabel>("0000", defaultFont, defaultFontColour, 0);
	slider.addComponent<UISlider>();
	slider.addComponent<MouseController>();

	button.addComponent<TransformComponent>(10, 50, 100, 50, 1);
	button.addComponent<UIButton>();
	button.addComponent<UILabel>("Test1", defaultFont, defaultFontColour, 0);
	button.getComponent<UIButton>().setCallBack(ButtonCallbacks::test1);
	button.addComponent<SoundEffectComponent>("spellhit", 0);
	button.addComponent<MouseController>();

	ui.addComponent<TransformComponent>(300, 300, 200, 200, 1);
	ui.addComponent<UIContent>(false);
	ui.getComponent<UIContent>().addEntity(&button);

	button2.addComponent<TransformComponent>(10, 150, 100, 50, 1);
	button2.addComponent<UIButton>();
	button2.getComponent<UIButton>().setCallBack(std::bind(&ButtonCallbacks::test2, bck));
	button2.addComponent<UILabel>("Test2", defaultFont, defaultFontColour, 0);
	button2.addComponent<SoundEffectComponent>("spellhit", 0);
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
auto& uiItems(manager.getGroup(Game::groupUI));

//Main event listener
void Game::handleEvents() {
	eventResult = SDL_PollEvent(&event);
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

	//std::stringstream ss;
	//ss << "Player position: " << playerPos;
	//label.getComponent<UILabel>().SetLabelText(ss.str(), "Fixedsys");

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
			p->getComponent<SoundEffectComponent>().stop();
			p->destroy();
		}
	}

	//Camera following
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x) - 400;
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y) - 320;

	//Keeps camera in bounds of window
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	/*if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.x = camera.h;
	}*/
	//std::cout << camera.x << ", " << camera.y << std::endl;
	background->InvokeParallax();
}

void Game::render() {
	SDL_RenderClear(renderer);
	background->Draw();
	//Add stuff to update here
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
	//ui.draw();
	button2.draw();
	//slider.draw();
	//TextureManager::Draw(assets->GetTexture("collider"), temp, Game::camera, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_CloseAudio();
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

