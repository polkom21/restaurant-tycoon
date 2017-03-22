#pragma once
#include "GuiElement.h"
class GuiLabel :
	public GuiElement
{
private:
	sf::Text text;
public:
	GuiLabel();
	~GuiLabel();
	void Draw(sf::RenderWindow & window) const;
	void Update(const float dt);
	void SetText(std::string text);
	void SetFont(sf::Font & font);
};

