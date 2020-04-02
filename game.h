#ifndef GAME_H
#define GAME_H

#include <iostream>;

#include "lib/SDL2/include/SDL.h"
#include "lib/SDL2_Image/include/SDL_image.h"
#include "lib/SDL2_mixer/include/SDL_mixer.h"
#include "lib/SDL2_ttf/include/SDL_ttf.h"
#include "lib/glm/glm.hpp"

#include "constants.h"

class Game {

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	int ticksLastFrame;

	Game();
	~Game();
	bool getIsRunning() const;
	bool initialize(const char* title, int width, int height);
	void processInput();
	void update();
	void render();
	void destroy();

};

#endif // !GAME_H
