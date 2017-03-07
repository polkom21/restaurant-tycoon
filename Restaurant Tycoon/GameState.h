#pragma once
#include "Game.h"

class Game;

class GameState
{
public:
	virtual void Draw(const float dt) = 0;
	virtual void Update(const float dt) = 0;
	virtual void HandleInput() = 0;

private:

};
