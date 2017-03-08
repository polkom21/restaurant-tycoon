#include "Map.h"



void Map::Draw(sf::RenderWindow & window)
{
	window.setView(this->mapView);
}

Map::Map(sf::Vector2i mapSize, sf::Vector2f windowSize)
{
	this->mapView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);
}


Map::~Map()
{
}
