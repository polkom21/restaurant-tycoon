#include "Gui.h"

void Gui::SetPosition(const sf::Vector2f position)
{
	this->size.left = position.x;
	this->size.top = position.y;
}

void Gui::SetSize(const sf::Vector2f size)
{
	this->size.width = size.x;
	this->size.height = size.y;
}

sf::Vector2f Gui::GetPosition() const
{
	return sf::Vector2f(this->size.left, this->size.top);
}

GuiElement * Gui::CreateElement(const std::string name, GuiElementType type)
{
	if (elements.find(name) == elements.end()) {
		// TODO: create new element by type (switch method)
		switch (type)
		{
		case GuiElementType::LABEL:
			elements.insert(std::make_pair(name, new GuiLabel()));
			GetElement(name)->parentPosition = this->GetPosition();
			return GetElement(name);
			break;
		case GuiElementType::BUTTON:
			elements.insert(std::make_pair(name, new GuiButton()));
			GetElement(name)->parentPosition = this->GetPosition();
			return GetElement(name);
			break;
		case GuiElementType::LIST_LAYOUT:
			elements.insert(std::make_pair(name, new GuiListLayout()));
			GetElement(name)->parentPosition = this->GetPosition();
			return GetElement(name);
			break;
		default:
			return nullptr;
			break;
		}
	}
	printf("Gui element by name %s has been created before\n", name.c_str());
	return nullptr;
}

GuiElement * Gui::GetElement(const std::string name) const
{
	if (elements.find(name) == elements.end()) {
		printf("Not found gui element by name %s\n", name.c_str());
		return nullptr;
	}
	return elements.at(name);
}

void Gui::Draw(sf::RenderWindow & window) const
{
	for (auto &kv : elements) {
		GetElement(kv.first)->Draw(window);
	}
}

void Gui::Update(const float dt)
{
	for (auto &kv : elements) {
		kv.second->Update(dt);
	}
}

void Gui::HandleInput(sf::Event & event)
{
	for (auto &kv : elements) {
		kv.second->HandleInput(event);
	}
}

Gui::Gui(AssetsManager & assets)
{
	this->assets = assets;
}


Gui::~Gui()
{
}
