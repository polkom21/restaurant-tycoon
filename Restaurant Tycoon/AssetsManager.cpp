#include "AssetsManager.h"



AssetsManager::AssetsManager()
{
}


AssetsManager::~AssetsManager()
{
}

void AssetsManager::LoadTexture(std::string name, std::string fileDir)
{
	sf::Texture tmp;

	if (!tmp.loadFromFile(fileDir)) {
		printf("Can\'t load texture!\n");
		return;
	}
	this->textures.insert(std::pair<std::string, sf::Texture>(name, tmp));
	return;
}

sf::Texture & AssetsManager::GetTexture(std::string name)
{
	if (this->textures.find(name) == this->textures.end()) {
		return sf::Texture();
	}
	return this->textures.at(name);
}

void AssetsManager::LoadFont(std::string name, std::string fileDir)
{
	sf::Font tmp;

	if (!tmp.loadFromFile(fileDir)) {
		printf("Can\'t load font file!\n");
		return;
	}
	this->fonts.insert(std::pair<std::string, sf::Font>(name, tmp));
	return;
}

sf::Font & AssetsManager::GetFont(std::string name)
{
	if (this->fonts.find(name) == this->fonts.end()) {
		return sf::Font();
	}
	return this->fonts.at(name);
}