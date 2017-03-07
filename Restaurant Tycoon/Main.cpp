#include "Game.h"
#include "PlayGameState.h"

int main(int args, char * argv[]) {
	Game * game = new Game();

	game->PushState(new PlayGameState(game));

	game->GameLoop();

	return 0;
}