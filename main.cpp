#include "lib/lua/lua.h"

#include "src/constants.h"
#include "src/game.h"

int main(int argc, char* argv[]) {

	Game *game = new Game();

	game->initialize(GAME_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->getIsRunning()) {
		game->processInput();
		game->update();
		game->render();
	}

	game->destroy();

	return 0;
}