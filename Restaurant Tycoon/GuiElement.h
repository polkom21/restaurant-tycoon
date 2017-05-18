#pragma once

#include <SFML\Graphics.hpp>
#include "AssetsManager.h"

enum class GuiElementType {LABEL, BUTTON, LIST_LAYOUT};

class GuiElement
{
protected:
	sf::Color textColor = sf::Color::Black;
	unsigned int characterSize = 16;
	bool clicked = false;
	bool released = false;
public:
	GuiElementType type;
	sf::Vector2f position;
	sf::Vector2f parentPosition;
	sf::Vector2f padding;
	sf::Vector2f size;
	bool toRemove = false;

	virtual void Draw(sf::RenderWindow & window) const = 0;
	virtual void Update(const float dt) = 0;
	virtual void HandleInput(sf::Event & event) = 0;

	void SetTextColor(const sf::Color color) {
		this->textColor = color;
	}

	void SetCharacterSize(const unsigned int size) {
		this->characterSize = size;
	}

	bool IsReleased() {
		if (this->released) {
			this->released = false;
			return true;
		}
		return false;
	}

	bool IsClicked() {
		return this->clicked;
	}
};

