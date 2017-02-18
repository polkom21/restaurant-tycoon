#include "Game.h"

int main(int args, char * argv[]) {
	Game * game = new Game();

	game->PushState(new GameState(game));

	game->GameLoop();

	return 0;
}