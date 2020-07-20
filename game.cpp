#include "game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Background.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include "MusicPlayer.hpp"
#include "UIManager.hpp"
#include "Scene/SceneManager.hpp"
#include "Scene/Scenes.hpp"
#include "LevelLoader.hpp"

#include "UIResources/ButtonCallbacks.hpp"

//Level controllers
Map* map;
Background* background;
Manager manager;

//engine components
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
int Game::eventResult = 0; //event can't be null, so we use this
SDL_Rect Game::camera = { 0,0,1200,800 };

//Asset manager
AssetManager* Game::assets = new AssetManager();

//UI Manager
UIManager* Game::uimanager = new UIManager(&manager);

//Scene Manager
SceneManager* Game::scenemanager = new SceneManager(Game::assets);

LevelLoader* Game::levelLoader = new LevelLoader();

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
auto& ui(manager.addEntity());


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
	assets->AddTexture("slider_empty", "assets/UITextures/slider_empty.png");
	assets->AddTexture("slider_full", "assets/UITextures/slider_full.png");
	assets->AddTexture("dropdown_active", "assets/UITextures/dropdown_active.png");
	assets->AddTexture("dropdown_passive", "assets/UITextures/dropdown_passive.png");

	map = new Map("terrain", 3, 32);
	map->LoadMap("assets/testmap.map",16,10);

	background = new Background("background", true);
	background->init();

	//ecs
	/*player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<ColliderComponent>("player");
	player.addComponent<KeyboardController>();
	player.getComponent<ColliderComponent>().setDrawFlag(true);
	player.addGroup(groupPlayers);
	*/

	ButtonCallbacks bck = ButtonCallbacks();
	bck.addEntity(&ui);

	//uimanager->CreateLabel(10, 5, "TestLabel");
	//uimanager->CreateSlider(500, 700, 150, 30, "0000");
	//uimanager->CreateButton(10, 50, 100, 50, "Test1", ButtonCallbacks::test1);

	//ui.addComponent<TransformComponent>(300, 300, 200, 200, 1);
	//ui.addComponent<UIContent>(false);
	//ui.getComponent<UIContent>().addEntity(&button);

	//uimanager->CreateButton(10, 150, 100, 50, "Test2", std::bind(&ButtonCallbacks::test2, bck));

	//std::string temp[] = { "monta", "rajko", "sam", "tristan", "josh" };
	//uimanager->CreateDropdown(60, 300, 100, 50, temp, 5);

	MenuScene* testscene = new MenuScene("test", "levels/MainMenu.xml");
	MenuScene* testscene2 = new MenuScene("test2", "levels/Settings.xml");
	levelLoader->LoadScene(testscene);
	levelLoader->PopulateEntities();
	levelLoader->LoadScene(testscene2);
	levelLoader->PopulateEntities();
	scenemanager->AddScene(testscene);
	scenemanager->AddScene(testscene2);
	scenemanager->SelectScene("test");

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
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_1) {
				printf("Switched to Scene 1\n");
				scenemanager->SelectScene("test");
			}
			else if (event.key.keysym.sym == SDLK_2) {
				printf("Switched to Scene 2\n");
				scenemanager->SelectScene("test2");
			}
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update() {

	/*SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();*/

	scenemanager->update();

	/*for (auto& c : colliders) {
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
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//Keeps camera in bounds of window
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}*/
	/*if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.x = camera.h;
	}*/

	//background->InvokeParallaxHorizontal();
}

void Game::render() {
	SDL_RenderClear(renderer);
	scenemanager->draw();
	//background->Draw();
	//Add stuff to update here
	/*for (auto& t : tiles) {
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
	for (auto& e : uiItems) {
		e->draw();
	}*/
	//TextureManager::Draw(assets->GetTexture("collider"), camera, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_CloseAudio();
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

