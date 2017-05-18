#include "GuiListLayout.h"

GuiListLayout::GuiListLayout()
{
	this->title.setString("Panel");
	this->title.setCharacterSize(this->characterSize);
	this->textColor = sf::Color::Black;

	this->exitButton = new GuiButton();
}


GuiListLayout::~GuiListLayout()
{
}

void GuiListLayout::Draw(sf::RenderWindow & window) const
{
	window.draw(this->backgroundSprite);
	
	window.draw(this->title);

	this->exitButton->Draw(window);

	for (auto &kv : childs) {
		GetElement(kv.first)->Draw(window);
	}
}

void GuiListLayout::Update(const float dt)
{
	float offsetY = 0;
	for (auto &kv : childs) {
		kv.second->parentPosition = this->position + this->padding;
		kv.second->position.y = offsetY;
		kv.second->Update(dt);
		offsetY += kv.second->size.y + 8;
	}

	backgroundSprite.setScale(1.f, 1.f);
	backgroundSprite.setTexture(this->texture.getTexture(), true);
	backgroundSprite.setPosition(this->position);

	this->title.setPosition(this->position);
	this->title.move(padding.x, (padding.y - this->title.getCharacterSize()) / 2);
	this->title.setFillColor(this->textColor);

	this->exitButton->parentPosition = this->position;
	this->exitButton->position = sf::Vector2f(this->size.x - this->exitButton->size.x - padding.x/2, (padding.y - this->title.getCharacterSize()) / 2);
	this->exitButton->Update(dt);
}

void GuiListLayout::HandleInput(sf::Event & event)
{
	for (auto &kv : childs) {
		kv.second->HandleInput(event);
		if (kv.second->IsClicked())
			this->selectedItem = kv.first;
	}

	exitButton->HandleInput(event);

	sf::Vector2f mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
	sf::Vector2f mouseMove = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
	titleHandler.left = this->position.x;
	titleHandler.top = this->position.y;

	sf::FloatRect rectElement = sf::FloatRect(position.x, position.y, size.x, size.y);

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
		if (rectElement.contains(mousePos)) {
			this->clicked = true;
			this->released = false;
			clickDiffPos = this->position - mousePos;
		}
		if (titleHandler.contains(mousePos))
			this->dragNDrop = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
		this->clicked = false;

		if (rectElement.contains(mousePos))
			this->released = true;

		if (titleHandler.contains(mousePos))
			this->dragNDrop = false;
	}

	if (event.type == sf::Event::MouseMoved && this->dragNDrop) {
		this->position = mouseMove + clickDiffPos;
	}

	if (this->exitButton->IsReleased())
		this->toRemove = true;
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

std::string GuiListLayout::GetSelectedItem() const
{
	return this->selectedItem;
}

void GuiListLayout::SetImages(AssetsManager & assets, const std::string textureName)
{
	this->exitButton->SetImages(assets, "ui.grey_crossGrey", "ui.grey_crossGrey");
	
	std::size_t pos = textureName.find('.');
	std::string tName = textureName.substr(0, pos);
	backgroundSprite.setTexture(assets.GetTexture(tName));

	this->texture.create((unsigned int)this->size.x, (unsigned int)this->size.y);
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
			backgroundSprite.setPosition((float)rects[0].width, 0);
			backgroundSprite.setScale((this->size.x - 2 * rects[0].width) / rects[i].width, 1.f);
			break;
		case 2:
			backgroundSprite.setPosition(this->size.x - rects[i].width, 0);
			break;
		case 3:
			backgroundSprite.setPosition(0, (float)rects[0].height);
			backgroundSprite.setScale(1.f, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 4:
			backgroundSprite.setPosition((float)rects[0].width, (float)rects[0].height);
			backgroundSprite.setScale((this->size.x - 2 * rects[0].width) / rects[i].width, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 5:
			backgroundSprite.setPosition(this->size.x - rects[i].width, (float)rects[2].height);
			backgroundSprite.setScale(1.f, (this->size.y - 2 * rects[0].height) / rects[i].height);
			break;
		case 6:
			backgroundSprite.setPosition(0, this->size.y - rects[i].height);
			break;
		case 7:
			backgroundSprite.setPosition((float)rects[6].width, this->size.y - rects[i].height);
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

	this->padding = sf::Vector2f((float)rects[0].width, (float)rects[0].height);

	this->titleHandler = sf::FloatRect(0, 0, this->size.x, (float)rects[0].height);
	this->title.setCharacterSize(rects[0].height * .55f);
}

void GuiListLayout::SetTitle(const std::string title)
{
	this->title.setString(title);
}
