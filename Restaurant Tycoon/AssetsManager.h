#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include "Object.h"

class AssetsManager
{
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, Object> objects;
public:
	void LoadTexture(std::string name, std::string fileDir);
	sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileDir);
	sf::Font& GetFont(std::string name);

	void CreateObject(std::string name, ObjectType type, sf::Texture & texture);
	Object& GetObject(std::string name);

	AssetsManager();
	~AssetsManager();
};

