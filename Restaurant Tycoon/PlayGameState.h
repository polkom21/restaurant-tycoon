#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Map.h"
#include "Gui.h"
#include "GuiLabel.h"

class PlayGameState :
	public GameState
{
private:
	Game * game;
	sf::RectangleShape test;
	Map * map;
	Gui * gui;
public:
	virtual void Draw(const float dt);
	virtual void Update(const float dt);
	virtual void HandleInput();
	PlayGameState(Game * game);
	~PlayGameState();
};

