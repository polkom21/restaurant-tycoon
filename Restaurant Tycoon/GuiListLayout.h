#pragma once
#include <map>
#include "GuiElement.h"
#include "GuiLabel.h"
#include "GuiButton.h"

class GuiListLayout :
	public GuiElement
{
private:
	std::map<std::string, GuiElement*> childs;
	sf::IntRect rects[9];
	sf::RenderTexture texture;
	sf::Sprite backgroundSprite;
public:
	GuiListLayout();
	~GuiListLayout();
	void Draw(sf::RenderWindow & window) const;
	void Update(const float dt);
	void HandleInput(sf::Event & event);

	GuiElement * AddElement(const std::string name, const GuiElementType type);
	GuiElement * GetElement(const std::string name) const;

	void SetImages(AssetsManager & assets, const std::string textureName);
};

