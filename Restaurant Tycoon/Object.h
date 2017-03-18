#pragma once

#include <SFML\Graphics.hpp>

enum class ObjectType
{
	ERROR,
	FLOOR
};

class Object
{
public:
	std::string name;
	sf::Sprite sprite;
	ObjectType type;

	Object(ObjectType type, sf::Texture & texture);
	Object(ObjectType type, sf::Texture & texture, sf::IntRect rect);
	~Object();
	void SetPosition(sf::Vector2f pos);
};

