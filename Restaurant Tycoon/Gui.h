#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "GuiElement.h"
#include "GuiLabel.h"
#include "GuiButton.h"
#include "GuiListLayout.h"

class Gui
{
private:
	AssetsManager assets;
	std::map<std::string, GuiElement*> elements;
	sf::FloatRect size;
public:
	Gui(AssetsManager & assets);
	~Gui();

	void SetPosition(const sf::Vector2f position);
	void SetSize(const sf::Vector2f size);
	sf::Vector2f GetPosition() const;

	GuiElement * CreateElement(const std::string name, GuiElementType type);
	GuiElement * GetElement(const std::string name) const;
	bool RemoveElement(const std::string name);

	void Draw(sf::RenderWindow & window) const;
	void Update(const float dt);
	void HandleInput(sf::Event & event);
};

