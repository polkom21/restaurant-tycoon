#pragma once
#include "GuiElement.h"
class GuiButton :
	public GuiElement
{
private:
	sf::Text text;
	sf::Sprite background;
	sf::Sprite background_click;
public:
	GuiButton();
	~GuiButton();
	void Draw(sf::RenderWindow & window) const;
	void Update(const float dt);
	void HandleInput(sf::Event & event);
	void SetImages(AssetsManager & assetsManager, const std::string bg, const std::string bg_click);
	void SetText(const std::string text);
	void SetFont(const sf::Font & font);
};

