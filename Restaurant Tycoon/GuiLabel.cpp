#include "GuiLabel.h"

GuiLabel::GuiLabel()
{
	this->position = this->text.getPosition();
	this->textColor = sf::Color::Black;
}

GuiLabel::~GuiLabel()
{
}

void GuiLabel::Draw(sf::RenderWindow & window) const
{
	window.draw(this->text);
}


void GuiLabel::Update(const float dt)
{
	this->text.setPosition(this->position + this->parentPosition);
	this->text.setFillColor(this->textColor);
	this->text.setCharacterSize(this->characterSize);
	this->size = sf::Vector2f(this->text.getLocalBounds().width, this->text.getLocalBounds().height);
}

void GuiLabel::HandleInput(sf::Event & event)
{
}

void GuiLabel::SetText(std::string text)
{
	this->text.setString(text);
}

void GuiLabel::SetFont(sf::Font & font)
{
	this->text.setFont(font);
}
