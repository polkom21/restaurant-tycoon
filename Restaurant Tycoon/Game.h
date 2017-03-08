#pragma once

#include <SFML\Graphics.hpp>
#include <stack>
#include "GameState.h"
#include "AssetsManager.h"

class GameState;

class Game
{
public:
	std::stack<GameState*> states;
	sf::RenderWindow window;
	AssetsManager assetsManager;

	void PushState(GameState * state);
	void PopState();
	void ChangeState(GameState * state);
	GameState * PeekState();

	void GameLoop();

	Game();
	~Game();
};

