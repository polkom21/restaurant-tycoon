#pragma once

#include <SFML\Graphics.hpp>
#include <map>

class AssetsManager
{
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
public:
	void LoadTexture(std::string name, std::string fileDir);
	sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileDir);
	sf::Font& GetFont(std::string name);

	AssetsManager();
	~AssetsManager();
};

