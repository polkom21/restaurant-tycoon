#pragma once

#include <SFML\Graphics.hpp>
#include <stack>
#include "GameState.h"

class GameState;

class Game
{
public:
	std::stack<GameState*> states;
	sf::RenderWindow window;

	void PushState(GameState * state);
	void PopState();
	void ChangeState(GameState * state);
	GameState * PeekState();

	void GameLoop();

	Game();
	~Game();
};

