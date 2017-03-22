#include "AssetsManager.h"

void AssetsManager::CreateObject(const std::string name, ObjectType type, const std::string textureName)
{
	Object tmp(type, GetTexture(textureName));
	std::size_t dotPos = textureName.find('.');
	if ((int)dotPos > 0) {
		tmp = Object(type, GetTexture(textureName.substr(0, dotPos)), GetRect(textureName));
	}

	tmp.name = name;

	this->objects.insert(std::pair<std::string, Object>(name, tmp));

	printf("Successfull adding object %s\n", name.c_str());
}

Object & AssetsManager::GetObject(const std::string name)
{
	if (this->objects.find(name) == this->objects.end()) {
		return Object(ObjectType::ERROR, sf::Texture());
	}
	return this->objects.at(name);
}

void AssetsManager::LoadTextureAtlas(const std::string filename)
{
	std::string line, loadedFileName, textureName;
	sf::Texture tempTexture;
	sf::FloatRect rect;
	std::ifstream inputStream;
	inputStream.open(filename);
	if (inputStream.is_open())
	{
		while (inputStream.good())
		{
			std::string param, value;
			std::getline(inputStream, line);
			line = RemoveSpaces(line);
			//printf("%s\n", line.c_str());

			std::size_t pos = line.find('.');

			if ((int)pos > 0) {
				printf("LoadTexture %s\n", line.c_str());
				pos = line.find('.');
				loadedFileName = line.substr(0, pos);
				LoadTexture(loadedFileName, std::string("Data/" + line));
				tempTexture = GetTexture(loadedFileName);
				continue;
			}

			pos = line.find(':');

			if ((int)pos > 0)
			{
				param = line.substr(0, pos);
				value = line.substr(pos + 1);
				
				if (param == "xy") {
					// TODO: get x and y position params
					pos = value.find(',');
					printf("Param: %s\tValue: %s\n", param.c_str(), value.c_str());
					rect.left = std::stof(value.substr(0, pos));
					rect.top = std::stof(value.substr(pos + 1));
				}
				else if (param == "size") {
					// TODO: get x and y size params
					pos = value.find(',');
					printf("Param: %s\tValue: %s\n", param.c_str(), value.c_str());
					rect.width = std::stof(value.substr(0, pos));
					rect.height = std::stof(value.substr(pos + 1));

					std::string fileId = loadedFileName + "." + textureName;
					printf("Add rect of texture name %s to map\n", fileId.c_str());
					rects.insert(std::pair<std::string, sf::IntRect>(loadedFileName + "." + textureName, rect));
					printf("add rect %f %f %f %f\n", rect.top, rect.left, rect.width, rect.height);
				}

				continue;
			}

			if (line.length() > 0)
			{
				printf("Must make texture with name: %s\n", line.c_str());

				textureName = line;
			}
		}
		inputStream.close();
	}
}

sf::IntRect AssetsManager::GetRect(const std::string name)
{
	if (this->rects.find(name) == this->rects.end()) {
		return sf::IntRect();
	}
	return this->rects.at(name);
}

AssetsManager::AssetsManager()
{
}


AssetsManager::~AssetsManager()
{
}

std::string AssetsManager::RemoveSpaces(std::string &string)
{
	string.erase(std::remove(string.begin(), string.end(), ' '), string.end());
	return string;
}

void AssetsManager::LoadTexture(const std::string name, std::string fileDir)
{
	sf::Texture tmp;

	if (!tmp.loadFromFile(fileDir)) {
		printf("Can\'t load texture!\n");
		return;
	}
	this->textures.insert(std::pair<std::string, sf::Texture>(name, tmp));
	return;
}

sf::Texture & AssetsManager::GetTexture(const std::string name)
{
	if (this->textures.find(name) == this->textures.end()) {
		return sf::Texture();
	}
	return this->textures.at(name);
}

void AssetsManager::LoadFont(const std::string name, std::string fileDir)
{
	sf::Font tmp;

	if (!tmp.loadFromFile(fileDir)) {
		printf("Can\'t load font file!\n");
		return;
	}
	this->fonts.insert(std::pair<std::string, sf::Font>(name, tmp));
	return;
}

sf::Font & AssetsManager::GetFont(const std::string name)
{
	if (this->fonts.find(name) == this->fonts.end()) {
		return sf::Font();
	}
	return this->fonts.at(name);
}