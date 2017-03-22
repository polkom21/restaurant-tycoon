#include "PlayGameState.h"

void PlayGameState::Draw(const float dt)
{
	this->game->window.draw(test);

	this->map->Draw(this->game->window);

	this->gui->Draw(this->game->window);
}

void PlayGameState::Update(const float dt)
{
	this->gui->Update(dt);
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
	}
}

PlayGameState::PlayGameState(Game * game)
{
	this->game = game;

	this->game->assetsManager.LoadFont("arial", "Data/arial.ttf");
	this->game->assetsManager.LoadTextureAtlas("Data/all.atlas");
	this->game->assetsManager.CreateObject("floor", ObjectType::FLOOR, "all.floor");
	
	this->test = sf::RectangleShape();
	this->test.setFillColor(sf::Color::Magenta);
	this->test.setSize(sf::Vector2f(100, 100));
	this->test.setPosition(200, 200);

	this->map = new Map(sf::Vector2i(5, 5), (sf::Vector2f)this->game->window.getSize(), this->game->assetsManager);

	this->gui = new Gui(this->game->assetsManager);

	GuiLabel * label = (GuiLabel*)this->gui->CreateElement("testLabel", GuiElementType::LABEL);
	label->SetText("Label");
	label->SetFont(this->game->assetsManager.GetFont("arial"));
	label->SetTextColor(sf::Color::Green);
}


PlayGameState::~PlayGameState()
{
}
