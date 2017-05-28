#include "PlayGameState.h"

void PlayGameState::Draw(const float dt)
{
	this->game->window.draw(test);

	//this->map->Draw(this->game->window);
	this->gui.draw();
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
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				game->window.close();
		}
		default:
			break;
		}
		this->gui.handleEvent(event);
	}
}

PlayGameState::PlayGameState(Game * game)
{
	this->game = game;

	this->game->assetsManager.LoadTextureAtlas("Data/ui.atlas");
	this->game->assetsManager.LoadFont("default", "Data/kenvector_future.ttf");
	this->game->assetsManager.LoadTextureAtlas("Data/All.atlas");
	this->game->assetsManager.CreateObject("floor", ObjectType::FLOOR, "All.floor");

	this->map = new Map(sf::Vector2i(5, 5), (sf::Vector2f)this->game->window.getSize(), this->game->assetsManager);

	gui.setWindow(game->window);
	auto exitBtn = tgui::Button::create("Close program");
	exitBtn->connect("pressed", [=]() { game->window.close(); });
	exitBtn->setPosition(100, 100);
	gui.add(exitBtn);
}


PlayGameState::~PlayGameState()
{
}
