#pragma once

#include <SFML\Graphics.hpp>

enum class GuiElementType {LABEL};

class GuiElement
{
public:
	GuiElementType type;
	sf::Vector2f position;
	sf::Vector2f parentPosition;

	virtual void Draw(sf::RenderWindow & window) = 0;
	virtual void Update(const float dt) = 0;
};

