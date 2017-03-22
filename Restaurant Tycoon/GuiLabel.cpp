#include "GuiLabel.h"

GuiLabel::GuiLabel()
{
	this->position = this->text.getPosition();
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
	this->text.setPosition(sf::Vector2f(this->position.x + parentPosition.x, this->position.y + parentPosition.y));
	this->text.setFillColor(this->textColor);
	this->text.setCharacterSize(this->characterSize);
}

void GuiLabel::SetText(std::string text)
{
	this->text.setString(text);

	printf("Change string to: %s\n", text.c_str());
}

void GuiLabel::SetFont(sf::Font & font)
{
	this->text.setFont(font);
}
