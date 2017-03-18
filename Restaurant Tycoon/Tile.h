#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include "Object.h"

class Tile
{
private:
	std::map<ObjectType, Object> objects;
	sf::Vector2f size, position;
	sf::Vector2i pos;
public:
	void Draw(sf::RenderWindow & window);
	void AddObject(Object object);
	Tile(sf::Vector2f size, sf::Vector2i pos);
	~Tile();
};

