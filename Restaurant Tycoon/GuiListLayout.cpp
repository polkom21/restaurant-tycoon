#include "GuiListLayout.h"

GuiListLayout::GuiListLayout()
{
	this->title.setString("Panel");
	this->title.setCharacterSize(this->characterSize);
}


GuiListLayout::~GuiListLayout()
{
}

void GuiListLayout::Draw(sf::RenderWindow & window) const
{
	window.draw(this->backgroundSprite);
	
	window.draw(this->title);

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

	this->title.setPosition(this->position + this->padding);
	this->title.setFillColor(this->textColor);
}

void GuiListLayout::HandleInput(sf::Event & event)
{
	for (auto &kv : childs) {
		GetElement(kv.first)->HandleInput(event);
	}

	sf::Vector2f mousePos = sf::Vector2f((int)event.mouseButton.x, (int)event.mouseButton.y);
	sf::Vector2f mouseMove = sf::Vector2f((int)event.mouseMove.x, (int)event.mouseMove.y);
	titleHandler.left = this->position.x;
	titleHandler.top = this->position.y;

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
		if (titleHandler.contains(mousePos)) {
			this->clicked = true;
			this->released = false;
			clickDiffPos = this->position - mousePos;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
		this->clicked = false;
		if (titleHandler.contains(mousePos)) {
			this->released = true;
		}
	}

	if (event.type == sf::Event::MouseMoved && this->clicked) {
		this->position = mouseMove + clickDiffPos;
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

	this->title.setFont(assets.GetFont("default"));

	this->padding = sf::Vector2f(rects[0].width, rects[0].height);

	this->titleHandler = sf::FloatRect(0, 0, this->size.x, rects[0].height);
}

void GuiListLayout::SetTitle(const std::string title)
{
	this->title.setString(title);
}
