#include "GuiButton.h"

GuiButton::GuiButton()
{
	this->textColor = sf::Color::Black;
}


GuiButton::~GuiButton()
{
}

void GuiButton::Draw(sf::RenderWindow & window) const
{
	if(!this->clicked)
		window.draw(this->background);
	else
		window.draw(this->background_click);
	window.draw(this->text);
}

void GuiButton::Update(const float dt)
{
	sf::Vector2f pos = this->position + this->parentPosition;

	float onClickDiff = this->background.getLocalBounds().height - this->background_click.getLocalBounds().height;

	if (this->clicked)
		pos.y += onClickDiff;

	this->text.setFillColor(this->textColor);
	this->text.setCharacterSize(this->characterSize);

	this->background.setPosition(pos);
	this->background_click.setPosition(pos);
	
	pos.x += (this->background.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2;
	pos.y += (this->background.getGlobalBounds().height - this->text.getGlobalBounds().height) / 4;
	this->text.setPosition(pos);
	
	this->size = sf::Vector2f(this->background.getLocalBounds().width, this->background.getLocalBounds().height);
}

void GuiButton::HandleInput(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (this->background.getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
			this->clicked = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		if (this->background.getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) 
			&& this->clicked) {
			this->released = true;
			this->clicked = false;
		}
	}
	else if (event.type == sf::Event::MouseMoved && this->clicked) {
		if (!this->background.getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
			this->clicked = false;
	}
}

void GuiButton::SetImages(AssetsManager & assetsManager, const std::string bg, const std::string bg_click)
{
	std::size_t pos = bg.find('.');
	this->background.setTexture(assetsManager.GetTexture(bg.substr(0, pos)));
	this->background.setTextureRect(assetsManager.GetRect(bg));

	pos = bg_click.find('.');
	this->background_click.setTexture(assetsManager.GetTexture(bg_click.substr(0, pos)));
	this->background_click.setTextureRect(assetsManager.GetRect(bg_click));
}

void GuiButton::SetText(const std::string text)
{
	this->text.setString(text);
}

void GuiButton::SetFont(const sf::Font & font)
{
	this->text.setFont(font);
}
