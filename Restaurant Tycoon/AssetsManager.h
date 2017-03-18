#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include "Object.h"

class AssetsManager
{
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::IntRect> rects;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, Object> objects;

	std::string RemoveSpaces(std::string &string);
public:
	void LoadTexture(const std::string name, std::string fileDir);
	sf::Texture& GetTexture(const std::string name);

	void LoadFont(const std::string name, std::string fileDir);
	sf::Font& GetFont(const std::string name);

	void CreateObject(const std::string name, ObjectType type, const std::string textureName);
	Object& GetObject(const std::string name);

	void LoadTextureAtlas(const std::string filename);
	sf::IntRect GetRect(const std::string name);

	AssetsManager();
	~AssetsManager();
};

