#include "Object.h"

Object::Object(ObjectType type, sf::Texture & texture)
{
	this->type = type;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y - 32.f);
}

Object::Object(ObjectType type, sf::Texture & texture, sf::IntRect rect)
{
	this->type = type;
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(rect);
	this->sprite.setOrigin(rect.width / 2.f, rect.height - 32.f);
}

Object::~Object()
{
}

void Object::SetPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}
