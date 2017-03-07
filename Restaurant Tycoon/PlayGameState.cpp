#include "PlayGameState.h"



void PlayGameState::Draw(const float dt)
{
	this->game->window.draw(test);
}

void PlayGameState::Update(const float dt)
{
}

void PlayGameState::HandleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			game->window.close();
		}
		default:
			break;
		}
	}
}

PlayGameState::PlayGameState(Game * game)
{
	this->game = game;
	
	this->test = sf::RectangleShape();
	this->test.setFillColor(sf::Color::Magenta);
	this->test.setSize(sf::Vector2f(100, 100));
	this->test.setPosition(200, 200);
}


PlayGameState::~PlayGameState()
{
}
