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

	if (button->IsReleased()) {
		this->game->window.close();
	}
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
		
		this->gui->HandleInput(event);
	}
}

PlayGameState::PlayGameState(Game * game)
{
	this->game = game;

	this->game->assetsManager.LoadTextureAtlas("Data/ui.atlas");
	this->game->assetsManager.LoadFont("default", "Data/kenvector_future.ttf");
	this->game->assetsManager.LoadTextureAtlas("Data/All.atlas");
	this->game->assetsManager.CreateObject("floor", ObjectType::FLOOR, "All.floor");
	
	this->test = sf::RectangleShape();
	this->test.setFillColor(sf::Color::Magenta);
	this->test.setSize(sf::Vector2f(100, 100));
	this->test.setPosition(200, 200);

	this->map = new Map(sf::Vector2i(5, 5), (sf::Vector2f)this->game->window.getSize(), this->game->assetsManager);

	this->gui = new Gui(this->game->assetsManager);

	GuiLabel * label = (GuiLabel*)this->gui->CreateElement("testLabel", GuiElementType::LABEL);
	label->SetText("Label");
	label->SetFont(this->game->assetsManager.GetFont("default"));
	label->SetTextColor(sf::Color::Green);

	button = (GuiButton*)this->gui->CreateElement("testButton", GuiElementType::BUTTON);
	button->SetText("Quit game");
	button->SetFont(this->game->assetsManager.GetFont("default"));
	button->SetTextColor(sf::Color::Black);
	button->SetImages(this->game->assetsManager, "ui.grey_button01", "ui.grey_button02");
	button->position = sf::Vector2f(100, 100);

	GuiListLayout * list = (GuiListLayout*)this->gui->CreateElement("testList", GuiElementType::LIST_LAYOUT);
	list->position = sf::Vector2f(350, 200);
	list->size = sf::Vector2f(250, 300);
	list->SetTextColor(sf::Color::Black);
	list->SetImages(this->game->assetsManager, "ui.grey_panel");
	list->SetTitle("List of elements");
}


PlayGameState::~PlayGameState()
{
}
