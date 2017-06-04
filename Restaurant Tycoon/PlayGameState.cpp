#include "PlayGameState.h"

void PlayGameState::Draw(const float dt)
{
	this->game->window.draw(test);

	this->map->Draw(this->game->window);

	this->gui.draw();
}

void PlayGameState::Update(const float dt)
{
	this->fpsLabel->setText("FPS: " + std::to_string(this->game->FPS));
	this->renderTimeLabel->setText("Render time: " + std::to_string(this->game->renderTime));
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

	this->game->assetsManager.LoadFont("default", "Data/kenvector_future.ttf");
	this->game->assetsManager.LoadTextureAtlas("Data/All.atlas");
	this->game->assetsManager.CreateObject("floor", ObjectType::FLOOR, "All.floor");

	this->map = new Map(sf::Vector2i(5, 5), (sf::Vector2f)this->game->window.getSize(), this->game->assetsManager);

	gui.setWindow(game->window);
	this->theme = tgui::Theme{"Data/Black.txt"};

	this->fpsLabel = tgui::Label::create("FPS");
	this->renderTimeLabel = tgui::Label::create("RenderTime");
	this->renderTimeLabel->setPosition(0, 30);

	this->debugWindow = tgui::ChildWindow::create();
	this->debugWindow->setRenderer(theme.getRenderer("ChildWindow"));
	this->debugWindow->setTitle("Debug");
	this->debugWindow->setTitleButtons(tgui::ChildWindow::Minimize | tgui::ChildWindow::Maximize | tgui::ChildWindow::Close);
	this->debugWindow->add(this->fpsLabel);
	this->debugWindow->add(this->renderTimeLabel);
	gui.add(this->debugWindow);

	auto exitBtn = tgui::Button::create("Close program");
	exitBtn->setRenderer(this->theme.getRenderer("Button"));
	exitBtn->connect("pressed", [=]() { game->window.close(); });
	exitBtn->setPosition(100, 200);
	this->debugWindow->add(exitBtn);
}


PlayGameState::~PlayGameState()
{
}
