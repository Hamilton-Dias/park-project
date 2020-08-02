#include <iostream>

#include "constants.h"
#include "game.h"
#include "graphics/AssetManager.h"
#include "Map.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControllerComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* map;

Game::Game() {
	this->isRunning = false;
	this->window = NULL;
	this->renderer = NULL;
	//this->ticksLastFrame = SDL_GetTicks();
};

Game::~Game() {};

bool Game::getIsRunning() const {
	return this->isRunning;
};

bool Game::initialize(const char* title, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL" << std::endl;
		return false;
	}

	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!this->window) {
		std::cout << "Error creating Window" << std::endl;
		return false;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (!this->renderer) {
		std::cout << "Error creating Renderer" << std::endl;
		return false;
	}

	this->loadLevel(0);

	this->isRunning = true;

	return true;
};

void Game::loadLevel(int levelNumber)
{
	assetManager->addTexture("tank-image", std::string("assets/images/tank-big-right.png").c_str());
	assetManager->addTexture("chopper-image", std::string("assets/images/chopper-spritesheet.png").c_str());
	assetManager->addTexture("radar-image", std::string("assets/images/radar.png").c_str());
	assetManager->addTexture("jungle-tiletexture", std::string("assets/tilemaps/jungle.png").c_str());

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("assets/tilemaps/jungle.map", 25, 20);

	Entity& chopperEntity(manager.addEntity("chopper", PLAYER_LAYER));
	chopperEntity.addComponent<TransformComponent>(240, 100, 0, 0, 32, 32, 1);
	chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	chopperEntity.addComponent<KeyboardControllerComponent>("up", "right", "down", "left", "space");

	Entity& tankEntity(manager.addEntity("tank", ENEMY_LAYER));
	tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.addComponent<SpriteComponent>("tank-image");

	Entity& radarEntity(manager.addEntity("radar", UI_LAYER));
	radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

void Game::processInput() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				this->isRunning = false;
			}
			break;

		default:
			break;
	}
};

void Game::update() {

	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - this->ticksLastFrame) / 1000.0f;
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
	this->ticksLastFrame = SDL_GetTicks();

	manager.update(deltaTime);

	//HandleCameraMovement();
};

/*void Game::HandleCameraMovement() {
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}*/

void Game::render() {
	SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
	SDL_RenderClear(this->renderer);
	
	if (manager.hasNoEntities()) {
		return;
	}

	manager.render();

	SDL_RenderPresent(this->renderer);
};

void Game::destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
};