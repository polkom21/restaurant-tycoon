#include "Tile.h"

void Tile::Draw(sf::RenderWindow & window)
{
	if (objects.find(ObjectType::FLOOR) != objects.end()) {
		window.draw(objects.at(ObjectType::FLOOR).sprite);
	}
}

void Tile::AddObject(Object object)
{
	object.SetPosition(this->position);
	if (this->objects.find(object.type) == this->objects.end()) {
		objects.insert(std::pair<ObjectType, Object>(object.type, object));
	}
	objects.at(object.type) = object;
}

Tile::Tile(sf::Vector2f size, sf::Vector2i pos)
{
	this->size = size;
	this->pos = pos;
	this->position = sf::Vector2f(pos.x * size.x, pos.y * size.y);

	if (this->pos.y % 2 == 1) {
		this->position.x += this->size.x / 2;
	}
	this->position.y -= this->size.y / 2 * this->pos.y;
}


Tile::~Tile()
{
}
