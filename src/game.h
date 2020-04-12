#ifndef GAME_H
#define GAME_H

#include "../lib/SDL2/include/SDL.h"
#include "../lib/SDL2_Image/include/SDL_image.h"
#include "../lib/SDL2_mixer/include/SDL_mixer.h"
#include "../lib/SDL2_ttf/include/SDL_ttf.h"

#include "entities/Entity.h"
#include "components/Component.h"
#include "entities/EntityManager.h"

class AssetManager;

class Game {

private:
	bool isRunning;
	SDL_Window* window;

public:
	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	int ticksLastFrame = 0;

	Game();
	~Game();
	bool getIsRunning() const;
	bool initialize(const char* title, int width, int height);
	void loadLevel(int levelNumber);
	void processInput();
	void update();
	void render();
	void destroy();

};

#endif // !GAME_H
