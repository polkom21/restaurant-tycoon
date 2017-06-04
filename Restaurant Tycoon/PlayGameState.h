#pragma once
#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>
#include "GameState.h"
#include "Map.h"

class PlayGameState :
	public GameState
{
private:
	Game * game;
	sf::RectangleShape test;
	Map * map;
	tgui::Gui gui;
	tgui::Theme theme;
	tgui::ChildWindow::Ptr debugWindow;
	tgui::Label::Ptr fpsLabel, renderTimeLabel;
public:
	virtual void Draw(const float dt);
	virtual void Update(const float dt);
	virtual void HandleInput();
	PlayGameState(Game * game);
	~PlayGameState();
};

