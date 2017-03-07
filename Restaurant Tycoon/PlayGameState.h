#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.h"
class PlayGameState :
	public GameState
{
private:
	Game * game;
	sf::RectangleShape test;
public:
	virtual void Draw(const float dt);
	virtual void Update(const float dt);
	virtual void HandleInput();
	PlayGameState(Game * game);
	~PlayGameState();
};

