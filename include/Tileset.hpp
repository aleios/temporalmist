#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

class Tileset
{
public:
	unsigned int firstGID;
	std::string name;
	unsigned int tileWidth, tileHeight;
	sf::Texture tex;
};

#endif