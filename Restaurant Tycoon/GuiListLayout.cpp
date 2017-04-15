#include "GuiListLayout.h"

GuiListLayout::GuiListLayout()
{
}


GuiListLayout::~GuiListLayout()
{
}

void GuiListLayout::Draw(sf::RenderWindow & window) const
{
	window.draw(this->backgroundSprite);
	
	for (auto &kv : childs) {
		GetElement(kv.first)->Draw(window);
	}
}

void GuiListLayout::Update(const float dt)
{
	float offsetY = 0;
	for (auto &kv : childs) {
		kv.second->position.y = offsetY;
		kv.second->Update(dt);
		offsetY += kv.second->size.y;
	}

	backgroundSprite.setScale(1.f, 1.f);
	backgroundSprite.setTexture(this->texture.getTexture(), true);
	backgroundSprite.setPosition(this->position);
}

void GuiListLayout::HandleInput(sf::Event & event)
{
	for (auto &kv : childs) {
		GetElement(kv.first)->HandleInput(event);
	}
}

GuiElement * GuiListLayout::AddElement(const std::string name, const GuiElementType type)
{
	switch (type)
	{
	case GuiElementType::LABEL:
		childs.insert(std::make_pair(name, new GuiLabel()));
		GetElement(name)->parentPosition = this->position;
		return GetElement(name);
	case GuiElementType::BUTTON:
		childs.insert(std::make_pair(name, new GuiButton()));
		GetElement(name)->parentPosition = this->position;
		return GetElement(name);
	default:
		break;
	}

	return nullptr;
}

GuiElement * GuiListLayout::GetElement(const std::string name) const
{
	if (childs.find(name) == childs.end()) {
		printf("Not found gui element by name %s\n", name.c_str());
		return nullptr;
	}
	
	return childs.at(name);
}

void GuiListLayout::SetImages(AssetsManager & assets, const std::string textureName)
{
	std::size_t pos = textureName.find('.');
	std::string tName = textureName.substr(0, pos);
	backgroundSprite.setTexture(assets.GetTexture(tName));

	this->texture.create(this->size.x, this->size.y);
	this->texture.clear(sf::Color::Transparent);

	for (int i = 0; i < 9; i++)
	{
		rects[i] = assets.GetRect(textureName + "_" + std::to_string(i+1));
		backgroundSprite.setTextureRect(rects[i]);
		backgroundSprite.setScale(1.f, 1.f);

		switch (i)
		{
		case 0:
			backgroundSprite.setPosition(0, 0);
			break;
		case 1:
			backgroundSprite.setPosition(rects[0].width, 0);
			backgroundSprite.setScale((this->size.x - 2 * rects[0].width) / rects[i].width, 1.f);
			break;
		case 2:
			backgroundSprite.setPosition(this->size.x - rects[i].width, 0);
			break;
		case 3:
			backgroundSprite.setPosition(0, rects[0].height);
			backgroundSprite.setScale(1.f, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 4:
			backgroundSprite.setPosition(rects[0].width, rects[0].height);
			backgroundSprite.setScale((this->size.x - 2 * rects[0].width) / rects[i].width, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 5:
			backgroundSprite.setPosition(this->size.x - rects[i].width, rects[2].height);
			backgroundSprite.setScale(1.f, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 6:
			backgroundSprite.setPosition(0, this->size.y - rects[i].height);
			break;
		case 7:
			backgroundSprite.setPosition(rects[6].width, this->size.y - rects[i].height);
			backgroundSprite.setScale((this->size.x - 2 * rects[0].width) / rects[i].width, 1.f);
			break;
		case 8:
			backgroundSprite.setPosition(this->size.x - rects[i].width, this->size.y - rects[i].height);
			break;
		}

		this->texture.draw(backgroundSprite);
	}

	this->texture.display();
}
