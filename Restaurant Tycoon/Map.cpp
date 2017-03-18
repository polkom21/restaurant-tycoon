#include "Map.h"

void Map::Draw(sf::RenderWindow & window)
{
	window.setView(this->mapView);

	for (std::vector<Tile>::iterator it = this->tiles.begin(); it != this->tiles.end(); it++)
	{
		it->Draw(window);
	}
}

Map::Map(sf::Vector2i mapSize, sf::Vector2f windowSize, AssetsManager & assetsManager)
{
	this->mapView = sf::View(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);
	this->mapSize = mapSize;
	this->assets = assetsManager;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			sf::Vector2i pos(x, y);
			Tile tile(sf::Vector2f(128, 64), pos);
			tile.AddObject(this->assets.GetObject("floor"));
			this->tiles.push_back(tile);
		}
	}
}


Map::~Map()
{
}
