#include <iostream>

#include "constants.h"
#include "game.h"
#include "graphics/AssetManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

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

void Game::loadLevel(int levelNumber) {

	std::string textureFilePath = "assets/images/tank-big-right.png";
	assetManager->addTexture("tank-image", textureFilePath.c_str());

	Entity& newEntity(manager.addEntity("tank"));
	newEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	newEntity.addComponent<SpriteComponent>("tank-image");
}

void Game::processInput() {
	SDL_Event event;
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
};

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