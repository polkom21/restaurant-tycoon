#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "AssetsManager.h"

class Map
{
private:
	sf::View mapView;
	sf::Vector2i mapSize;
	std::vector<Tile> tiles;
	AssetsManager assets;
public:
	void Draw(sf::RenderWindow & window);
	void Update(const float dt);

	Map(sf::Vector2i mapSize, sf::Vector2f windowSize, AssetsManager & assetsManager);
	~Map();
};

