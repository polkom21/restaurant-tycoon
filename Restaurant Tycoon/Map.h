#pragma once

#include <SFML\Graphics.hpp>

class Map
{
private:
	sf::View mapView;
public:
	void Draw(sf::RenderWindow & window);
	void Update(const float dt);

	Map(sf::Vector2i mapSize, sf::Vector2f windowSize);
	~Map();
};

