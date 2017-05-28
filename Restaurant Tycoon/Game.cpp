#include "Game.h"

void Game::PushState(GameState * state)
{
	this->states.push(state);

	return;
}

void Game::PopState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::ChangeState(GameState * state)
{
	if (this->states.empty())
		PopState();
	PushState(state);

	return;
}

GameState * Game::PeekState()
{
	if (this->states.empty())
		return nullptr;
	return this->states.top();
}

void Game::GameLoop()
{
	sf::Clock clock, fpsClock;
	sf::Time frameStepper = sf::Time::Zero;
	int frameCounter = 0;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		float dt = elapsed.asSeconds();

		if (fpsClock.getElapsedTime().asSeconds() >= 1.f) {
			fpsClock.restart();
			this->FPS = frameCounter;
			frameCounter = 0;
		}
		frameCounter++;

		if (PeekState() == nullptr)
			continue;
		clock.restart();
		PeekState()->HandleInput();
		PeekState()->Update(dt);

		clock.restart();
		this->window.clear(sf::Color::Black);
		PeekState()->Draw(dt);
		this->window.display();
		renderTime = clock.getElapsedTime().asSeconds();
		clock.restart();
	}
}

Game::Game()
{
	this->window.create(sf::VideoMode(800, 600), "Restaurant Tycoon");
	this->window.setFramerateLimit(60);
}


Game::~Game()
{
	while (!this->states.empty()) PopState();
}
