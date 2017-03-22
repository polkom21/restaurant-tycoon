#pragma once

#include <SFML\Graphics.hpp>

enum class GuiElementType {LABEL};

class GuiElement
{
protected:
	sf::Color textColor = sf::Color::White;
	unsigned int characterSize = 16;
public:
	GuiElementType type;
	sf::Vector2f position;
	sf::Vector2f parentPosition;

	virtual void Draw(sf::RenderWindow & window) const = 0;
	virtual void Update(const float dt) = 0;

	void SetTextColor(const sf::Color color) {
		this->textColor = color;
	}

	void SetCharacterSize(const unsigned int size) {
		this->characterSize = size;
	}
};

