#include "game.h"

Game::Game() {
	this->isRunning = false;
	this->window = NULL;
	this->renderer = NULL;
	this->ticksLastFrame = SDL_GetTicks();
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

	this->isRunning = true;

	return true;
};

//Example using glm!
glm::vec2 projectilePosition = glm::vec2(0.0f, 0.0f);

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

	//do the update
	// value += value * deltatime ----> to move smoothly
};

void Game::render() {
	SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255);
	SDL_RenderClear(this->renderer);
	
	SDL_Rect projectile{10, 10,	10,	10};
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(this->renderer, &projectile);

	SDL_RenderPresent(this->renderer);
};

void Game::destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
};